/*
 * 2018.5.2 kanda.motohiro@gmail.com C++ 練習
 * released under https://creativecommons.org/publicdomain/zero/1.0/legalcode.ja
 */
// 結局、何を引っ掛けてくれるのかよくわからない。
#define _GLIBCXX_DEBUG
#include <map>
#include <string.h>
#include "base.h"

void asan(int argc)
{
    char name[4];

    if (argc == 3)
        strcpy(name, "12345");
    else if (argc == 4)
        free(name);
    else if (argc == 5)
        strcpy(name - 2, "1234");
    else if (argc == 6) {
    const char *s;
    { s = string{"hina"}.c_str();
        p(s);
    }
    p(s); // 落ちない。
    }
    else if (argc == 7) {
        char *s = (char *)malloc(128);
        strcpy(s, "momo");
        // leak not supported on i386.
    }
    else { printf("unknown %d args", argc); }
    exit(0);
}

void sub()
{
    vector<string> vec{"mado", "homu", "saya"};
    string& a{vec[0]};
    p(a);
    vec.push_back("kyo");
    vec.push_back("mami");
    parr(vec);
    // これはごみを表示して止まらない。検出されないんだ。
    // ==2862==ERROR: AddressSanitizer: heap-use-after-free
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
    if (argc == 2) sub();
    else if (argc != 1) asan(argc);
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
    // ==2822==ERROR: AddressSanitizer: heap-use-after-free
    // サニタイザをかけると検出した。
    //p(--a);
    m.clear();
/*
/usr/bin/../lib/gcc/i686-redhat-linux/6.4.1/../../../../include/c++/6.4.1/debug/safe_iterator.h:284:
Error: attempt to dereference a singular iterator.
 */
    p(b->second);
    parr4(m);
}
