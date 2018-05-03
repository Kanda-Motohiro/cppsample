/*
 * 2018.5.3 kanda.motohiro@gmail.com C++ 練習
 * released under https://creativecommons.org/publicdomain/zero/1.0/legalcode.ja
 */
#include <iostream>
#include <vector>
#include <memory.h>
using namespace std;

constexpr size_t SIZE = 16;
class Base {
public:
    char data[SIZE];
    Base(char a) { memset(data, a, SIZE -1); data[SIZE - 1] = 0; }
};

int main()
{
    vector<Base> vec;
    Base a{'a'};
    Base b{'b'};
    vec.push_back(a);
    vec.push_back(b);
    char *p = (char *)malloc(SIZE);
    memset(p, 'c', SIZE);
    printf("vec=%p %u a=%p b=%p p=%p\n", &vec, sizeof(vec), &a, &b, p);

    for (vector<Base>::const_iterator iter = vec.begin(); iter != vec.end(); iter++) {
        printf("%p %s\n", &(*iter),(*iter).data);
    }
    vec.pop_back();

    for (Base c: vec) {
        c.data[0] = 'C';
        printf("%p %s\n", &c, c.data);
    }
    for (Base& c: vec) {
        c.data[1] = 'D';
        printf("%p %s\n", &c, c.data);
    }

    return 0;
}
#if 0
0xbfff がスタックで、0x8051 がヒープ。
vec=0xbffff184 12 a=0xbffff174 b=0xbffff164 p=0x8051a10
(gdb) p/x $esp
$1 = 0xbffff160

(gdb) x/32x 0xbffff164
0xbffff164:	0x62626262	0x62626262	0x62626262	0x00626262 # b on stack
0xbffff174:	0x61616161	0x61616161	0x61616161	0x00616161 # a
0xbffff184:	0x08051a28	0x08051a48	0x08051a48 # vec on stack

vec は、１２バイトで、ヒープへのポインタが３つ。
(gdb) x/32x 0x8051a10
0x8051a10:	0x63636363	0x63636363	0x63636363	0x63636363 # p
0x8051a20:	0x00000000	0x00000029	0x61616161	0x61616161 # a on heap
0x8051a30:	0x61616161	0x00616161	0x62626262	0x62626262 # b
0x8051a40:	0x62626262	0x00626262	0x00000000	0x00000409

これで明らかなように、 vector.push_back は、引数を new してアドレスを持つ。
0x8051a28 aaaaaaaaaaaaaaa
0x8051a38 bbbbbbbbbbbbbbb

pop_back したあと。別のセッションなので、アドレスは変わっている。
0xbffff184:	0x08051a28	0x08051a38	0x08051a48

0x8051a28:	0x00000000	0x61616161	0x61616161	0x00616161 # 捨てたエントリ
0x8051a38:	0x62626262	0x62626262	0x62626262	0x00626262

0xbfe8ea14 Caaaaaaaaaaaaaa # これはスタックに複写された実体を見ている。
0x8e75a28 aDaaaaaaaaaaaaa # これは、vector が持っているヒープを見ている。
前者に行った変更は、後者には反映されないことにも注意。
#endif
