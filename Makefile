all: bin/tests

bin/tests: obj/tests.o obj/Piece.o obj/Soldat.o obj/Siege.o obj/Donjon.o obj/Terrain.o
	g++ -g obj/tests.o obj/Piece.o obj/Soldat.o obj/Siege.o obj/Donjon.o obj/Terrain.o -o bin/tests

obj/tests.o: src/tests.cpp src/Piece.h src/Soldat.h src/Siege.h src/Donjon.h src/Terrain.h
	g++ -g -c src/tests.cpp -o obj/tests.o

obj/Piece.o: src/Piece.cpp src/Piece.h
	g++ -g -c src/Piece.cpp -o obj/Piece.o

obj/Soldat.o: src/Soldat.cpp src/Soldat.h src/Piece.h src/Terrain.h
	g++ -g -c src/Soldat.cpp -o obj/Soldat.o

obj/Siege.o: src/Siege.cpp src/Siege.h src/Piece.h src/Soldat.h src/Terrain.h
	g++ -g -c src/Siege.cpp -o obj/Siege.o

obj/Donjon.o: src/Donjon.cpp src/Donjon.h src/Piece.h
	g++ -g -c src/Donjon.cpp -o obj/Donjon.o

obj/Terrain.o: src/Terrain.cpp src/Terrain.h src/Piece.h
	g++ -g -c src/Terrain.cpp -o obj/Terrain.o