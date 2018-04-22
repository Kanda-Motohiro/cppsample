/*
 * by kanda.motohiro@gmail.com
 * released under https://creativecommons.org/publicdomain/zero/1.0/legalcode.ja
 */
#include <iostream>
#include <fcntl.h>

std::string s;
#ifdef C
#include <stdlib.h>
int main() {
    void *p = malloc(256);
    s = "C";
    printf("Hello ");
#else
#include <cstdlib>
int main() {
    void *p = std::malloc(256);
    s = "C++";
    std::printf("World ");
#endif
    //int fd = std::open("/etc/hosts", 0);
    int fd = open("/etc/hosts", 0);
    std::cout << s << p << std::endl;
}

