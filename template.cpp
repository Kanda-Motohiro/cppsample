/*
 * 2018.9.8 kanda.motohiro@gmail.com C++ 練習
 * released under https://creativecommons.org/publicdomain/zero/1.0/legalcode.ja
 */
//#include "base.h"
#include <type_traits>
#include <tuple>
#include <assert.h>
#include <string.h>
#include <stdio.h>

class Base {
public:
virtual ~Base() {}
};

template<typename T>
T Double(T a)
{
    static_assert(std::is_integral<T>::value);
    //assert(is_integral<T>::value); // ランタイムにも使える。
    return a+a;
}

template<typename T>
void copy(T* p, const T* q, int n)
{
    if (std::is_pod<T>::value)
        memcpy(p, q, n*sizeof(T));
    else
        for (int i=0; i!=n; i++)
            p[i] = q[i];
}

namespace std {
template<bool C, typename T, typename F>
struct Conditional {
    using type = T;
};

template<typename T, typename F>
struct Conditional<false,T,F> {
    using type = F;
};
}

template<typename T>
class K {
public:
    T body;
    typename std::Conditional<std::is_pod<T>::value, int, char>::type size;
};

template<int N>
constexpr int fac() { return N*fac<N-1>(); }
template<>
constexpr int fac<1>() { return 1; }


int main()
{
{
    std::tuple<int, std::string, Base> t{3, "hello", Base{}};
    int i = std::get<0>(t);
    std::string s;
    Base b;
    std::tie(i, s, b) = t;
    auto [j, k, l] = t;
}

    constexpr int x5 = fac<5>();
    K<int> kint;
    K<Base> kbase;

    printf("kint.size=%d kbase.size=%d\n", sizeof(kint.size), sizeof(kbase.size));

//static_assert(std::is_pod<Base>::value);
    constexpr int n = 32;
    int b[n];
    int c[n];
    Base d[n];
    Base e[n];

    copy(b, c, n);
    copy(d, e, n);

    (void)Double<int>(1);
    /*
    p(b);
    float c = 3.14;
    float d = Double<float>(c);
    p(d);
    Base e;
    auto b = Double<Base>(Base()); // error
    */
}
#if 0
template.cpp: In instantiation of ‘T Double(T) [with T = Base]’:
template.cpp:20:28:   required from here
template.cpp:9:11: エラー: no match for ‘operator+’ (operand types are ‘Base’ and ‘Base’)
 { return a+a; }
          ~^~
template.cpp: In instantiation of ‘T Double(T) [with T = float]’:
template.cpp:20:30:   required from here
template.cpp:10:5: エラー: static assertion failed
     static_assert(is_integral<T>::value);
     ^~~~~~~~~~~~~


#endif
