# MIT 6.S081 Operačné systémy 2020

https://uim.fei.stuba.sk/predmet/b-os/

- [x] [Lab util: Unix utilities (utility)](https://github.com/s7rayn/xv6-labs-2020/tree/util)
- [Sleep (ľahká)](https://github.com/s7rayn/xv6-labs-2020/commit/ef2b4445afe068d0984f8f38019c3583e7314adc)
- [Pingpong (ľahká)](https://github.com/s7rayn/xv6-labs-2020/commit/7c2a045da75dbc31de63c99787573e8b9c8039c8)
- [Primes (stredná)/(ťažká)](https://github.com/s7rayn/xv6-labs-2020/commit/0bfd937421d6aa8cb871927678253290f4edda18)
- [Find (stredná)](https://github.com/s7rayn/xv6-labs-2020/commit/3f722541770f7dd7f9b77a6f9165234a69521318)
- [Xargs (stredná)](https://github.com/s7rayn/xv6-labs-2020/commit/3c269e9e6c4a39834a3a173f33b98eca7ec6b9ec)
- [x] [Lab syscall: System calls (systémové volania)](https://github.com/s7rayn/xv6-labs-2020/tree/syscall)
- [Trasovanie systémových volaní (stredná)](https://github.com/s7rayn/xv6-labs-2020/commit/7f9a466272357faa3879838767cfaa0c850c2d23)
- [Sysinfo (stredná)](https://github.com/s7rayn/xv6-labs-2020/commit/cd42188e8a98f375f1f6ee18ea88dd34cff7aaaf)
- [ ] [Lab pgtbl: Page tables (tabuľky stránok)](https://github.com/s7rayn/xv6-labs-2020/tree/pgtbl) - chýba zjednodušenie copyin/copyinstr
- [Vypísanie tabuľky stránok (ľahká)](https://github.com/s7rayn/xv6-labs-2020/commit/28b3feefaf6132e0a30eb4c12741f35fbe1df237)
- [Jedna tabuľka stránok jadra na každý proces (ťažká)](https://github.com/s7rayn/xv6-labs-2020/commit/b3b0b9b183116abbfdaa5c59e1144182058f90c5)
- [Zjednodušte copyin/copyinstr (ťažká)](#)
- [x] [Lab traps: Trap (výnimky)](https://github.com/s7rayn/xv6-labs-2020/tree/traps)
- [Assembly architektúry RISC-V (ľahká)](https://github.com/s7rayn/xv6-labs-2020/commit/e3e9769c99ca190705ccd6b5cdd678f820761e51)
- [Backtrace (stredná)](https://github.com/s7rayn/xv6-labs-2020/commit/b7450b2e7f034c75d6587824636c29b44cbf6cb4)
- [Alarm (ťažká)](https://github.com/s7rayn/xv6-labs-2020/commit/cfa5874cab286877e8004534da0f4f316d0950b5)
- [x] [Lab lazy: Lazy allocation (lenivá alokácia)](https://github.com/s7rayn/xv6-labs-2020/tree/lazy)
- [Lenivá alokácia (stredná) # 1](https://github.com/s7rayn/xv6-labs-2020/commit/a1eb6e451c79f6ed86390bbd6a9b00e10a44059b)
- [Lenivá alokácia (stredná) # 2](https://github.com/s7rayn/xv6-labs-2020/commit/d757b0e55b1828d9c1ff7fe4f55b7a2d9870ab50)
- [Lenivá alokácia (stredná) #3](https://github.com/s7rayn/xv6-labs-2020/commit/ac33028c900a3184ce3682d222a4462a84827bfa)
- [Lazytests a Usertests (stredná) #1 - sbrk()](https://github.com/s7rayn/xv6-labs-2020/commit/c60716aafefb174a073cd503568b43b809802c50)
- [Lazytests a Usertests (stredná) #2](https://github.com/s7rayn/xv6-labs-2020/commit/233cc4dd7257418362a51226821840390a9ba8f5)
#
- [x] [Lab cow: Copy-on-write fork (COW fork)](https://github.com/s7rayn/xv6-labs-2020/tree/cow)
- [Implementácia copy-on write (ťažká)](https://github.com/s7rayn/xv6-labs-2020/commit/3859b62d17188c3086fde42a3bdc066bc08dc185)
- [x] [Lab thread: Multithreading (vlákna)](https://github.com/s7rayn/xv6-labs-2020/tree/thread)
- [Uthread: prepínanie medzi vláknami (stredná)](https://github.com/s7rayn/xv6-labs-2020/commit/d1f1f6efb6be6e861e7beaf3dc1436e0e35c8743)
- Použitie vlákien (stredná)
  - [#1 (jeden zámok)](https://github.com/s7rayn/xv6-labs-2020/commit/eb139f3e6123fd82edd83f3fb19d3d5e3114d17b)
  - [#2 (pole zámkov - buckety)](https://github.com/s7rayn/xv6-labs-2020/commit/6cd08cede601b9df4a73159837bb2e0ac9840255)
  - [#3 (pole zámkov - buckety - optimalizované)](https://github.com/s7rayn/xv6-labs-2020/commit/87705ace4e98b4bd41bf45198e83f70b4c385ac4)
- [Bariéra (stredná)](https://github.com/s7rayn/xv6-labs-2020/commit/b0572d3d3b3ac2537121934eb0379236bc1807c0)
- [x] [Lab lock: Parallelism/locking (zámky)](https://github.com/s7rayn/xv6-labs-2020/tree/lock)
- [Pamäťový alokátor (stredná)](https://github.com/s7rayn/xv6-labs-2020/commit/8cea90f8befdd4ce043cacbe56986341f3ea5b16)
- [Cache bufferov (ťažká)](https://github.com/s7rayn/xv6-labs-2020/commit/aff5f030323436fb7b127848fbda1f44d069502f)
- [x] [Lab fs: File system (súborový systém)](https://github.com/s7rayn/xv6-labs-2020/tree/fs)
- [Dvojito nepriame bloky - veľké súbory](https://github.com/s7rayn/xv6-labs-2020/commit/767c78f18614c548f75bd4ecf7729db7bcf110ea)
- [Symbolické odkazy](https://github.com/s7rayn/xv6-labs-2020/commit/5241d325c5b9fc0549a794cc4e36239fc7ca2936)
- [x] [Lab mmap: Mmap](https://github.com/s7rayn/xv6-labs-2020/tree/mmap)
- [Mmap (ťažká)](https://github.com/s7rayn/xv6-labs-2020/commit/f8116612f5b79bc9b57591744e6482893fe1f652)
