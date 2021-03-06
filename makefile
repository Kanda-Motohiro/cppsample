run: a.out
	./a.out

CXXFLAGS=-g -Wall -std=c++1z -O0
CXX=g++
a.out: gsl.cpp
	$(CXX) ${CXXFLAGS} -I/opt/GSL/include -o$@ $^

bind: bind.cpp
	clang++ ${CXXFLAGS} -o$@ $^

move: move.cpp
	$(CXX) ${CXXFLAGS} -o$@ $^

func: func.cpp
	$(CXX) ${CXXFLAGS} -o$@ $^

vtbl: vtbl.cpp
	$(CXX) ${CXXFLAGS} -o$@ $^

init: init.cpp
	$(CXX) ${CXXFLAGS} -o$@ $^

datetime: datetime.cpp
	$(CXX) ${CXXFLAGS} $^ -o$@ -lboost_date_time

A.out: async.cpp
	$(CXX) ${CXXFLAGS} -lpthread $^

t.out: thread.cpp
	$(CXX) ${CXXFLAGS} -lpthread $^

V.out: vectorentry.cpp
	$(CXX) ${CXXFLAGS} $^

B.out: booststr.cpp
	$(CXX) ${CXXFLAGS} $^

ASANFLAGS=-fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer
# -fsanitize=leak  
# clang-3.9: error: unsupported option '-fsanitize=leak' for target 'i686-pc-linux-gnu'
# -fsanitize-address-use-after-scope
# g++: エラー: unrecognized command line option : c++ (GCC) 6.4.1

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

string: string.cpp
	$(CXX) ${CXXFLAGS} -o $@ $^

hello: hello.cpp
	#g++ -Wall -g -std=c++1z hello.cpp
	$(CXX) ${CXXFLAGS} -o hello hello.cpp
