/*
 * 2018.5.6 kanda.motohiro@gmail.com C++ 練習
 * released under https://creativecommons.org/publicdomain/zero/1.0/legalcode.ja
 */
#include "base.h"
#include <locale>

class Derived: public base {
    int i = 0xdddddddd;
public:
    Derived(char a) : base(a) {}
    const string toString() const override {
        string s = base::toString();
        return "==" + s;
    }
};

int main()
{
    p(locale{""}.name());
    // ja_JP.utf8 at line 19

    Derived d('1');
    base *pb = &d;
    printf("base=%p %u derived=%p %u\n", pb, sizeof(base), &d, sizeof(d)); 
    cout << pb->toString();
}
#if 0
base=0xbffff150 20 derived=0xbffff150 24

Breakpoint 1, base::toString[abi:cxx11]() const (this=0xbffff150) at base.h:49
49	    virtual const string toString() const { return data; }
(gdb) x/8x 0xbffff150
0xbffff150:	0x08049254	0x31313131	0x31313131	0x31313131 # vtbl base::data
0xbffff160:	0x00313131	0xdddddddd # Derived::i

(gdb) bt
#0  base::toString[abi:cxx11]() const (this=0xbffff150) at base.h:49
#1  0x08049099 in Derived::toString[abi:cxx11]() const (this=0xbffff150) at vtbl.cpp:13
#2  0x08048eab in main () at vtbl.cpp:26

(gdb) x/4x 0x08049254
0x8049254 <_ZTV7Derived+8>:	0x08049082	0x00000000

(gdb) p pb->toString
$6 = {const std::__cxx11::string (const base * const)} 0x8048fe4 <base::toString[abi:cxx11]() const>
(gdb) p d.toString
$7 = {const std::__cxx11::string (const Derived * const)} 0x8049082 <Derived::toString[abi:cxx11]() const>

vtbl に入っているのは後者。でも、pb->toString をデバッガで見た結果が、
base のメンバ関数になっているのはなぜ。
#endif
