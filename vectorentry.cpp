/*
 * 2018.5.3 kanda.motohiro@gmail.com C++ 練習
 * released under https://creativecommons.org/publicdomain/zero/1.0/legalcode.ja
 */
#include <iostream>
#include <vector>
#include <array>
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

    vector<int> ivec;
    int i = 0x11111111;
    ivec.push_back(i);
    ivec.push_back({0x22222222});
/*
int であっても、コンテナに入るときは、 new される。
(gdb) p &ivec
$1 = (std::vector<int, std::allocator<int> > *) 0xbffff148
(gdb) x/8x 0xbffff148
0xbffff148:	0x08052e68	0x08052e70	0x08052e70
(gdb) x/8x 0x08052e68
0x8052e68:	0x11111111	0x22222222	0x00000000
 */
    array<int, 4> iarr;
    iarr[0] = i;
    iarr[1] = {0x33333333};
/*
array は、実体が入る。この場合、スタックにある。
(gdb) p &iarr
$1 = (std::array<int, 4u> *) 0xbffff134
(gdb) x/4x 0xbffff134
0xbffff134:	0x11111111	0x33333333	0xb7c18d00	0xb7fb9d2c
 */
    array<Base, 2> arr{'1', '2'};
    //array<Base, 2> arr;
    // エラー: no matching function for call to ‘Base::Base()’
    // 候補では 1 個の引数が予期されますが、0 個の引数が与えられています
    printf("%p %u\n", arr.data(), sizeof(arr));
/*
(gdb) p arr
$1 = {_M_elems = {{data = '1' <repeats 15 times>}, {data = '2' <repeats 15 times>}}}
(gdb) p &arr
$2 = (std::array<Base, 2u> *) 0xbffff114
(gdb) x/32x 0xbffff114
0xbffff114:	0x31313131	0x31313131	0x31313131	0x00313131
0xbffff124:	0x32323232	0x32323232	0x32323232	0x00323232
(gdb) p arr.size()
$3 = 2
余分な管理情報は何もないはずなのに、どこから、要素数を得るのだろう。
 */
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
