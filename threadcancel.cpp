/*
 * 2018.8.13 kanda.motohiro@gmail.com C++ 練習
 * released under https://creativecommons.org/publicdomain/zero/1.0/legalcode.ja
pthread_cancel and catch (...) causes FATAL: exception not rethrown abort
なるほど。
http://mkosaki.blog46.fc2.com/blog-entry-1134.html
 */
#include <iostream>
#include <thread>
#include <pthread.h>
using namespace std;

void worker()
{
    try {
    cout << this_thread::get_id() << " started" << endl;
    this_thread::sleep_for(chrono::seconds{60});
    cout << this_thread::get_id() << " done" << endl;
    } catch (...) {
    cout << this_thread::get_id() << " catch" << endl;
    }
}

int main()
{
    int ret;
    thread t = thread(worker);
    auto h = t.native_handle();
    ret = pthread_yield();
    this_thread::sleep_for(chrono::seconds{3});
    ret = pthread_cancel(h);
    void *retval;
    ret = pthread_join(h, &retval);
    this_thread::sleep_for(chrono::seconds{30});
}
#if 0
(gdb) run
Starting program: /home/kanda/git/cppsample/a.out 
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/libthread_db.so.1".
[New Thread 0xb7bc6b40 (LWP 4127)]
3082578752 started
3082578752 catch
FATAL: exception not rethrown

Thread 2 "a.out" received signal SIGABRT, Aborted.
[Switching to Thread 0xb7bc6b40 (LWP 4127)]
__kernel_vsyscall () at arch/x86/entry/vdso/vdso32/system_call.S:71
71		popl	%ebp
(gdb) bt
#0  __kernel_vsyscall () at arch/x86/entry/vdso/vdso32/system_call.S:71
#1  0xb7bf79b0 in __libc_signal_restore_set (set=0xb7bc5f50)
    at ../sysdeps/unix/sysv/linux/nptl-signals.h:79
#2  __GI_raise (sig=6) at ../sysdeps/unix/sysv/linux/raise.c:48
#3  0xb7bf9077 in __GI_abort () at abort.c:89
#4  0xb7c3640f in __libc_message (do_abort=<optimized out>, 
    fmt=<optimized out>) at ../sysdeps/posix/libc_fatal.c:175
#5  0xb7c3644c in __GI___libc_fatal (
    message=0xb7faff90 "FATAL: exception not rethrown\n")
    at ../sysdeps/posix/libc_fatal.c:185
#6  0xb7fabfbb in unwind_cleanup (reason=_URC_FOREIGN_EXCEPTION_CAUGHT, 
    exc=0xb7bc6d90) at unwind.c:105
#7  0xb7db8e0c in _Unwind_DeleteException (exc=0xb7bc6d90)
    at ../../../libgcc/unwind.inc:271
#8  0xb7e89035 in __cxxabiv1::__cxa_end_catch ()
    at ../../../../libstdc++-v3/libsupc++/eh_catch.cc:109
#9  0x08048dd2 in worker () at threadcancel.cpp:16
#10 0x080498c5 in std::_Bind_simple<void (*())()>::_M_invoke<>(std::_Index_tuple<>) (this=0x8051a14) at /usr/include/c++/6.4.1/functional:1391
#11 0x0804986e in std::_Bind_simple<void (*())()>::operator()() (
    this=0x8051a14) at /usr/include/c++/6.4.1/functional:1380
#12 0x08049855 in std::thread::_State_impl<std::_Bind_simple<void (*())()> >::_M_run() (this=0x8051a10) at /usr/include/c++/6.4.1/thread:197
---Type <return> to continue, or q <return> to quit---
#13 0xb7ebba0f in std::execute_native_thread_routine (__p=0x8051a10)
    at ../../../../../libstdc++-v3/src/c++11/thread.cc:83
#14 0xb7fa34be in start_thread (arg=0xb7bc6b40) at pthread_create.c:333
#15 0xb7cc7fd6 in clone () at ../sysdeps/unix/sysv/linux/i386/clone.S:110
(gdb) 

(gdb) list
100	static void
101	unwind_cleanup (_Unwind_Reason_Code reason, struct _Unwind_Exception *exc)
102	{
103	  /* When we get here a C++ catch block didn't rethrow the object.  We
104	     cannot handle this case and therefore abort.  */
105	  __libc_fatal ("FATAL: exception not rethrown\n");
106	}
#endif
