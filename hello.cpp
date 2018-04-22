/*
 * 2018.4.15 kanda.motohiro@gmail.com
 * C++ ポケットレファレンス　サンプル
 * https://github.com/cpp-pocketref/sample-code
 * を、見ながら、私が書いた練習用のコード。
 * released under https://creativecommons.org/publicdomain/zero/1.0/legalcode.ja
 */
#include <iostream>
#include <vector>
#include <array>
#include <map>
#include <list>
#include <algorithm>
#include <typeinfo>
using namespace std;

#define p(a) { cout << (a) << " at line " << __LINE__ << endl; }
#define p2(a) { cout << (a).toString() << " at line " << __LINE__ << endl; }
#define parr(a) { for (const auto &x : (a)) { cout << x << ','; } \
	cout << " at line " << __LINE__ << endl; }
#define pmap(a) { for (const auto &x : (a)) { cout << x.first << ':' << x.second << ','; } \
	cout << " at line " << __LINE__ << endl; }
#define parr2(a) { for (const auto &x : (a)) { cout << x.toString() << ','; } \
	cout << " at line " << __LINE__ << endl; }

class Base {
	string s = "null";
public:
	Base(string a) :s(a) { }
	Base() { }
	virtual const string toString() const /* final */ { return s; }
};
class Derived : public Base {
public:
	Derived(string a) :Base(a) {}
	virtual const string toString() const override { return "===" + Base::toString(); }
	int i;
	string S;
};

template <class T> struct Pair {
	T x, y; 
	Pair(T a, T b) : x(a), y(b) { p(typeid(T).name()); }
	string tostring() { return x + ":" + y; }
	string toString() { return x.toString() + ":" + y.toString(); }
};

template <typename T> T square(T a) { return a * a; }

void sub() {
	Pair<string> a("hina", "momo");
	p(a.tostring());
	Pair<Base> b(Base("mayu"), Base("cris"));
	p(b.toString());
	// c++17 Pair c(Base("mayu"), Base("cris"));
	p(square<int>(3));
	p(square<double>(5.19));
	p(square(1.41421356));
	p(__cplusplus);
	vector<string> c = { "a", "b", "c", "d" };
	vector<string>::iterator iter = c.begin();
	*iter = "A";
	p(*iter);
	p(*next(iter, 2));
	vector<string>::reverse_iterator d = c.rbegin();
	p(*d);
	p(*begin(c));
	array<int, 4> e;
	for (int i: e) { cout << i << " "; }
	array<int, 4> f = {1, 2, 3};
	for (int i: f) { cout << i << " "; }
	auto g = move(c);
	for (auto i: g) { cout << i << " "; }
	for (auto i: c) { cout << i << " "; }
	vector<string> h(g.begin(), g.end());
	vector<string> j(g.begin(), next(g.begin(), 2));
	p(h[0]);
	for (auto i: h) { cout << i << " "; }
	p(j[0]);
	parr(j);
	map<string, int> k = { {"hoe", 1}, {"fue", 2}};
	pmap(k);
	list<int64_t> m;
	m.push_front(3);
	m.push_front(4);
	m.push_back(100);
	m.push_back(200);
	parr(m);
	Base n("one");
	Base *o = new Base("two");
	vector<Base> p;
	p.push_back(n);
	p.push_back(*o);
	//p.push_back(&n);
	//p.push_back(&*o));
	//p.push_back(o);
	auto q = p.insert(p.end(), 3, n);
	p2(*q);
	q = p.insert(p.begin(), 2, Base("three"));
	p2(*q);
	parr2(p);
	//delete n;
	delete o;
	p(string("12345678").insert(3, "hoe"));
    p(g.front());
    p(g.back());
    p(g[2]);
    p(g[100]);
    try {
        auto a = g.at(100);
    } catch (out_of_range& e) {
        p(e.what());
    }
    p(g.size());
    p(size(g));
    vector<int> r(100);
    p(size(r));
    array<string, 8> s;
    p(size(s));
    p(s.size());
    for_each(g.begin(), g.end(), [](string& s) { cout << s << endl;});
    s.fill("hoe");
    parr(s)
    vector<Base> t(3);
    fill(t.begin(), t.end(), Base("moe"));
    parr2(t);
    replace(s.begin(), s.end(), string("hoe"), string("Homu"));
    parr(s)
    reverse(g.begin(), g.end());
    parr(g)
    p(count(s.begin(), s.end(), string("Homu")));
    auto u = find(g.cbegin(), g.cend(), "c");
    p(*u);
    string v("abcdefghijk");
    v.erase(v.cbegin(), next(v.cbegin(), 3));
    p(v);
    vector<int> w = { 1,2,3,4,5,6,7};
    for (auto i = w.begin(); i != w.end(); i++) {
        if (i == (w.end() - 1))
            break;
        w.erase(i);
    }
    parr(w)
    array<int, 8> x = { 1,2,3,4,5,6,7,8};
    //x.erase(x.begin() + 1, x.end() -3);
    //parr(x);
    auto y = x.begin() + 1;
    p(*y);
    p(*(next(y,2)));
    p(*(y-1));
    p(*min_element(x.begin(), x.end()));
    p(min_element(x.begin(), x.end()));
    p(*(x.data()));
    p(*(string("qwer").data()));
    p(hash<string>()("acdefg"));
}

