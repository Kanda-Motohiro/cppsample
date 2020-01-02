#include "klass.h"
extern std::shared_ptr<Klass> sub();
int main()
{
    auto out = sub();
    out->hello();
}
#if 0
[kanda@f25 cppsample]$ g++ -Wall -g -std=c++1z sub.cpp mock.cpp
[kanda@f25 cppsample]$ ./a.out
mock
#endif
