run: a.out
	./a.out

CXXFLAGS=-g -Wall -std=c++1z -O0

a.out: vec.cpp
	clang++ ${CXXFLAGS} vec.cpp

b.out: string.cpp
	clang++ ${CXXFLAGS} string.cpp

hello: hello.cpp
	#g++ -Wall -g -std=c++1z hello.cpp
	clang++ ${CXXFLAGS} -o hello hello.cpp
