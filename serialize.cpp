/*
 * 2018.5.2 kanda.motohiro@gmail.com C++ 練習
 * released under https://creativecommons.org/publicdomain/zero/1.0/legalcode.ja
 * Based on tutorial at
 * https://www.boost.org/doc/libs/1_67_0/libs/serialization/doc/index.html
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
using namespace std;

class Base {
    string s;
    int i;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & s;
        ar & i;
    }
public:
    Base(string a, int b) : s(a), i(b) { }
    Base() {}
    const string toString() { return s + to_string(i); }
};

int main(int argc, char *argv[])
{
    if (argc == 1) {
        Base a{"a", 0x0a};
        Base b{"b", 0x0b};
        vector<Base> vec{a, b};
        
        boost::archive::text_oarchive oa(cout);
        oa << vec;
    } else {
        string path = argv[1];
        istream is{0};
        if (path[0] == '/')
            is.rdbuf(ifstream(path).rdbuf());
        else
            is.rdbuf(cin.rdbuf());
        boost::archive::text_iarchive ia(is);
        vector<Base> vec;
        ia >> vec;
        for (Base& a: vec) { cout << a.toString() << endl; }
    }
}
