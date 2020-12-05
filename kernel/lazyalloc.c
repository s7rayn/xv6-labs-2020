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

#define min(a, b) (a) < (b) ? (a):(b)

void lazyalloc(void)
{
  struct proc *p = myproc();
  uint64 stval = r_stval();
  struct vma *mmap = p->mmaps;
  int found = 0;

  for(int i = 0; i < 16; i++) {
    if(mmap->length) {
      uint64 start = mmap->addr;
      uint64 end = (uint64) ((char *) mmap->addr + mmap->length);
      if(stval >= start && stval < end) {
        found = 1;
        break;
      }
      mmap++;
    }
  }

  if(!found) {
    //panic("vma not found");
		exit(-1);
  }

  struct file *f = mmap->f;
  int offset = mmap->offset;
  uint64 off = offset + (uint64) ((char *) PGROUNDDOWN(stval) - (char *) mmap->addr);

  // load content from file
  void *data = kalloc();
  memset(data, 0 , PGSIZE);
  if(!data) {
    panic("lazy alloc, no enough memory.");
  }
  if(mappages(p->pagetable, stval, PGSIZE, (uint64) data, PTE_U | PTE_W | PTE_R | PTE_V | PTE_X) != 0) {
    panic("lazyalloc mappages.");
  }

  ilock(f->ip);
  if(readi(f->ip, 1, (uint64) PGROUNDDOWN(stval), off, PGSIZE) < 0) {
    panic("lazyalloc read.");
  }
  iunlock(f->ip);
}
