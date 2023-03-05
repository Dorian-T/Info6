#ifndef SOLDAT_H
#define SOLDAT_H

#include "Piece.h"
#include "Terrain.h"

class Siege;

class Soldat : public Piece
{
	private:
		Piece* siege;

	public:
		Soldat();
		Soldat(unsigned int Px, unsigned int Py, Couleur Pcouleur, Type Stype);
		~Soldat();

		Type getType() const;
		Piece* getSiege() const;
		void setSiege(Piece* Ssiege);

		void deplacerH(Terrain & t);
		void deplacerHD(Terrain & t);
		void deplacerD(Terrain & t);
		void deplacerBD(Terrain & t);
		void deplacerB(Terrain & t);
		void deplacerBG(Terrain & t);
		void deplacerG(Terrain & t);
		void deplacerHG(Terrain & t);

		void testRegression();
};

#endif

