#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "stat.h"
#include "spinlock.h"
#include "proc.h"
#include "fs.h"
#include "sleeplock.h"
#include "file.h"
#include "fcntl.h"
#include "memlayout.h"

#define max(a, b) (a) > (b) ? (a):(b)

// Fetch the nth word-sized system call argument as a file descriptor
// and return both the descriptor and the corresponding struct file.
static int
argfd(int n, int *pfd, struct file **pf)
{
  int fd;
  struct file *f;

  if(argint(n, &fd) < 0)
    return -1;
  if(fd < 0 || fd >= NOFILE || (f=myproc()->ofile[fd]) == 0)
    return -1;
  if(pfd)
    *pfd = fd;
  if(pf)
    *pf = f;
  return 0;
}

uint64
sys_mmap(void)
{
  uint64 addr, start=MMAP_START;
  int length, prot, flags, offset;
  struct file *f;
  int found = 0;
  if(argaddr(0, &addr)   < 0 ||
      argint(1,  &length) < 0 ||
      argint(2,  &prot)   < 0 ||
      argint(3,  &flags)  < 0 ||
      argint(5,  &offset) < 0 ||
      argfd(4, 0, &f)     < 0
      ) {
    return -1;
  }
  if(prot & PROT_WRITE && !((flags & MAP_PRIVATE) || (f->writable))) {
    return 0xffffffffffffffff;
  }
  struct proc *p = myproc();
  struct vma *mmaps = p->mmaps;
  struct vma *m = 0;
  for(int i = 0; i < 16; i++) {
    if(!m) {
      if(!mmaps[i].length) {
        found = 1;
        m = &mmaps[i];
      }
    }
    if(mmaps[i].length) {
      start = max(start, (uint64) ((char *)mmaps[i].addr + mmaps[i].length));
    }
  }
  if(!found) {
    return 0xffffffffffffffff;
  }
  filedup(f);
  m->addr   = start;
  m->length = length;
  m->prot   = prot;
  m->flags  = flags;
  m->f      = f;
  m->offset = offset;
  return m->addr;
}

uint64
sys_munmap(void)
{
  uint64 addr;
  int length;
  if(argaddr(0, &addr) < 0 ||
      argint(1,  &length) < 0 ) {
    return -1;
  }

	return kmunmap(addr, length);
}

int
kmunmap(uint64 addr, int length)
{
	uint64 start1, start2, end1, end2;
	int found = 0;
  struct proc *p = myproc();
  struct vma *mmap = p->mmaps;
  for(int i = 0; i < 16; i++) {
    if(mmap->length) {
      uint64 start = mmap->addr;
      uint64 end = (uint64) ((char *) mmap->addr + mmap->length);
      if(addr >= start && addr < end) {
        found = 1;
        break;
      }
    }
    mmap++;
  }

  if(!found) {
    return -1;
  }

	start1 = (uint64) ((char *) mmap->addr);
	end1 = (uint64) ((char *) mmap->addr + mmap->length);
	start2 = addr;
	end2 = (uint64) ((char *) addr + length);

	// write back into disk
	for(int offset = 0; offset < length; offset += PGSIZE) {
		uint64 a = (uint64) ((char *) addr) + offset;
		pte_t *pte = walk(p->pagetable, a, 0);
		if(pte == 0) {
			continue;
		}
		if(mmap->flags & MAP_SHARED) {
      if (*pte & PTE_D) {
        begin_op();
        ilock(mmap->f->ip);
        writei(mmap->f->ip, 1, a, a - mmap->addr, PGSIZE);
        iunlock(mmap->f->ip);
        end_op();
      }
    }
		// free the allocated page
		uvmunmap(p->pagetable, a, 1, 1);
  }

	if(start1 == start2) {
		mmap->addr = end2;
		mmap->length = (int) ((char *) end1 - (char *) end2);
	} else if(end1 == end2) {
		mmap->length = (int) ((char *) start2 - (char *) start1);
	}
	if(mmap->length == 0) {
		fileclose(mmap->f);
		memset(mmap, 0, sizeof(struct vma));
	}
  return 0;
}
