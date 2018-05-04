/*
 * 2018.5.4 kanda.motohiro@gmail.com C++ 練習
 * released under https://creativecommons.org/publicdomain/zero/1.0/legalcode.ja
 */
#include <iostream>
#include <thread>
#include <future>
using namespace std;

int worker(int a)
{
    this_thread::sleep_for(chrono::seconds{3});
    return a*a;
}

int main()
{
    future<int> f = async(launch::async, worker, 5);
    cout << f.get() << endl;
}
#if 0
Thread 2 "a.out" hit Breakpoint 1, worker (a=5) at async.cpp:12
12	    this_thread::sleep_for(chrono::seconds{3});
(gdb) info thread
  Id   Target Id         Frame 
  1    Thread 0xb7bc8700 (LWP 4582) "a.out" __kernel_vsyscall () at arch/x86/entry/vdso/vdso32/system_call.S:71
* 2    Thread 0xb7bc7b40 (LWP 4586) "a.out" worker (a=5) at async.cpp:12
(gdb) thread 1
[Switching to thread 1 (Thread 0xb7bc8700 (LWP 4582))]
#0  __kernel_vsyscall () at arch/x86/entry/vdso/vdso32/system_call.S:71
71		popl	%ebp
(gdb) bt
#0  __kernel_vsyscall () at arch/x86/entry/vdso/vdso32/system_call.S:71
#1  0xb7fa5613 in pthread_join (threadid=3082582848, thread_return=0x0) at pthread_join.c:90
#2  0xb7ebcd48 in __gthread_join (__value_ptr=0x0, __threadid=<optimized out>)
    at /usr/src/debug/gcc-6.4.1-20170727/obj-i686-redhat-linux/i686-redhat-linux/libstdc++-v3/include/i686-redhat-linux/bits/gthr-default.h:668
#3  std::thread::join (this=0x805aa30) at ../../../../../libstdc++-v3/src/c++11/thread.cc:136
#4  0x0804b91b in std::__invoke_impl<void, void (std::thread::*)(), std::thread*>(std::__invoke_memfun_deref, void (std::thread::*&&)(), std::thread*&&) (__f=<unknown type in /home/kanda/git/cppsample/a.out, CU 0x0, DIE 0xfbf2>, 
    __t=<unknown type in /home/kanda/git/cppsample/a.out, CU 0x0, DIE 0xfbe6>) at /usr/include/c++/6.4.1/functional:227
#5  0x0804b2c2 in std::__invoke<void (std::thread::*)(), std::thread*>(void (std::thread::*&&)(), std::thread*&&) (
    __fn=<unknown type in /home/kanda/git/cppsample/a.out, CU 0x0, DIE 0xfbf2>, 
    __args#0=<unknown type in /home/kanda/git/cppsample/a.out, CU 0x0, DIE 0xfbe6>)
    at /usr/include/c++/6.4.1/functional:251
#6  0x0804a9e6 in void std::call_once<void (std::thread::*)(), std::thread*>(std::once_flag&, void (std::thread::*&&)(), std::thread*&&)::{lambda()#1}::operator()() const (__closure=0xbffff060) at /usr/include/c++/6.4.1/mutex:602
#7  0x0804aa17 in void std::call_once<void (std::thread::*)(), std::thread*>(std::once_flag&, void (std::thread::*&&)(), std::thread*&&)::{lambda()#2}::operator()() const (__closure=0x0) at /usr/include/c++/6.4.1/mutex:607
#8  0x0804aa2d in void std::call_once<void (std::thread::*)(), std::thread*>(std::once_flag&, void (std::thread::*&&)(), std::thread*&&)::{lambda()#2}::_FUN() () at /usr/include/c++/6.4.1/mutex:607
#9  0xb7fab615 in __pthread_once_slow (once_control=0x805aa34, init_routine=0x80495a0 <__once_proxy@plt>)
    at pthread_once.c:116
#10 0x080497f8 in __gthread_once (__once=0x805aa34, __func=0x80495a0 <__once_proxy@plt>)
    at /usr/include/c++/6.4.1/i686-redhat-linux/bits/gthr-default.h:699
---Type <return> to continue, or q <return> to quit---
#11 0x0804aa91 in std::call_once<void (std::thread::*)(), std::thread*>(std::once_flag&, void (std::thread::*&&)(), std::thread*&&) (__once=..., __f=<unknown type in /home/kanda/git/cppsample/a.out, CU 0x0, DIE 0xfbf2>, 
    __args#0=<unknown type in /home/kanda/git/cppsample/a.out, CU 0x0, DIE 0xfbe6>) at /usr/include/c++/6.4.1/mutex:614
#12 0x0804a47c in std::__future_base::_Async_state_commonV2::_M_join (this=0x805aa1c) at /usr/include/c++/6.4.1/future:1645
#13 0x0804a441 in std::__future_base::_Async_state_commonV2::_M_complete_async (this=0x805aa1c)
    at /usr/include/c++/6.4.1/future:1643
#14 0x0804a07e in std::__future_base::_State_baseV2::wait (this=0x805aa1c) at /usr/include/c++/6.4.1/future:325
#15 0x0804b66e in std::__basic_future<int>::_M_get_result (this=0xbffff194) at /usr/include/c++/6.4.1/future:706
#16 0x0804af10 in std::future<int>::get (this=0xbffff194) at /usr/include/c++/6.4.1/future:785
#17 0x08049932 in main () at async.cpp:19
(gdb) 

#endif
