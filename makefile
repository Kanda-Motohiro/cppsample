run: a.out
	./a.out

a.out: vec.cpp
	clang++ -g -Wall -std=c++1z vec.cpp

b.out: string.cpp
	clang++ -g -Wall -std=c++1z string.cpp

hello: hello.cpp
	#rm -f a.out
	#g++ -Wall -g -std=c++1z hello.cpp
	clang++ -g -Wall -std=c++1z -o hello hello.cpp
