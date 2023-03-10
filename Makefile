FLAGS = -g -Wall

CORE_PATH = src/core/
CORE_OBJS = obj/Piece.o obj/Soldat.o obj/Siege.o obj/Donjon.o obj/Terrain.o
CORE_HEADERS = $(CORE_PATH)Piece.h $(CORE_PATH)Soldat.h $(CORE_PATH)Siege.h $(CORE_PATH)Donjon.h $(CORE_PATH)Terrain.h

GAME_PATH = src/game/
GAME_OBJS = obj/Joueur.o obj/main.o obj/jeu.o


all: bin/tests bin/main


bin/tests: $(CORE_OBJS) obj/tests.o
	g++ $(FLAGS) $(CORE_OBJS) obj/tests.o -o bin/tests

obj/Piece.o: $(CORE_PATH)Piece.cpp $(CORE_PATH)Piece.h $(CORE_PATH)Soldat.h $(CORE_PATH)Siege.h
	g++ $(FLAGS) -c $(CORE_PATH)Piece.cpp -o obj/Piece.o

obj/Soldat.o: $(CORE_PATH)Soldat.cpp $(CORE_PATH)Soldat.h $(CORE_PATH)Piece.h $(CORE_PATH)Siege.h $(CORE_PATH)Terrain.h
	g++ $(FLAGS) -c $(CORE_PATH)Soldat.cpp -o obj/Soldat.o

obj/Siege.o: $(CORE_PATH)Siege.cpp $(CORE_PATH)Siege.h $(CORE_PATH)Piece.h $(CORE_PATH)Soldat.h
	g++ $(FLAGS) -c $(CORE_PATH)Siege.cpp -o obj/Siege.o

obj/Donjon.o: $(CORE_PATH)Donjon.cpp $(CORE_PATH)Donjon.h $(CORE_PATH)Piece.h $(CORE_PATH)Terrain.h
	g++ $(FLAGS) -c $(CORE_PATH)Donjon.cpp -o obj/Donjon.o

obj/Terrain.o: $(CORE_PATH)Terrain.cpp $(CORE_PATH)Terrain.h $(CORE_PATH)Piece.h
	g++ $(FLAGS) -c $(CORE_PATH)Terrain.cpp -o obj/Terrain.o

obj/tests.o: $(CORE_PATH)tests.cpp $(CORE_PATH)Piece.h $(CORE_PATH)Soldat.h $(CORE_PATH)Siege.h $(CORE_PATH)Donjon.h $(CORE_PATH)Terrain.h
	g++ $(FLAGS) -c $(CORE_PATH)tests.cpp -o obj/tests.o


bin/main: $(GAME_OBJS) $(CORE_OBJS)
	g++ $(FLAGS) $(GAME_OBJS) $(CORE_OBJS) -o bin/main

obj/Joueur.o: $(GAME_PATH)Joueur.cpp $(GAME_PATH)Joueur.h $(CORE_HEADERS)
	g++ $(FLAGS) -c $(GAME_PATH)Joueur.cpp -o obj/Joueur.o

obj/main.o: $(GAME_PATH)Jeu.h $(CORE_HEADERS)
	g++ $(FLAGS) -c $(GAME_PATH)main.cpp -o obj/main.o

obj/jeu.o: $(GAME_PATH)Jeu.cpp $(GAME_PATH)Jeu.h $(GAME_PATH)Joueur.h $(CORE_HEADERS)
	g++ $(FLAGS) -c $(GAME_PATH)Jeu.cpp -o obj/jeu.o