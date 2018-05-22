/*
 * 2018.5.1 kanda.motohiro@gmail.com C++ 練習
 * released under https://creativecommons.org/publicdomain/zero/1.0/legalcode.ja
 */
#include "base.h"

int main()
{
    shared_ptr<Base> a(new Base{"a"});
    p3(a);
    { shared_ptr<Base> b{a};
        p(b.use_count());
    }
    Base *c = new Base{"c"};
    shared_ptr<Base> d = make_shared<Base>("d");
    unique_ptr<Base> f = make_unique<Base>("f");
    printf("shared=%d unique=%d\n", sizeof(a), sizeof(f));
    p("---- end of scope ----");
}
#if 0
shared=8 unique=4

(gdb) p d
$1 = std::shared_ptr (count 1, weak 0) 0x8052e7c
(gdb) p f
$2 = std::unique_ptr<Base> containing 0x8052ea0
(gdb) p &d
$3 = (std::shared_ptr<Base> *) 0xbffff12c
(gdb) p &f
$4 = (std::unique_ptr<Base, std::default_delete<Base> > *) 0xbffff128
(gdb) x/2x 0xbffff12c
0xbffff12c:	0x08052e7c	0x08052e70
(gdb) x/x 0xbffff128
0xbffff128:	0x08052ea0

(gdb) 
0x08048ffb	15	    shared_ptr<Base> d = make_shared<Base>("d");
1: x/i $eip
=> 0x8048ffb <main()+491>:	
    call   0x80494a2 <std::make_shared<Base, char const (&) [2]>(char const (&) [2])>
(gdb) si
std::make_shared<Base, char const (&) [2]> (__args#0=...)
    at /usr/include/c++/6.4.1/bits/shared_ptr.h:632
632	    make_shared(_Args&&... __args)

    inline shared_ptr<_Tp>
    make_shared(_Args&&... __args)
    {
      typedef typename std::remove_const<_Tp>::type _Tp_nc;
      return std::allocate_shared<_Tp>(std::allocator<_Tp_nc>(),
                       std::forward<_Args>(__args)...);
    }

(gdb) 
0x0804900f	16	    unique_ptr<Base> f = make_unique<Base>("f");
1: x/i $eip
=> 0x804900f <main()+511>:	
    call   0x8049513 <std::make_unique<Base, char const (&) [2]>(char const (&) [2])>
(gdb) 
std::make_unique<Base, char const (&) [2]> (__args#0=...)
    at /usr/include/c++/6.4.1/bits/unique_ptr.h:790
790	    make_unique(_Args&&... __args)

    make_unique(_Args&&... __args)
    { return unique_ptr<_Tp>(new _Tp(std::forward<_Args>(__args)...)); }
#endif
