#ifndef HUMAIN_H
#define HUMAIN_H

#include "../core/Piece.h"
#include "../core/Terrain.h"

#include <string>


class Humain {
	private:
		Couleur couleur;

		bool coordonneesValides(Terrain & t, int x, int y);
		Piece* choixCoordonnees(Terrain & t);
		bool choixDirection(Terrain & t, Piece * P);

	public:
		Humain(Couleur c);
		void joue(Terrain & t);
};

#endif