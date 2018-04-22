/*
 * 2018.4.22 kanda.motohiro@gmail.com
 * released under https://creativecommons.org/publicdomain/zero/1.0/legalcode.ja
 */
#include <iostream>
#include <string>
#include <thread>
using namespace std;

#define p(a) { cout << (a) << " at line " << __LINE__ << endl; }

void work(int n) {
    p(this_thread::get_id());
    cout << "sleeping " << n << endl;
    this_thread::sleep_for(chrono::seconds(30));
}

int main()
{
    p(this_thread::get_id());
    thread t0(work, 0);
    thread t1(work, 1);

    t0.join();
    t1.join();

#if 0
    {
        thread t2(work, 2);
    }
実行中のスレッドがいるのに、デストラクタが呼ばれると落ちる。
Thread 1 "a.out" received signal SIGABRT, Aborted.
__kernel_vsyscall () at arch/x86/entry/vdso/vdso32/system_call.S:71
71		popl	%ebp
(gdb) bt
#0  __kernel_vsyscall () at arch/x86/entry/vdso/vdso32/system_call.S:71
#1  0xb7bfa9b0 in __libc_signal_restore_set (set=0xbfffeda0) at ../sysdeps/unix/sysv/linux/nptl-signals.h:79
#2  __GI_raise (sig=6) at ../sysdeps/unix/sysv/linux/raise.c:48
#3  0xb7bfc077 in __GI_abort () at abort.c:89
#4  0xb7e8fb67 in __gnu_cxx::__verbose_terminate_handler () at ../../../../libstdc++-v3/libsupc++/vterminate.cc:95
#5  0xb7e8d295 in __cxxabiv1::__terminate (handler=0xb7e8f9a0 <__gnu_cxx::__verbose_terminate_handler()>)
    at ../../../../libstdc++-v3/libsupc++/eh_terminate.cc:47
#6  0xb7e8d30d in std::terminate () at ../../../../libstdc++-v3/libsupc++/eh_terminate.cc:57
#7  0x08049cb9 in std::thread::~thread (this=0xbffff190)
    at /usr/bin/../lib/gcc/i686-redhat-linux/6.4.1/../../../../include/c++/6.4.1/thread:146
#8  0x0804937d in main () at i8n.cpp:29
#endif

    string s = u8"あいうえお12345";
    p(s);
    p(s.size());
    p(s[0]);
    p(s[5]);
    for (unsigned char c: s) printf("%02x ", c);
    cout << endl;
    p(s.find(u8"い"));
    p(s.find(u8"3"));
    p(s.replace(3, 3, u8"まで"));
#if 0
あいうえお12345 at line 50
20 at line 51
� at line 52
� at line 53
e3 81 82 e3 81 84 e3 81 86 e3 81 88 e3 81 8a 31 32 33 34 35
3 at line 56
17 at line 57
あまでうえお12345 at line 58
#endif
}

