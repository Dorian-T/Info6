CORE_OBJS = obj/Piece.o obj/Soldat.o obj/Siege.o obj/Donjon.o obj/Terrain.o
CORE_PATH = src/core/


all: bin/tests

bin/tests: obj/tests.o $(CORE_OBJS)
	g++ -g obj/tests.o $(CORE_OBJS) -o bin/tests

obj/tests.o: $(CORE_PATH)tests.cpp $(CORE_PATH)Piece.h $(CORE_PATH)Soldat.h $(CORE_PATH)Siege.h $(CORE_PATH)Donjon.h $(CORE_PATH)Terrain.h
	g++ -g -c $(CORE_PATH)tests.cpp -o obj/tests.o

obj/Piece.o: $(CORE_PATH)Piece.cpp $(CORE_PATH)Piece.h $(CORE_PATH)Soldat.h $(CORE_PATH)Siege.h
	g++ -g -c $(CORE_PATH)Piece.cpp -o obj/Piece.o

obj/Soldat.o: $(CORE_PATH)Soldat.cpp $(CORE_PATH)Soldat.h $(CORE_PATH)Piece.h $(CORE_PATH)Siege.h $(CORE_PATH)Terrain.h
	g++ -g -c $(CORE_PATH)Soldat.cpp -o obj/Soldat.o

obj/Siege.o: $(CORE_PATH)Siege.cpp $(CORE_PATH)Siege.h $(CORE_PATH)Piece.h $(CORE_PATH)Soldat.h
	g++ -g -c $(CORE_PATH)Siege.cpp -o obj/Siege.o

obj/Donjon.o: $(CORE_PATH)Donjon.cpp $(CORE_PATH)Donjon.h $(CORE_PATH)Piece.h $(CORE_PATH)Terrain.h
	g++ -g -c $(CORE_PATH)Donjon.cpp -o obj/Donjon.o

obj/Terrain.o: $(CORE_PATH)Terrain.cpp $(CORE_PATH)Terrain.h $(CORE_PATH)Piece.h
	g++ -g -c $(CORE_PATH)Terrain.cpp -o obj/Terrain.o