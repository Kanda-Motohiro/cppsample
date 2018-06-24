/*
 * 2018.6.24 kanda.motohiro@gmail.com
 * C++ 練習
 * released under https://creativecommons.org/publicdomain/zero/1.0/legalcode.ja
 */
#include <iostream>
#include <vector>
using namespace std;

#define p(a) { cout << (a) << " at line " << __LINE__ << endl; }

template<typename T> auto add(T a0, T a1) -> T
{
    T sum = a0 + a1;
    return sum;
}

int main()
{
    auto a = add<int>(1, 2);
    p(a);
    auto b = add(string{"aaa"}, string{"bbb"});
    p(b);
    //auto c = add(vector<int>{1}, vector<int>{2});
}
#if 0
(gdb) b add
Function "add" not defined.
Make breakpoint pending on future shared library load? (y or [n]) n
(gdb) b _Z3addIiET_S0_S0_
Breakpoint 1 at 0x8048d27: file template.cpp, line 14.
(gdb) b _Z3addINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEET_S6_S6_
Breakpoint 2 at 0x8048d3d: file template.cpp, line 14.
(gdb) run

Breakpoint 1, add<int> (a0=1, a1=2) at template.cpp:14
14	    T sum = a0 + a1;
(gdb) n
15	    return sum;
(gdb) bt
#0  add<int> (a0=1, a1=2) at template.cpp:15
#1  0x08048b09 in main () at template.cpp:20
(gdb) c
Continuing.
3 at line 21

Breakpoint 2, add<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > (a0="aaa", a1="bbb") at template.cpp:14
14	    T sum = a0 + a1;
(gdb) bt
#0  add<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > (a0="aaa", a1="bbb") at template.cpp:14
#1  0x08048bb5 in main () at template.cpp:22
(gdb) c
Continuing.
aaabbb at line 23

$ nm --demangle a.out | grep add
08048d37 W std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > add<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >)
08048d21 W int add<int>(int, int)

(gdb) b *0x08048d21
Breakpoint 1 at 0x8048d21: file template.cpp, line 12.
(gdb) run

Breakpoint 1, add<int> (a0=1, a1=2) at template.cpp:12
12	template<typename T> auto add(T a0, T a1) -> T
(gdb) n
14	    T sum = a0 + a1;
(gdb) b *0x08048d37
Breakpoint 2 at 0x8048d37: file template.cpp, line 12.
(gdb) c
Continuing.
3 at line 21

Breakpoint 2, add<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > (a0="aaa", a1="bbb") at template.cpp:12
12	template<typename T> auto add(T a0, T a1) -> T

(gdb) b add<int>
Breakpoint 1 at 0x8048d27: file template.cpp, line 14.
賢い。

(gdb) b add<std::string>
Function "add<std::string>" not defined.
basic_string なんとか、と書かないといけないのだろう。
#endif
