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

vector::push_back(const T& x) だけど、T はコピーコンストラクタが呼ばれて、複写したものがコンテナに入る。そもそも、参照を、コンテナに入れることはできないらしい。

map に存在しないキーを検索すると、新しいアイテムができる。

string, stream は、マルチバイトに対応していない。文字の境界はわからない。

to_string(stoi("1234")) 整数と文字列の変換。

Object.to_string は無い。

move をみんなが実装すれば、参照はいらないのでない？そもそも、 -> のかわりにドットを使いたいだけのシンタクティックシュガーなのでしょ。

Stroustrup 先生の C++ の本を読んでいるが、 あまりに、“resource allocation is initialization” (RAII) の賞賛がうるさいので、Paul E. McKenney さんの批判を紹介しておく。
Is Parallel Programming Hard, And, If So, What Can You Do About It?
https://mirrors.edge.kernel.org/pub/linux/kernel/people/paulmck/perfbook/perfbook.html 
7.2.4 Scoped Locking 参照。


