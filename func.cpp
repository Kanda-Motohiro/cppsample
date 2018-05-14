/*
 * 2018.5.14 kanda.motohiro@gmail.com C++ 練習
 * released under https://creativecommons.org/publicdomain/zero/1.0/legalcode.ja
 */
#include "base.h"

base func()
{
    base a{'a'};
    printf("%p %u %c\n", &a, sizeof(a), a.data[0]);
    // memcpy でも動くかと思ったが、コール元の領域にいきなり、作成するみたい。
    return a;
}

int main()
{
    base b = func();
    printf("%p %u %c\n", &b, sizeof(b), b.data[0]);
}
#if 0
そもそも、レジスタに入らないものを関数戻り値で返すってどうやるのだっけ。
Dump of assembler code for function main():
   0x08048836 <+0>:	lea    0x4(%esp),%ecx

   0x08048847 <+17>:	lea    -0x1c(%ebp),%eax
   0x0804884d <+23>:	push   %eax # ここに戻せと、コール元が指示する。
   0x0804884e <+24>:	call   0x80487fb <func()>

Dump of assembler code for function func():
   0x080487fb <+0>:	push   %ebp
   0x08048804 <+9>:	push   $0x61
   0x08048806 <+11>:	pushl  0x8(%ebp)
   0x08048809 <+14>:	call   0x80488da <base::base(char)>

0xbffff18c 20 a

(gdb) p/x $eax
$3 = 0xbffff18c

(gdb) p/x &a
$5 = 0xbffff18c
(gdb) x/8x 0xbffff18c
0xbffff18c:	0x08048a28	0x61616161	0x61616161	0x61616161
0xbffff19c:	0x00616161	0xb7dbd3bc	0xbffff1c0	0x00000000
(gdb) p/x $ebp-0x1c
$7 = 0xbffff18c

もらうものの大きさは、コール元でわかるから、フレームに場所を確保する。
つまり、 ebp-sizeof(base) を渡して、そこに書き込んでもらう。
#endif
