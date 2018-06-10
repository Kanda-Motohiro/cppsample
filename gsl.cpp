/*
 * 2018.5.27 kanda.motohiro@gmail.com C++ 練習
 * released under https://creativecommons.org/publicdomain/zero/1.0/legalcode.ja
 */
#include <iostream>
#define GSL_THROW_ON_CONTRACT_VIOLATION
#include <gsl/gsl>
using namespace std;
using namespace gsl;

char
func(not_null<int *> arg)
{
    try {
        return narrow<char>(*arg);
    } catch (const narrowing_error& e) {
        cout << e.what() << "\n";
    }
    return narrow_cast<char>(*arg);
}

void fail(int a)
{
    int line = 0;
    int *pline = &line;
    char *p = (char *)malloc(100);
    auto _ = finally([pline, p] { cout << *pline << "\n"; free(p); });
    if (a == 0) { line = __LINE__; return; }
    else if (a == 1) { line = __LINE__; return; }
}

int main()
{
    czstring<> s{"Hello gsl"};
    cout << s << "\n";
    span<int> a;
    int b[100];
    a = b;
    cout << a.size() << "\n";
    try {
        Expects(0==1);
    } catch (const fail_fast& e) {
        cout << e.what() << "\n";
        // GSL: Precondition failure at gsl.cpp: 31
    }
    int d = 0x1231;
    char c = func(not_null<int *>{&d});
    cout << c << "\n";
    /*char e = func(nullptr);
エラー: use of deleted function ‘gsl::not_null<T>::not_null(std::nullptr_t) 
    */
    fail(0);
    fail(1);
    fail(9);
}
