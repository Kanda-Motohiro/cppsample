/*
 * 2018.5.1 kanda.motohiro@gmail.com C++ 練習
 * released under https://creativecommons.org/publicdomain/zero/1.0/legalcode.ja
 */
#include <iostream>
#include <vector>
#include <memory>
using namespace std;

#define p(a) { cout << (a) << " at line " << __LINE__ << endl; }
#define p2(a) { cout << (a).toString() << " at line " << __LINE__ << endl; }
#define p3(a) { cout << (a)->toString() << " at line " << __LINE__ << endl; }
#define parr(a) { for (const auto &x : (a)) { cout << x << ','; } \
    cout << " at line " << __LINE__ << endl; }
#define parr2(a) { for (const auto &x : (a)) { cout << x.toString() << ','; } \
        cout << " at line " << __LINE__ << endl; }
#define parr3(a) { for (const auto &x : (a)) { cout << x->toString() << ','; } \
        cout << " at line " << __LINE__ << endl; }
#define parr4(a) { for (const auto &x : (a)) { cout << x.first << ":" << x.second << ','; } \
    cout << " at line " << __LINE__ << endl; }

class Base {
public:
    string s = "null";
    Base() { cout << "def ctor" << endl; }
    Base(string a) :s(a) { cout << "ctor-" << a << endl; }
    // copy ctor
    Base(const Base& b) :s(b.s) { cout << "copy-" << b.s << endl; }
    Base& operator=(const Base& b) { s = b.s; cout << "assign-" << b.s << endl; return *this; }

    // move ctor
    Base(Base&& b) :s(b.s) { b.s = ""; cout << "moved " << s << endl; }
    Base& operator=(Base&& b) { s = b.s; b.s = ""; cout << "move-" << s << endl; return *this; }

    // なんで、これが使われることがある？
    //Base(Base& b) :s(b.s) { cout << "Xcopy-" << b.s << endl; }
    //Base& operator=(Base& b) { s = b.s; cout << "Xassign-" << b.s << endl; return *this; }

    virtual ~Base() { cout << "dtor " << s << endl; }
    virtual const string toString() const { return s; }
};

