FLAGS = -g -Wall

CORE_PATH = src/core/
CORE_OBJS = obj/Piece.o obj/Terrain.o
CORE_HEADERS = $(CORE_PATH)Piece.h $(CORE_PATH)Terrain.h

GAME_PATH = src/game/
GAME_OBJS = obj/Joueur.o obj/jeu.o
GAME_HEADERS = $(GAME_PATH)Joueur.h $(GAME_PATH)Jeu.h


all: bin/tests bin/main


# core

bin/tests: $(CORE_OBJS) $(GAME_OBJS) obj/tests.o
	g++ $(FLAGS) $(CORE_OBJS) $(GAME_OBJS) obj/tests.o -o bin/tests

obj/Piece.o: $(CORE_PATH)Piece.cpp $(CORE_PATH)Piece.h
	g++ $(FLAGS) -c $(CORE_PATH)Piece.cpp -o obj/Piece.o

obj/Terrain.o: $(CORE_PATH)Terrain.cpp $(CORE_PATH)Terrain.h $(CORE_PATH)Piece.h
	g++ $(FLAGS) -c $(CORE_PATH)Terrain.cpp -o obj/Terrain.o

obj/tests.o: $(CORE_PATH)tests.cpp $(CORE_HEADERS) $(GAME_HEADERS)
	g++ $(FLAGS) -c $(CORE_PATH)tests.cpp -o obj/tests.o


# game

bin/main: $(GAME_OBJS) $(CORE_OBJS) obj/main.o
	g++ $(FLAGS) $(GAME_OBJS) $(CORE_OBJS) obj/main.o -o bin/main

obj/Joueur.o: $(GAME_PATH)Joueur.cpp $(GAME_PATH)Joueur.h $(CORE_HEADERS)
	g++ $(FLAGS) -c $(GAME_PATH)Joueur.cpp -o obj/Joueur.o

obj/jeu.o: $(GAME_PATH)Jeu.cpp $(GAME_PATH)Jeu.h $(GAME_PATH)Joueur.h $(CORE_HEADERS)
	g++ $(FLAGS) -c $(GAME_PATH)Jeu.cpp -o obj/jeu.o

obj/main.o: $(GAME_PATH)Jeu.h $(CORE_HEADERS)
	g++ $(FLAGS) -c $(GAME_PATH)main.cpp -o obj/main.o


clean:
	rm obj/*.o
	
veryclean: clean
	rm bin/*