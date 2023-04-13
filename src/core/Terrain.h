#ifndef TERRAIN_H
#define TERRAIN_H

#include <string>
#include <iostream>

class Piece;

class Terrain {

	private:
        Piece* grille[9][7]; // tableau statique de pointeurs sur Piece

	public:
		Terrain(); // TODO : à supprimer
        Terrain(const std::string & fichier);
		~Terrain();

		Piece* getPiece(unsigned int x, unsigned int y) const;

		bool verifieCase(unsigned int ax, unsigned int ay, unsigned int nx, unsigned int ny, bool recule);

		friend std::ostream& operator<<(std::ostream& os, const Terrain& t);

		void testRegression();
};

#endif
