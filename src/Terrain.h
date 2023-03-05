#ifndef TERRAIN_H
#define TERRAIN_H

#include "Piece.h"

class Terrain {
	private:
		Piece* grille[9][7];

	public:
		Terrain();
		~Terrain();

		Piece* getPiece(unsigned int x, unsigned int y) const;

		bool verifieCase(unsigned int x, unsigned int y);

		void testRegression();
};

#endif