/*
 * 2018.5.3 kanda.motohiro@gmail.com C++ 練習
 * released under https://creativecommons.org/publicdomain/zero/1.0/legalcode.ja
 * Based on sample code at
 * https://www.boost.org/doc/libs/1_67_0/libs/format/doc/format.html
 * https://www.boost.org/doc/libs/1_67_0/doc/html/string_algo/usage.html
 */
#include "base.h"
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
using namespace std;

int main(int argc, char *argv[])
{
    int a = 123;
    double b = 3.14;
    string c{"momo"};

    // インラインのフォーマット文字列構築
    string d = (boost::format("a=%d pi=%f Hello, %s") % a % b %c).str();
    p(d);
    p(boost::format("a=%2% c=%1%") % c % a);

    // 全てを置換
    const string s{"abcd1234aabb. Hello, momo. Bye, momo."};
    p(boost::algorithm::replace_all_copy(s, "a", "A"));
    p(boost::algorithm::replace_all_copy(s, "momo", "hina"));

    // trim==strip, split, join
    p(boost::algorithm::trim_copy(string{"           --              "}));
    vector<string> e;
    boost::algorithm::split(e, s, boost::algorithm::is_any_of(" "));
    parr(e);
    p(boost::algorithm::join(e, "#"));

    // startswith
    p(boost::algorithm::starts_with(s, "abc"));
    p(boost::algorithm::starts_with(s, "abcde"));
    p(boost::algorithm::contains(s, "momo. "));
    // boost すごい。他の言語にあって C++ に無い文字列操作が全部ある。  
}
