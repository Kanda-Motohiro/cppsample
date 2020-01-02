#include "klass.h"
#include "mock.h"
extern std::shared_ptr<Klass> sub();
int main()
{
    auto out = sub();
    out->hello();
}
#if 0
[kanda@f25 cppsample]$ g++ -Wall -g -std=c++1z -O3 sub.cpp mock.cpp
[kanda@f25 cppsample]$ ./a.out
base class
[kanda@f25 cppsample]$ rm a.out
[kanda@f25 cppsample]$ g++ -Wall -g -std=c++1z -O0 sub.cpp mock.cpp
[kanda@f25 cppsample]$ ./a.out
mock

[kanda@f25 cppsample]$ g++ -Wall -g -std=c++1z -O0 sub.cpp -c
[kanda@f25 cppsample]$ g++ -Wall -g -std=c++1z -O0 mock.cpp -c
[kanda@f25 cppsample]$ objdump --disassemble --demangle  mock.o > mock.asm
[kanda@f25 cppsample]$ objdump --disassemble --demangle  sub.o > sub.asm
[kanda@f25 cppsample]$ grep make_shared *.asm | grep -v _tag
mock.asm:000000d5 <std::shared_ptr<Klass> std::make_shared<Klass>()>:
mock.asm:  e2:	e8 fc ff ff ff       	call   e3 <std::shared_ptr<Klass> std::make_shared<Klass>()+0xe>
mock.asm:  f5:	e8 fc ff ff ff       	call   f6 <std::shared_ptr<Klass> std::make_shared<Klass>()+0x21>
mock.asm: 104:	e8 fc ff ff ff       	call   105 <std::shared_ptr<Klass> std::make_shared<Klass>()+0x30>
mock.asm:セクション .text._ZSt11make_sharedI4MockJEESt10shared_ptrIT_EDpOT0_ の逆アセンブル:
mock.asm:00000000 <std::shared_ptr<Mock> std::make_shared<Mock>()>:
mock.asm:   e:	e8 fc ff ff ff       	call   f <std::shared_ptr<Mock> std::make_shared<Mock>()+0xf>
mock.asm:  21:	e8 fc ff ff ff       	call   22 <std::shared_ptr<Mock> std::make_shared<Mock>()+0x22>
mock.asm:  30:	e8 fc ff ff ff       	call   31 <std::shared_ptr<Mock> std::make_shared<Mock>()+0x31>
mock.asm:  38:	eb 1c                	jmp    56 <std::shared_ptr<Mock> std::make_shared<Mock>()+0x56>
mock.asm:  43:	e8 fc ff ff ff       	call   44 <std::shared_ptr<Mock> std::make_shared<Mock>()+0x44>
mock.asm:  51:	e8 fc ff ff ff       	call   52 <std::shared_ptr<Mock> std::make_shared<Mock>()+0x52>
sub.asm:セクション .text._ZSt11make_sharedI5KlassJEESt10shared_ptrIT_EDpOT0_ の逆アセンブル:
sub.asm:00000000 <std::shared_ptr<Klass> std::make_shared<Klass>()>:
sub.asm:   e:	e8 fc ff ff ff       	call   f <std::shared_ptr<Klass> std::make_shared<Klass>()+0xf>
sub.asm:  21:	e8 fc ff ff ff       	call   22 <std::shared_ptr<Klass> std::make_shared<Klass>()+0x22>
sub.asm:  30:	e8 fc ff ff ff       	call   31 <std::shared_ptr<Klass> std::make_shared<Klass>()+0x31>
sub.asm:  38:	eb 1c                	jmp    56 <std::shared_ptr<Klass> std::make_shared<Klass>()+0x56>
sub.asm:  43:	e8 fc ff ff ff       	call   44 <std::shared_ptr<Klass> std::make_shared<Klass>()+0x44>
sub.asm:  51:	e8 fc ff ff ff       	call   52 <std::shared_ptr<Klass> std::make_shared<Klass>()+0x52>
[kanda@f25 cppsample]$

[kanda@f25 cppsample]$ g++ -Wall -g -std=c++1z -O3 sub.cpp -c
[kanda@f25 cppsample]$ g++ -Wall -g -std=c++1z -O3 mock.cpp -c
[kanda@f25 cppsample]$ grep make_shared *.asm | grep -v _tag
mock.asm:00000000 <std::shared_ptr<Klass> std::make_shared<Klass>()>:
mock.asm:   a:	e8 fc ff ff ff       	call   b <std::shared_ptr<Klass> std::make_shared<Klass>()+0xb>
mock.asm:  3c:	74 1a                	je     58 <std::shared_ptr<Klass> std::make_shared<Klass>()+0x58>
mock.asm:  49:	74 25                	je     70 <std::shared_ptr<Klass> std::make_shared<Klass>()+0x70>
mock.asm:  91:	75 b8                	jne    4b <std::shared_ptr<Klass> std::make_shared<Klass>()+0x4b>
mock.asm:  9f:	eb aa                	jmp    4b <std::shared_ptr<Klass> std::make_shared<Klass>()+0x4b>
[kanda@f25 cppsample]$

(gdb) b std::make_shared<Klass>
Breakpoint 1 at 0x8048898: std::make_shared<Klass>. (2 locations)
(gdb) run
Starting program: /home/kanda/git/cppsample/a.out

Breakpoint 1, std::make_shared<Klass> () at mock.h:10
10	    auto out = make_shared<Mock>();
(gdb) info break
Num     Type           Disp Enb Address    What
1       breakpoint     keep y   <MULTIPLE>
	breakpoint already hit 1 time
1.1                         y     0x08048898 in std::make_shared<Klass>()
                                           at /usr/include/c++/6.4.1/bits/shared_ptr.h:636
1.2                         y     0x0804919b in std::make_shared<Klass>()
                                           at mock.h:10
(gdb)

00000000 <std::shared_ptr<Klass> std::make_shared<Klass>()>:
   0:   53                      push   %ebx
   1:   83 ec 24                sub    $0x24,%esp
   4:   8b 5c 24 2c             mov    0x2c(%esp),%ebx
   8:   6a 14                   push   $0x14
   a:   e8 fc ff ff ff          call   b <std::shared_ptr<Klass> std::make_shared<Klass>()+0xb>
   f:   8d 50 0c                lea    0xc(%eax),%edx
  12:   83 c4 10                add    $0x10,%esp
  15:   c7 40 04 01 00 00 00    movl   $0x1,0x4(%eax)
  1c:   c7 40 08 01 00 00 00    movl   $0x1,0x8(%eax)
  23:   c7 00 08 00 00 00       movl   $0x8,(%eax)
  29:   89 13                   mov    %edx,(%ebx)
  2b:   ba 00 00 00 00          mov    $0x0,%edx
  30:   c7 40 0c 08 00 00 00    movl   $0x8,0xc(%eax)
  37:   85 d2                   test   %edx,%edx
  39:   c7 40 10 77 07 00 00    movl   $0x777,0x10(%eax)

(gdb) b std::make_shared<Klass>
Breakpoint 1 at 0x8048880: file mock.h, line 9.
(gdb) run
Starting program: /home/kanda/git/cppsample/a.out
base class
[Inferior 1 (process 4456) exited normally]

(gdb) s
std::make_shared<Klass> () at sub.cpp:6
6	    auto out = std::make_shared<Klass>();
(gdb) s
std::allocate_shared<Klass, std::allocator<Klass>>(std::allocator<Klass> const&) (__a=...) at sub.cpp:6
6	    auto out = std::make_shared<Klass>();

#endif
