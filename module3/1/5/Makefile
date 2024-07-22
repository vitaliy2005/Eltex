all:
	clang -fPIC -c structFunctions.c
	clang -shared structFunctions.o -o libname.so
	clang main.c -o main -L. -ldl
	./main