int main() {
	sub();

	Base b("base");
	Derived d("derived");
	p(b.toString())
	p(d.toString());
	Base& c = d;
	Derived& e = dynamic_cast<Derived&>(c);
	p(c.toString());
	p(e.toString());

	Base g = d;
	Derived& h = dynamic_cast<Derived&>(c);
	p(g.toString());
	p(h.toString());

	//int i = static_cast<int>(b);
	Derived& f = static_cast<Derived&>(b);
	p(f.toString());
	p(f.i);
	//p(f.S);

	// terminate called after throwing an instance of 'std::bad_cast'
	//Derived& j = dynamic_cast<Derived&>(b);
	//p(j.toString());
	Base *k = &c;
	Derived *m = dynamic_cast<Derived *>(&c);
	p(k->toString())
	p(m->toString())
	Derived *n = dynamic_cast<Derived *>(&b);
	p(n);
	intptr_t o = reinterpret_cast<int>(&b);
	p(sizeof(o));

	Base *q = new Base(u8"hoe");
	p(q->toString());
	delete q;

	array<int, 4> ar;
	int r=0;
	for (array<int, 4>::iterator iter = ar.begin(); iter != ar.end(); iter++) {
		*iter = r++ * 100;
	}
	for (int i: ar) {
		p(i);
	}
	Base *s = new Base;
	Base *t = new Base("t");
	p(s->toString());
	p(t->toString());
	Base *u = new Base();
	//Base x = new Base();
	class X {
		string x;
	//private	string y;
	public:
		X(const char *a) { x = a; }
		string toString() { return x; }
	};
	X x("mado");
	X y = "homu";
	p(x.toString());
	p(y.toString());
	array<string, 4> z{"saya", "mami", "kyo"};
	for (string s: z) { p(s); }
	//p(z.value_type);

	p("-------------------------------------");
	p(int('0'));
	p(char(40));

	p(R"(Hello, \nWorl
d)");
	int i = 0;
	vector<string> w(4);
	for (vector<string>::iterator iter = w.begin(); iter != w.end(); iter++) {
		*iter = "aaa";
	}
	for (auto v : w) v = "bbb";

	for (vector<string>::const_iterator iter = w.begin(); iter != w.end(); iter++) {
		p(*iter);
	}
	for (auto v : w) p(v);


	vector<int> v;
	v.push_back(1);
	v.push_back(3);
	//for (vector<int>::iterator iter = v.begin(); iter != v.end(); iter++) {
	for (auto iter = v.begin(); iter != v.end(); iter++) {
		p(*iter);
	}
}

