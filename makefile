out: game.o main.cpp
	g++ -o out game.o main.cpp -lncurses

game.o: game.cpp
	g++ -c game.cpp -o game.o
