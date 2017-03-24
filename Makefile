all: main.cpp
	${CROSS_COMPILE}g++ -std=c++14 $^ -o menu

clean:
	rm  -rf menu
