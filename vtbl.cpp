/*
 * 2018.5.6 kanda.motohiro@gmail.com C++ 練習
 * released under https://creativecommons.org/publicdomain/zero/1.0/legalcode.ja
 */
#include "base.h"
#include <locale>

class Derived: public base {
public:
    int i = 0xdddddddd;
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
    cout << pb->toString() << endl;

    Derived *pd = static_cast<Derived *>(pb);
    pd->i+= 7;
    pd = dynamic_cast<Derived *>(pb);
    pd->i-= 5;
    Base *bad = dynamic_cast<Base *>(pb);
    p(bad);
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
(gdb) x/i 0x08049082
   0x08049082 <Derived::toString[abi:cxx11]() const>:	push   %ebp

(gdb) p pb->toString
$6 = {const std::__cxx11::string (const base * const)} 0x8048fe4 <base::toString[abi:cxx11]() const>
(gdb) p d.toString
$7 = {const std::__cxx11::string (const Derived * const)} 0x8049082 <Derived::toString[abi:cxx11]() const>

vtbl に入っているのは後者。でも、pb->toString をデバッガで見た結果が、
base のメンバ関数になっているのはなぜ。


    Derived *pd = static_cast<Derived *>(pb);
    pd->i+= 7;
    pd = dynamic_cast<Derived *>(pb);
    pd->i-= 5;

static_cast は、実行コードは無い。
(gdb) x/16i $eip
=> 0x8048cd7 <main()+268>:	addl   $0x7,-0x40(%ebp)
   0x8048cdb <main()+272>:	push   $0x0
   0x8048cdd <main()+274>:	push   $0x8048fe8 # なんだこれ
   0x8048ce2 <main()+279>:	push   $0x8048fd4
   0x8048ce7 <main()+284>:	lea    -0x54(%ebp),%eax
   0x8048cea <main()+287>:	push   %eax
   0x8048ceb <main()+288>:	call   0x8048a00 <__dynamic_cast@plt>
   0x8048cf0 <main()+293>:	add    $0x10,%esp
   0x8048cf3 <main()+296>:	subl   $0x5,0x14(%eax)

キャスト元先の型情報らしい。
(gdb) x/4x 0x8048fe8
0x8048fe8 <_ZTI7Derived>:	0x0804b154	0x08048fdc	0x08048fd4	0x00000000
(gdb) x/4x 0x8048fd4
0x8048fd4 <_ZTI4base>:	0x0804b088	0x08048fcc	0x72654437	0x64657669
(gdb) p/x $eax
$4 = 0xbffff154
(gdb) info locals
pb = 0xbffff154
#endif
