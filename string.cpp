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
    const char *f = a.c_str();
    printf("%p %u %u %p\n", &a, sizeof(a), a.size(), f);
    a += "bbbbbbbb";
    const char *g = a.c_str();
/*
0xbffff148 24 8
17	    a += "bbbbbbbb";
(gdb) x/8x 0xbffff148
0xbffff148:	0xbffff150	0x00000008	0x61616161	0x61616161
短い文字列は、 string 実体に、今の場合スタックに置かれる。

(gdb) x/8x 0xbffff148
0xbffff148:	0x08051e18	0x00000010	0x0000001e	0x61616161
(gdb) x/8x 0x08051e18
0x8051e18:	0x61616161	0x61616161	0x62626262	0x62626262
長くなると、ヒープに移る。

(gdb) n
0xbffff130 24 64
e は最初からヒープにある。
(gdb) x/4x 0xbffff130
0xbffff130:	0x08051e40	0x00000040	0x00000040	0xb7c18d00
(gdb) x/4x 0x08051e40
0x8051e40:	0x30303030	0x30303030	0x30303030	0x30303030
 */
    string e(64, '0');
    printf("%p %u %u\n", &e, sizeof(e), e.size());

    const char *b = a.c_str();
    string c = a;
    string& d = a;
    c[0] = 'c';
    d[0] = 'd';
    p(c);
    p(d);
    c.assign(16, 'C');
    p(c);

    p(to_string(stoi("1234")));
    p(int("123"));
    //p(string(123));
}

