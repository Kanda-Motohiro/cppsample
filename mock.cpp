#include "klass.h"
#include "mock.h"
extern std::shared_ptr<Klass> sub();
int main()
{
    auto out = sub();
    out->hello();
}
#if 0
[kanda@f25 cppsample]$ g++ -Wall -g -std=c++1z -O3 sub.cpp mock.cpp
[kanda@f25 cppsample]$ ./a.out
base class
[kanda@f25 cppsample]$ rm a.out
[kanda@f25 cppsample]$ g++ -Wall -g -std=c++1z -O0 sub.cpp mock.cpp
[kanda@f25 cppsample]$ ./a.out
mock
#endif
