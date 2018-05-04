# cppsample
by kanda.motohiro@gmail.com in April 2018
released under https://creativecommons.org/publicdomain/zero/1.0/legalcode

私が C++ を学ぶ間に、自宅で書き散らした、 C++ のコードサンプル。
私が他の場所で見たくなったときのために、 github に置く。

私は、参照がわからないレベルの初心者です。

アドバイスとおぼえがき
---------------------

コンパイラのエラーメッセージは、全部、読まないでいい。char trait とか、なんのことかわからなくていい。自分のソースコードの行番号が出ている行だけを探せ。

端末は 24x80 よりも、横を長くする。

gdb のブレークポイントは、名前空間::クラス名::関数名 を指定する必要がある。

main は名前空間に入っていてはいけない。

コンパイラのエラーメッセージは、ぐぐるとわかることが多い。

string は更新できる。

"abc" x 100 繰り返し、ということはできない。作れば、できる、けど。

例外を起こしたソースコードの関数名と行番号を、 python のように backtrace 表示することはできない。作れば、略。

C の関数のごく一部は、 cstdlib にあって、 std::printf のように使えるけど、わざわざそうする利益はない．

std::exit は、(データセグメントに実体があるインスタンスの)デストラクタを実行する。 ::exit はしない。

vector::push_back(const T& x) だけど、T はコピーコンストラクタが呼ばれて、new で複写したものがコンテナに入る。そもそも、参照を、コンテナに入れることはできないらしい。array は、実体が入る。vectorentry.cpp

string, stream は、マルチバイトに対応していない。文字の境界はわからない。i8n.cpp VC++ はどうか知らない。

to_string(stoi("1234")) 整数と文字列の変換。

Object.to_string は無い。シリアライズは、 boost にある。serialize.cpp

Stroustrup 先生の C++ の本を読んでいるが、 あまりに、“resource allocation is initialization” (RAII) の賞賛がうるさいので、Paul E. McKenney さんの批判を紹介しておく。
Is Parallel Programming Hard, And, If So, What Can You Do About It?
https://mirrors.edge.kernel.org/pub/linux/kernel/people/paulmck/perfbook/perfbook.html 
7.2.4 Scoped Locking 参照。

boost すごい。strip==trim, split, startswith, s.replace("a", "b"), インラインフォーマット文字列構築など、python にあって C++ で不便に思っていたことが全部、できる。booststr.cpp 

ツール
=======

cppcheck, cpplint.py, scan-build from clang-analyzer package

AddressSanitizer https://github.com/google/sanitizers/wiki/AddressSanitizer

clang
=====

clang でビルドしても、 gcc の libc がくっつく。

$ g++ -g -Wall -std=c++1z -O0 vectorentry.cpp
$ ls -l a.out
-rwxrwxr-x 1 kanda kanda 102500  5月  4 17:26 a.out
$ ldd a.out
	linux-gate.so.1 (0xb7fb3000)
	libstdc++.so.6 => /lib/libstdc++.so.6 (0xb7e13000)
	libm.so.6 => /lib/libm.so.6 (0xb7dbc000)
	libgcc_s.so.1 => /lib/libgcc_s.so.1 (0xb7d9e000)
	libc.so.6 => /lib/libc.so.6 (0xb7bc4000)
	/lib/ld-linux.so.2 (0xb7fb5000)
$ clang++ -g -Wall -std=c++1z -O0 vectorentry.cpp
$ ls -l a.out
-rwxrwxr-x 1 kanda kanda 116924  5月  4 17:26 a.out
$ ldd a.out
	linux-gate.so.1 (0xb7eee000)
	libstdc++.so.6 => /lib/libstdc++.so.6 (0xb7d4e000)
	libm.so.6 => /lib/libm.so.6 (0xb7cf7000)
	libgcc_s.so.1 => /lib/libgcc_s.so.1 (0xb7cd9000)
	libc.so.6 => /lib/libc.so.6 (0xb7aff000)
	/lib/ld-linux.so.2 (0xb7ef0000)

$ ldd /usr/bin/clang-3.9
	linux-gate.so.1 (0xb7f79000)
	libLLVM-3.9.so => /lib/libLLVM-3.9.so (0xb5494000)
...
/usr/lib/libclang* にたくさんあるのは、コンパイラ自身の dll.

$ ls /usr/include/clang
ARCMigrate   Basic    Edit          Index    Sema
これは何？


