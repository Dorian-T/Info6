#ifndef TERRAIN_H
#define TERRAIN_H

#include "Piece.h"

class Terrain {
	private:
		Piece* grille;

	public:
		Terrain();
		~Terrain();
		bool verifieCase(unsigned int x, unsigned int y);
};

#endif