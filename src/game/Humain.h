#ifndef HUMAIN_H
#define HUMAIN_H

#include "../core/Piece.h"
#include "../core/Terrain.h"

// classe représentant un joueur humain
class Humain {
	private:
		Couleur couleur; // couleur du joueur

		// fonctions permettant de choisir et vérifier un coup
		bool coordonneesValides(Terrain & t, int x, int y);
		Piece* choixCoordonnees(Terrain & t);
		bool choixDirection(Terrain & t, Piece * P);

	public:
		// constructeur
		Humain(Couleur c);

		// fonction principale permettant de jouer un tour
		void joue(Terrain & t);
};

#endif