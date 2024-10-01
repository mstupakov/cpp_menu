all: menu_cpp menu_c

menu_cpp: main.cpp
	${CROSS_COMPILE}g++ -std=c++14 $^ -o $@

menu_c: main.c menu.c
	${CROSS_COMPILE}gcc $^ -o $@

clean:
	rm  -rf menu_cpp menu_c
