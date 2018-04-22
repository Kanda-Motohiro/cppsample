/*
 * by kanda.motohiro@gmail.com
 * released under https://creativecommons.org/publicdomain/zero/1.0/legalcode.ja
 */
#include <string>
#include <iostream>

using namespace std;

#define p(a) { cout << (a) << " at line " << __LINE__ << endl; }

int main()
{
    string a(8, 'a');
    p(a);
    const char *b = a.c_str();
    string c = a;
    string& d = a;
    c[0] = 'c';
    d[0] = 'd';
    p(c);
    p(d);
    c.assign(16, 'C');
    p(c);
}

