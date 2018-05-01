/*
 * 2018.5.1 kanda.motohiro@gmail.com C++ 練習
 * released under https://creativecommons.org/publicdomain/zero/1.0/legalcode.ja
 */
#include "base.h"

class Kls {
public:
    string s;
    //Kls(string a) { s = a; }
    Kls& operator=(const Kls& a) { s=a.s; cout << "assign-" << s << endl; return *this; }
    //Kls& operator=(Kls&& a) { s=a.s; cout << "move-" << s << endl; a.s=""; return *this; }
    //~Kls() {}
};

int main()
{
    Kls a;
    a.s = "a";
    Kls b{a};
    Kls c; c = a;
    Kls d = move(a);
    p(a.s);
    {
    Base a;
    a.s = "A";
    Base b{a};
    Base c; c = a;
    Base d = move(a);
    }
}
