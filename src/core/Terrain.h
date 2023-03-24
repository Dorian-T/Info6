#ifndef TERRAIN_H
#define TERRAIN_H

#include <string>

class Piece;

class Terrain {

	private:
        Piece* grille[9][7]; // tableau statique de pointeurs sur Piece

	public:
		Terrain();
        Terrain(const std::string & fichier);
		~Terrain();

		Piece* getPiece(unsigned int x, unsigned int y) const;

		bool verifieCase(unsigned int ax, unsigned int ay, unsigned int nx, unsigned int ny, bool recule);

		void testRegression();
};

#endif
