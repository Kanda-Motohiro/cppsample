/*
 * 2018.5.20 kanda.motohiro@gmail.com C++ 練習
 * released under https://creativecommons.org/publicdomain/zero/1.0/legalcode.ja
 */
#include "base.h"

Base sub()
{
    Base g{"g"};
    p("sub");
    return g; // ここで、 copy/move が走るはずなのだが、呼ばれない
}

int main()
{
    Base a{"a"};
    Base b = a;
    Base c;
    c = a;
    Base d{move(a)};
    Base e;
    e = move(b);
    p("done");
    for (const Base *f : {&a, &b, &c, &d, &e})
        p3(f);
    p("call");
    Base g = sub();
    p("ret");
}
#if 0
./a.out
ctor-a
copy-a
def ctor
assign-a
moved a
def ctor
move-a
done at line 16
 at line 18
 at line 18
a at line 18
a at line 18
a at line 18
dtor a
dtor a
dtor a
dtor
dtor

(gdb) bt
#0  Base::operator=(Base&&) (this=0xbffff0b8,
    b=<unknown type in /home/kanda/git/cppsample/a.out, CU 0x0, DIE 0x5410>)
    at base.h:33
#1  0x08048c7c in main () at move.cpp:15

#endif
