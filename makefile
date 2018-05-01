run: a.out
	./a.out

CXXFLAGS=-g -Wall -std=c++1z -O0

a.out: shared.cpp
	clang++ ${CXXFLAGS} $^

i.out: i8n.cpp
	clang++ ${CXXFLAGS} i8n.cpp -lpthread

v.out: vec.cpp
	clang++ ${CXXFLAGS} -o $@ $^

b.out: string.cpp
	clang++ ${CXXFLAGS} string.cpp

hello: hello.cpp
	#g++ -Wall -g -std=c++1z hello.cpp
	clang++ ${CXXFLAGS} -o hello hello.cpp
