/*
 * 2018.5.23 kanda.motohiro@gmail.com C++ 練習
 * released under https://creativecommons.org/publicdomain/zero/1.0/legalcode.ja
 */
#include "base.h"
#include <tuple>
using namespace std;

tuple<string, int> func()
{
    return {"hello", 0};
}
// needs gcc7 or clang4
int main()
{
    auto [a, b] = func();
    p(a);
    auto c = func();
    p(get<0>(c));
    tie(d,e) = func();
    p(d);
}
