/*
 * 2018.5.2 kanda.motohiro@gmail.com C++ 練習
 * released under https://creativecommons.org/publicdomain/zero/1.0/legalcode.ja
 */
// 結局、何を引っ掛けてくれるのかよくわからない。
#define _GLIBCXX_DEBUG
#include <map>
#include "base.h"

void sub()
{
    vector<string> vec{"mado", "homu", "saya"};
    string& a{vec[0]};
    p(a);
    vec.push_back("kyo");
    vec.push_back("mami");
    parr(vec);
    // これはごみを表示して止まらない。検出されないんだ。
    //p(a);
    p(vec[5]);
/*
/usr/bin/../lib/gcc/i686-redhat-linux/6.4.1/../../../../include/c++/6.4.1/debug/vector:415:
Error: attempt to subscript container with out-of-bounds index 5, but 
container only holds 5 elements.
 */
}

int main(int argc, char *argv[])
{
    if (argc != 1) sub();
    map<string, int> m = {{"mado", 1}, {"homu", 2}};
    int& a = m["mado"];
    p(a);
    auto b = m.find("homu");
    if (b != m.end())
        p(b->second);
    parr4(m);
    m.erase("mado");
    parr4(m);
    // これは動いてしまうんだ。
    p(--a);
    m.clear();
/*
/usr/bin/../lib/gcc/i686-redhat-linux/6.4.1/../../../../include/c++/6.4.1/debug/safe_iterator.h:284:
Error: attempt to dereference a singular iterator.
 */
    p(b->second);
    parr4(m);
}
