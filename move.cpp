/*
 * 2018.5.20 kanda.motohiro@gmail.com C++ 練習
 * released under https://creativecommons.org/publicdomain/zero/1.0/legalcode.ja
 */
#include "base.h"

class nodefaults {
public:
string s;
};
class unmovable {
public:
string s;
unmovable(const string a) : s(a) {}
unmovable(const unmovable& a) : s(a.s) {}
};

void sub2()
{
nodefaults a{"nodefaults"};
unmovable b{"unmovable"};
nodefaults c = move(a);
p(a.s);
unmovable d = move(b);
p(b.s);
p(sizeof(vector<string>));
}
#if 0
 at line 23
unmovable at line 25
つまり、コンパイラが暗黙的に生成する move を阻害するコンストラクタなど
を書くと、 move と書いてもコピーがされる。
move がコンパイルエラーになるわけではない。
#endif

Base sub()
{
    Base g{"g"};
    p("sub");
    return g; // ここで、 copy/move が走るはずなのだが、呼ばれない
}

int main()
{
    sub2();
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
move コンストラクタと、 move 代入が定義されていない時は、copy が使われる。

逆は、コンパイルエラーになる。
move.cpp:17:14: エラー: use of deleted function ‘Base::Base(const Base&)’
base.h:22:7: 備考: ‘Base::Base(const Base&)’ is implicitly declared as deleted because ‘Base’ declares a move constructor or move assignment operator

move.cpp:19:9: エラー: use of deleted function ‘Base& Base::operator=(const Base&)’

clang も同じ。
move.cpp:17:10: error: call to implicitly-deleted copy constructor of 'Base'
./base.h:32:5: note: copy constructor is implicitly deleted because 'Base' has a user-declared move constructor

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
