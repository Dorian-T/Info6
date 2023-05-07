#ifndef TERRAIN_H
#define TERRAIN_H

#include "Piece.h"

#include <string>
#include <iostream>

class Piece;

// classe représentant le terrain de jeu
class Terrain {

	private:
        Piece* grille[9][7]; // tableau statique de pointeurs sur Piece

	public:
		// constructeurs et destructeur
        Terrain(const std::string & fichier);
		Terrain(const Terrain & t);
		~Terrain();

		// accesseur
		Piece* getPiece(unsigned int x, unsigned int y) const;

		// vérifie qu'un coup est valide et le joue
		bool verifieCoup(unsigned int ax, unsigned int ay, unsigned int nx, unsigned int ny, bool recule);

		// surcharge de l'opérateur <<
		friend std::ostream& operator<<(std::ostream& os, const Terrain& t);

		// tests de non-régression
		void testRegression();
};

#endif
