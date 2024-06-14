CC = gcc
FLAGS = -Wall -Werror -Wextra 

all: clean install
	./build/front.app/Contents/MacOS/front
	
install:
	mkdir build
	cd ./build; cmake ../front/CMakeLists.txt; cmake --build .

uninstall:
	rm -rf build

clean: uninstall
	rm -rf *.o *.a *.g* calculator
	rm -rf model/*.o model/*.a model/*.g* model/calculator
	rm -rf test.info test report test1 test2
	rm -rf ../src.tar

dvi:
	open 1.html

dist: 
	cd ..; tar -cvf src.tar src

# for linux: -lrt -lm -lsubunit
test: clean 
	$(CC) $(FLAGS) model/calculator.c model/test.c -lcheck  -o test
	./test

gcov_report: clean
	$(CC) --coverage model/test.c model/calculator.c $(FLAGS) -lcheck -o test
	./test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
#open report/index.html

rebuild: clean all

stylei:
	clang-format -style=google -i model/calculator.c
	clang-format -style=google -i model/calculator.h
	clang-format -style=google -i model/test.c
	clang-format -style=google -i front/mainwindow.cpp
	clang-format -style=google -i front/mainwindow.h
style:
	clang-format -style=google -n model/calculator.c
	clang-format -style=google -n model/calculator.h
	clang-format -style=google -n model/test.c
	clang-format -style=google -n front/mainwindow.cpp
	clang-format -style=google -n front/mainwindow.h

21: 
	$(CC) $(FLAGS) model/calculator.c -lm -o calculator
	./calculator

leaks: clean test
		CK_FORK=no leaks --atExit -- ./test
