/*
 * 2018.5.4 kanda.motohiro@gmail.com C++ 練習
 * released under https://creativecommons.org/publicdomain/zero/1.0/legalcode.ja
 */
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
using namespace std;

class Locker {
public:
    int refcount = 0;
    mutex m;
};
Locker *L = nullptr;

#define p(a) cout << "pid=" << getpid() << " tid=" << this_thread::get_id() \
<< " " << (a) << endl;

void worker()
{
    this_thread::sleep_for(chrono::seconds{3});
    p("started");
    L->m.lock();
    p("got lock");
    this_thread::sleep_for(chrono::seconds{10});
    L->m.unlock();
    p("unlock");
}

int main()
{
    int fd = open("/tmp/zero", O_RDWR);
    if (fd < 0) exit(1);
    void *p = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (p == MAP_FAILED) exit(1);
    L = (Locker *)p;
    p(L->refcount);
    // 最初のプロセスが、 mutex を初期化する。
    if (L->refcount == 0) {
        L = new(p) Locker;
    }
    L->refcount++; // I know this is not atomic.

    vector<thread> vec(2);
    for (size_t i=0; i<vec.size(); i++) {
        vec[i] = thread(worker);
    }
    this_thread::sleep_for(chrono::seconds{3});
    for (size_t i=0; i<vec.size(); i++) {
        vec[i].join();
    }
    L->refcount--;
}
#if 0
mmap したところに、 mutex を置けば、 futex を使っているなら
プロセス間でロックが効くと思ったが、うまくいかなかった。
posix mutex というのはそういうものだけどさ。

[kanda@f25 cppsample]$ ./a.out
pid=3531 tid=3081799424 0
pid=3531 tid=3073403712 started
pid=3531 tid=3073403712 got lock
pid=3531 tid=3081796416 started
pid=3531 tid=3073403712 unlock
pid=3531 tid=3081796416 got lock
pid=3531 tid=3081796416 unlock
[kanda@f25 cppsample]$ od -x /tmp/zero
0000000 0001 0000 0000 0000 0000 0000 0000 0000

[kanda@f25 cppsample]$ ./a.out
pid=3534 tid=3081885440 1
pid=3534 tid=3073489728 started
pid=3534 tid=3081882432 started
ここで、止まってしまう。

(gdb) bt
#0  __kernel_vsyscall () at arch/x86/entry/vdso/vdso32/system_call.S:71
#1  0xb7f02232 in __lll_lock_wait () at ../sysdeps/unix/sysv/linux/i386/lowlevellock.S:144
#2  0xb7efbb2e in __GI___pthread_mutex_lock (mutex=0xb7f25004) at ../nptl/pthread_mutex_lock.c:80
#3  0x08048e42 in __gthread_mutex_lock (__mutex=0xb7f25004)
    at /usr/include/c++/6.4.1/i686-redhat-linux/bits/gthr-default.h:748
#4  0x0804959a in std::mutex::lock (this=0xb7f25004) at /usr/include/c++/6.4.1/bits/std_mutex.h:103
#5  0x08048f45 in worker () at thread.cpp:29

29	    L->m.lock();
(gdb) p *L
$1 = {refcount = 1, m = {<std::__mutex_base> = {_M_mutex = {__data = {__lock = 0, __count = 0, __owner = 0, __kind = 0, 
          __nusers = 0, {__elision_data = {__espins = 0, __elision = 0}, __list = {__next = 0x0}}}, 
        __size = '\000' <repeats 23 times>, __align = 0}}, <No data fields>}}

なぜか、デバッガをデタッチすると、アンロックされていることに気がつく。
(gdb) detach
Detaching from program: /home/kanda/git/cppsample/a.out, process 3534

pid=3534 tid=3073489728 got lock
pid=3534 tid=3073489728 unlock
pid=3534 tid=3081882432 got lock
pid=3534 tid=3081882432 unlock
#endif
