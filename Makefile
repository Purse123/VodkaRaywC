all: init render

init: ./include/calam.cpp
	g++ ./include/calam.cpp -c -o calam.o -I/usr/include/SDL2 -D_REENTRANT -lSDL2 -Wall -Wextra -O3

render: calam.o main.cpp
	g++ main.cpp calam.o -o main -I/usr/include/SDL2 -D_REENTRANT -lSDL2 -Wall -Wextra -O3

clean:
	rm *~ calam.o main
