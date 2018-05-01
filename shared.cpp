/*
 * 2018.5.1 kanda.motohiro@gmail.com C++ 練習
 * released under https://creativecommons.org/publicdomain/zero/1.0/legalcode.ja
 */
#include "base.h"

int main()
{
    shared_ptr<Base> a(new Base{"a"});
    p3(a);
    { shared_ptr<Base> b{a};
        p(b.use_count());
    }
    p("---- end of scope ----");
}
