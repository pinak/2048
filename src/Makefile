all: 2048

2048: main.o game.o
	g++ main.o game.o -o 2048

main.o: main.cpp
	g++ -c main.cpp

game.o: game.cpp
	g++ -c game.cpp

clean:
	rm -rf *.o 2048

