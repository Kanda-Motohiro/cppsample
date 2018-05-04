/*
 * 2018.5.4 kanda.motohiro@gmail.com C++ 練習
 * released under https://creativecommons.org/publicdomain/zero/1.0/legalcode.ja
 */
#include <iostream>
#include <atomic>
using namespace std;

int main()
{
    atomic<int> x{0};
    // -O2 でビルドして、objdump -S した結果。
    // 8:	c7 44 24 0c 00 00 00 	movl   $0x0,0xc(%esp)
    x.store(1, memory_order_seq_cst);
    // 3:	b8 01 00 00 00       	mov    $0x1,%eax
    // 10:	87 44 24 0c          	xchg   %eax,0xc(%esp)
    int y = x.load(memory_order_seq_cst);
    // 14:	8b 44 24 0c          	mov    0xc(%esp),%eax
    atomic_thread_fence(memory_order_seq_cst);
    // 18:	f0 83 0c 24 00       	lock orl $0x0,(%esp)
    x += y;
    // 1d:	f0 01 44 24 0c       	lock add %eax,0xc(%esp)

    x.store(9, memory_order_relaxed);
    // 22:	c7 44 24 0c 09 00 00 	movl   $0x9,0xc(%esp)
    y = x.load(memory_order_relaxed);
    // このへんは、何も展開されない。
    atomic_thread_fence(memory_order_relaxed);

    atomic_thread_fence(memory_order_consume);
    atomic_thread_fence(memory_order_acquire);
    atomic_thread_fence(memory_order_release);
    atomic_thread_fence(memory_order_acq_rel);
/*
-O0 で展開するとこうなる。x86 のメモリモデルに
関係なく、 lock で同期するみたい。 enum をスタックに覚えている？
  df:	f0 83 0c 24 00       	lock orl $0x0,(%esp)
  e4:	c7 45 e4 01 00 00 00 	movl   $0x1,-0x1c(%ebp)
  eb:	f0 83 0c 24 00       	lock orl $0x0,(%esp)
  f0:	c7 45 e8 02 00 00 00 	movl   $0x2,-0x18(%ebp)
  f7:	f0 83 0c 24 00       	lock orl $0x0,(%esp)
  fc:	c7 45 ec 03 00 00 00 	movl   $0x3,-0x14(%ebp)
 103:	f0 83 0c 24 00       	lock orl $0x0,(%esp)
 108:	c7 45 f0 04 00 00 00 	movl   $0x4,-0x10(%ebp)
 10f:	f0 83 0c 24 00       	lock orl $0x0,(%esp)
*/
    return 5;
}
