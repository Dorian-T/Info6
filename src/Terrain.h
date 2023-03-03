#ifndef TERRAIN_H
#define TERRAIN_H

#include "Piece.h"

class Terrain {
	private:
		Piece** grille; // tableau de pointeurs sur Piece

	public:
		Terrain();
		~Terrain();

		bool verifieCase(unsigned int x, unsigned int y);

		void testRegression();
};

#endif