FLAGS = -g -Wall

CORE_PATH = src/core/
CORE_OBJS = obj/Piece.o obj/Terrain.o
CORE_HEADERS = $(CORE_PATH)Piece.h $(CORE_PATH)Terrain.h

GAME_PATH = src/game/
GAME_OBJS = obj/Humain.o obj/Jeu.o
GAME_HEADERS = $(GAME_PATH)Humain.h $(GAME_PATH)Jeu.h


all: bin/tests bin/main


bin/main: obj/main.o $(GAME_OBJS) $(CORE_OBJS)
	g++ $(FLAGS) obj/main.o $(GAME_OBJS) $(CORE_OBJS) -o bin/main

obj/main.o: src/main.cpp $(GAME_HEADERS) $(CORE_HEADERS)
	g++ $(FLAGS) -c src/main.cpp -o obj/main.o


# core

obj/Piece.o: $(CORE_PATH)Piece.cpp $(CORE_PATH)Piece.h
	g++ $(FLAGS) -c $(CORE_PATH)Piece.cpp -o obj/Piece.o

obj/Terrain.o: $(CORE_PATH)Terrain.cpp $(CORE_PATH)Terrain.h $(CORE_PATH)Piece.h
	g++ $(FLAGS) -c $(CORE_PATH)Terrain.cpp -o obj/Terrain.o


bin/tests: $(CORE_OBJS) $(GAME_OBJS) obj/tests.o
	g++ $(FLAGS) $(CORE_OBJS) $(GAME_OBJS) obj/tests.o -o bin/tests

obj/tests.o: $(CORE_PATH)tests.cpp $(CORE_HEADERS) $(GAME_HEADERS)
	g++ $(FLAGS) -c $(CORE_PATH)tests.cpp -o obj/tests.o


# game

obj/Humain.o: $(GAME_PATH)Humain.cpp $(GAME_PATH)Humain.h $(CORE_HEADERS)
	g++ $(FLAGS) -c $(GAME_PATH)Humain.cpp -o obj/Humain.o

obj/Jeu.o: $(GAME_PATH)Jeu.cpp $(GAME_PATH)Jeu.h $(GAME_PATH)Humain.h $(CORE_HEADERS)
	g++ $(FLAGS) -c $(GAME_PATH)Jeu.cpp -o obj/Jeu.o


clean:
	rm obj/*.o
	
veryclean: clean
	rm bin/*