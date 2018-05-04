run: a.out
	./a.out

CXXFLAGS=-g -Wall -std=c++1z -O0
ASANFLAGS=-fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer
# -fsanitize=leak  
# clang-3.9: error: unsupported option '-fsanitize=leak' for target 'i686-pc-linux-gnu'
# -fsanitize-address-use-after-scope
# g++: エラー: unrecognized command line option : c++ (GCC) 6.4.1

CXX=g++
a.out: async.cpp
	$(CXX) ${CXXFLAGS} -lpthread $^

t.out: thread.cpp
	$(CXX) ${CXXFLAGS} -lpthread $^

V.out: vectorentry.cpp
	$(CXX) ${CXXFLAGS} $^

B.out: booststr.cpp
	$(CXX) ${CXXFLAGS} $^

d.out: debug.cpp
	$(CXX) ${CXXFLAGS} $(ASANFLAGS) $^

#CXX=clang++
S.out: serialize.cpp
	$(CXX) ${CXXFLAGS} $^ -lboost_serialization

e.out: except.cpp
	$(CXX) ${CXXFLAGS} $^

s.out: shared.cpp
	$(CXX) ${CXXFLAGS} $^

i.out: i8n.cpp
	$(CXX) ${CXXFLAGS} i8n.cpp -lpthread

v.out: vec.cpp
	$(CXX) ${CXXFLAGS} -o $@ $^

b.out: string.cpp
	$(CXX) ${CXXFLAGS} string.cpp

hello: hello.cpp
	#g++ -Wall -g -std=c++1z hello.cpp
	$(CXX) ${CXXFLAGS} -o hello hello.cpp
