#ifndef TERRAIN_H
#define TERRAIN_H

#include "Case.h"

class Terrain {
	private:
		Case* grille;

	public:
		Terrain();
		~Terrain();
		bool verifieCase(unsigned int x, unsigned int y);
};

#endif