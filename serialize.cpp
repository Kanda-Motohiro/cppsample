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
    string path;
    if (argc == 3)
        path = argv[2];
    if (argc <= 2 || strcmp(argv[1], "out") == 0) {
        Base a{"a", 0x0a};
        Base b{"b", 0x0b};
        vector<Base> vec{a, b};
        
        ostream os{0};
        if (path.size())
            os.rdbuf(ofstream(path).rdbuf());
        else
            os.rdbuf(cout.rdbuf());
        boost::archive::text_oarchive oa(os);
        oa << vec;
    } else {
        istream is{0};
        if (path.size())
            is.rdbuf(ifstream(path).rdbuf());
        else
            is.rdbuf(cin.rdbuf());
        boost::archive::text_iarchive ia(is);
        vector<Base> vec;
        ia >> vec;
        for (Base& a: vec) { cout << a.toString() << endl; }
    }
}
