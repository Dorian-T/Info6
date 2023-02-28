all: obj/Piece.o obj/Siege.o obj/Terrain.o
	g++ -g src/Piece.o src/Siege.o src/Terrain.o -o bin/jeu

obj/Piece.o: src/Piece.cpp src/Piece.h src/Siege.h src/Terrain.h
	g++ -g -c src/Piece.cpp -o obj/Piece.o

obj/Siege.o: src/Siege.cpp src/Siege.h
	g++ -g -c src/Siege.cpp -o obj/Siege.o

obj/Terrain.o: src/Terrain.cpp src/Terrain.h src/Piece.h
	g++ -g -c src/Terrain.cpp -o obj/Terrain.o