out: game.o main.cpp
	g++ -o out game.o main.cpp -lncurses --std=c++11

game.o: game.cpp
	g++ -c game.cpp -o game.o --std=c++11
