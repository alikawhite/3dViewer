.PHONY: tests gcov_report uninstall build install dvi_install dvi dist clang leaks clean
CC = g++ -std=c++17
TESTFILE = gtest
OS = $(shell uname -s)
ifeq ($(OS), Linux)
	LIBS_FOR_CHECK_PCKG = -lgtest -lpthread -lgtest_main -pthread -lrt
	D_OS = -D __My_Linux__
	NAME = 3d_Viewer_2
	LEAK_COMMAND = valgrind --tool=memcheck --leak-check=yes  ./a.out
	DVI_INSTALL_COMMAND = sudo apt install doxygen
	OPEN_FILE = xdg-open
else
	LIBS_FOR_CHECK_PCKG = -lcheck -lgtest -lgtest_main -pthread
	D_OS = -D __My_APPLE__
	NAME = 3d_Viewer_2.app
	LEAK_COMMAND = CK_FORK=no leaks --atExit -- ./a.out
	DVI_INSTALL_COMMAND = brew install doxygen
	OPEN_FILE = open
endif

all: clean install tests gcov_report

tests:
	$(CC) -g $(TESTFILE).cc $(LIBS_FOR_CHECK_PCKG) -L /usr/local/lib  --coverage
	@ echo "\n-------------------- Test --------------------"
	@./a.out --gtest_repeat=10 --gtest_break_on_failure

gcov_report:
	gcovr --html --html-details -o report.html
	@$(OPEN_FILE) report.html

uninstall:
	rm -rf $(HOME)/3d_Viewer_2/

build:
	@mkdir build
	@cd ./build/ && qmake ../ && make

install: build
	rm -rf $(HOME)/3d_Viewer_2
	mkdir $(HOME)/3d_Viewer_2/
	cp -rf build/$(NAME) $(HOME)/3d_Viewer_2/
	make clean

dvi_install:
	$(DVI_INSTALL_COMMAND)

dvi:
	@rm -rf doxygen
	@doxygen
	@$(OPEN_FILE) doxygen/html/index.html

dist: 
	rm -rf build
	mkdir 3d_Viewer_2
	mkdir 3d_Viewer_2/src
	cp Makefile Doxyfile src/tests/box.txt *.cc *.h *.cpp *.ui *.pro *.pro.user 3d_Viewer_2/src/
	tar -cvzf 3d_Viewer_2.tar.gz 3d_Viewer_2
	mv 3d_Viewer_2.tar.gz $(HOME)/
	rm -rf 3d_Viewer_2/

clang:
	clang-format --style=google -n *.cc *.h

leaks:
	$(LEAK_COMMAND)

clean:
	rm -rf  *.gc* report test.info build SmartCalculator doxygen *.dSYM report.* 
	rm -f *.a *.o *.so *.out $(TESTFILE) *.info *.user
