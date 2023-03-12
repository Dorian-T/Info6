#ifndef TERRAINTEST_H
#define TERRAINTEST_H

class Piece;

class Terrain {
    private:
        Piece* grilleTest[5][3];;

    public:
        TerrainTest()
        ~TerrainTest();

        Piece* getPieceTest(unsigned int x, unsigned int y) const;

        bool verifieCaseTest(unsigned int ax, unsigned int ay, unsigned int nx, unsigned int ny, bool recule);

        void testRegression();
};

#endif

