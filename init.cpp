/*
 * 2018.5.5 kanda.motohiro@gmail.com C++ 練習
 * released under https://creativecommons.org/publicdomain/zero/1.0/legalcode.ja
 */
#include "base.h"

int main()
{
    Base c{"c"};
    for (int i=0; i<2; i++) {
        Base a{"a"};
        Base b;
        b.s = "b";
        a.s += "0";
        b.s += "1";
        c.s += "2";
        p2(a);
        p2(b);
        p2(c);
        // for ループ内の変数は回るたびに、 ctor, dtor が呼ばれる。
    }
    p("=============");
}
#if 0
./a.out
ctor-c
ctor-a
def ctor
a0 at line 17
b1 at line 18
c2 at line 19
dtor b1
dtor a0
ctor-a
def ctor
a0 at line 17
b1 at line 18
c22 at line 19
dtor b1
dtor a0
============= at line 21
dtor c22
#endif
