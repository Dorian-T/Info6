#ifndef HUMAIN_H
#define HUMAIN_H

#include "../core/Terrain.h"

#include <string>


class Humain {
	private:
		Couleur couleur;

		bool coordonneesValides(Terrain & t, int x, int y);
		unsigned int choixCoordonnees(Terrain & t);
		std::string choixDirection();

	public:
		Humain(Couleur c);
		void joue(Terrain & t);
};

#endif