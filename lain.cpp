/*
 * 2018.8.22 kanda.motohiro@gmail.com C++ 練習
 * released under https://creativecommons.org/publicdomain/zero/1.0/legalcode.ja
 */
#include <iostream>
using namespace std;

class Base {
public:
    Base() { cout << "before main\n"; }
};

Base b;

int main()
{
    cout << "Hello World\n";
}
#if 0
[kanda@f25 cppsample]$ ./a.out
before main
Hello World

(gdb) bt
#0  Base::Base (this=0x804a0cd <b>) at lain.cpp:10
#1  0x080486aa in __static_initialization_and_destruction_0 (__initialize_p=1, 
    __priority=65535) at lain.cpp:13
#2  0x080486c5 in _GLOBAL__sub_I_b () at lain.cpp:18
#3  0x0804873b in __libc_csu_init ()
#4  0xb7bfe166 in __libc_start_main (main=0x804862b <main()>, argc=1, 
    argv=0xbffff254, init=0x80486f0 <__libc_csu_init>, 
    fini=0x8048750 <__libc_csu_fini>, rtld_fini=0xb7fe98f0 <_dl_fini>, 
    stack_end=0xbffff24c) at ../csu/libc-start.c:245
#5  0x08048541 in _start ()
(gdb) c
Continuing.
before main

Breakpoint 2, main () at lain.cpp:17
17	    cout << "Hello World\n";
(gdb) bt
#0  main () at lain.cpp:17
#endif
