#ifndef TERRAIN_H
#define TERRAIN_H

class Piece;

class Terrain {
	private:
        Piece* grille[9][7];

	public:
		Terrain();
        TerrainTest()
		~Terrain();

		Piece* getPiece(unsigned int x, unsigned int y) const;

		bool verifieCase(unsigned int ax, unsigned int ay, unsigned int nx, unsigned int ny, bool recule);

		void testRegression();
};

#endif
