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

		bool verifieCase(unsigned int ax, unsigned int ay, unsigned int nx, unsigned int ny);

		void testRegression();
};

#endif