/*
 * 2018.4.21 kanda.motohiro@gmail.com
 * C++ 練習
 * released under https://creativecommons.org/publicdomain/zero/1.0/legalcode.ja
 */
#include <iostream>
#include <vector>
using namespace std;

#define p(a) { cout << (a) << " at line " << __LINE__ << endl; }
#define p2(a) { cout << (a).toString() << " at line " << __LINE__ << endl; }
#define parr2(a) { for (const auto &x : (a)) { cout << x.toString() << ','; } \
        cout << " at line " << __LINE__ << endl; }
#define parr3(a) { for (const auto &x : (a)) { cout << x->toString() << ','; } \
        cout << " at line " << __LINE__ << endl; }


class Base {
public:
    string s = "null";
    Base() { cout << "def ctor" << endl; }
    Base(string a) :s(a) { cout << "ctor-" << a << endl; }
    Base& operator=(const Base& b) { s = b.s;
    cout << "assign-" << b.s << endl;
    return *this; }
    Base(const Base& b) :s(b.s) { cout << "copy-" << b.s << endl; }
    Base(Base&& b) :s(b.s) { b.s = "";
    cout << "moved " << s << endl;
    }
    virtual ~Base() { cout << "destructor " << s << endl; }
    virtual const string toString() const { return s; }
};

class Base2 {
public:
    string s = "null";
    Base2() { cout << "def ctor" << endl; }
    Base2(string a) :s(a) { cout << "ctor-" << a << endl; }
    Base2& operator=(const Base2& b) { s = b.s;
    cout << "assign-" << b.s << endl;
    return *this; }
    Base2(const Base2& b) :s(b.s) { cout << "copy-" << b.s << endl; }
    //Base2(Base2&& b) :s(b.s) { b.s = "";
    //cout << "moved " << s << endl; }
    virtual ~Base2() { cout << "destructor " << s << endl; }
    virtual const string toString() const { return s; }
};

class Composit {
public:
    Base b;
    Composit(string s) { b = Base(s); }
    ~Composit() { cout << "composit-destructor " << b.s << endl; }
    const string toString() const { return b.s; }
};

template <class T>
T __attribute__((noinline)) func(string s) { T h(s);
p2(h);
return h; }

Base2 func2(string s) {
Base2 a(s); // 実体はスタックなので、ctor, copy-ctor, dtor が呼ばれるはず？
return a; }

int main()
{
    auto a = Base("a");
    p2(a);
    vector<Base> vec = { Base("b"), Base("c") };
    parr2(vec);
    vec[0].s = "B";
    parr2(vec);
    p("----iter----");
    // この書き方だと、毎回、オブジェクトの生成消滅が起きるわけだ。
    for (auto i: vec) { p2(i); }
    for (auto& i: vec) { p2(i); }

    for (auto i: vec) { i.s = "modified"; }
    parr2(vec);
    for (auto& i: vec) { i.s = "modified"; }
    parr2(vec);
    p("----end iter----");

    vector<Base*> ved = { new Base("d"), new Base("e") };
    parr3(ved);
    ved[0]->s = "D";
    parr3(ved);

    auto f = Composit("f");

    auto g = move(a);
    p2(a);
    p2(g);

    Base h = func<Base>("h");
    p2(h);
    Base2 i = func<Base2>("i");
    p2(i);
    Base2 j = func2("j");
    p2(j);
    p("---- end of scope ----");
}

