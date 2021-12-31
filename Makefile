build:
	g++ -std=c++17 src/* -I include -o FileList

run:
	valgrind ./FileList
