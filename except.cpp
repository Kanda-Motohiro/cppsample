/*
 * 2018.5.1 kanda.motohiro@gmail.com C++ 練習
 * released under https://creativecommons.org/publicdomain/zero/1.0/legalcode.ja
 */
#include "base.h"
#include <exception>
#include <system_error>

int main()
{
    try {
        throw range_error{"index < 0"};
    } catch (range_error e) { // 実体で拾うことも
        p(e.what());
    }
    try {
        throw system_error(make_error_code(errc::timed_out));
    } catch (system_error &e) { // 参照で拾うこともできる。
        p(e.what());
    }
    try {
        throw int{99};
    } catch (...) {
        auto e = current_exception();
        //p(e);
/*
(gdb) p e
$1 = {<std::runtime_error> = {<std::exception> = {_vptr.exception = 0xb7fb54fc <vtable for std::runtime_error+8>}, _M_msg = ""}, <No data fields>}
 */
    }
    throw "Oops!";
}
