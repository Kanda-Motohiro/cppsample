/*
 * 2018.5.4 kanda.motohiro@gmail.com C++ 練習
 * released under https://creativecommons.org/publicdomain/zero/1.0/legalcode.ja
 */
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
using namespace std;

mutex m;

void worker()
{
    this_thread::sleep_for(chrono::seconds{3});
    cout << this_thread::get_id() << " started" << endl;
    m.lock();
    cout << this_thread::get_id() << " got lock" << endl;
    this_thread::sleep_for(chrono::seconds{10});
    m.unlock();
}

int main()
{
    vector<thread> vec(4);
    for (size_t i=0; i<vec.size(); i++) {
        vec[i] = thread(worker);
    }
    this_thread::sleep_for(chrono::seconds{3});
    for (size_t i=0; i<vec.size(); i++) {
        vec[i].join();
    }
}
#if 0
linux では、 futex になる。
(gdb) bt
#0  __lll_lock_wait () at ../sysdeps/unix/sysv/linux/i386/lowlevellock.S:140
#1  0xb7fa6b2e in __GI___pthread_mutex_lock (mutex=0x804d15c <m>) at ../nptl/pthread_mutex_lock.c:80
#2  0x08048d62 in __gthread_mutex_lock (__mutex=0x804d15c <m>)
    at /usr/include/c++/6.4.1/i686-redhat-linux/bits/gthr-default.h:748
#3  0x0804925a in std::mutex::lock (this=0x804d15c <m>) at /usr/include/c++/6.4.1/bits/std_mutex.h:103
#4  0x08048e19 in worker () at thread.cpp:17
#5  0x08049f77 in std::_Bind_simple<void (*())()>::_M_invoke<>(std::_Index_tuple<>) (this=0x8052a2c)
    at /usr/include/c++/6.4.1/functional:1391
#6  0x08049f20 in std::_Bind_simple<void (*())()>::operator()() (this=0x8052a2c) at /usr/include/c++/6.4.1/functional:1380
#7  0x08049f07 in std::thread::_State_impl<std::_Bind_simple<void (*())()> >::_M_run() (this=0x8052a28)
    at /usr/include/c++/6.4.1/thread:197
#8  0xb7ebca0f in std::execute_native_thread_routine (__p=0x8052a28) at ../../../../../libstdc++-v3/src/c++11/thread.cc:83
#9  0xb7fa44be in start_thread (arg=0xb7bc7b40) at pthread_create.c:333
#10 0xb7cc8fd6 in clone () at ../sysdeps/unix/sysv/linux/i386/clone.S:110
(gdb) list
135		movl	%edx, %ebx
136		movl	$2, %edx
137		xorl	%esi, %esi	/* No timeout.  */
138		LOAD_FUTEX_WAIT (%ecx)
139
140		cmpl	%edx, %eax	/* NB:	 %edx == 2 */
141		jne 2f
142
143	1:	movl	$SYS_futex, %eax
144		ENTER_KERNEL

__kernel_vsyscall () at arch/x86/entry/vdso/vdso32/system_call.S:41
#endif
