#ifndef TERRAIN_H
#define TERRAIN_H

#include <string>
#include <iostream>

class Piece;

class Terrain {

	private:
        Piece* grille[9][7]; // tableau statique de pointeurs sur Piece

		void realiseCoup(unsigned int ax, unsigned int ay, unsigned int nx, unsigned int ny, bool recule);

	public:
        Terrain(const std::string & fichier);
		Terrain(const Terrain & t);
		~Terrain();

		Piece* getPiece(unsigned int x, unsigned int y) const;

		bool verifieCoup(unsigned int ax, unsigned int ay, unsigned int nx, unsigned int ny, bool recule);

		friend std::ostream& operator<<(std::ostream& os, const Terrain& t);

		void testRegression();
};

#endif
