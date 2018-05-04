/*
 * 2018.5.4 kanda.motohiro@gmail.com C++ 練習
 * released under https://creativecommons.org/publicdomain/zero/1.0/legalcode.ja
 * based on https://www.boost.org/doc/libs/1_67_0/doc/html/date_time/examples.html
 */
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <chrono>
#include <thread>
#include "base.h"

int main()
{
    chrono::high_resolution_clock::time_point a = chrono::high_resolution_clock::now();
    this_thread::sleep_for(chrono::milliseconds{1});
    chrono::high_resolution_clock::time_point b = chrono::high_resolution_clock::now();
    chrono::nanoseconds c = chrono::duration_cast<chrono::nanoseconds>(b - a);
    p(c.count());

    boost::gregorian::date d(boost::gregorian::from_string("2018-5-4"));
    p(d);
    boost::gregorian::date e(2000, 1, 1);
    p(e);
    boost::gregorian::date_duration f = d - e;
    p(f);

    boost::posix_time::ptime g(d, boost::posix_time::seconds{0});
    p(g);
    boost::posix_time::ptime h = g + boost::posix_time::hours{22};
    p(h);
}
