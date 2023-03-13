#ifndef SOLDAT_H
#define SOLDAT_H

#include "Piece.h"
#include "Terrain.h"
#include <string>

class Siege;

class Soldat : public Piece
{
	private:
		Piece* siege;

		bool deplacerH(Terrain & t);
		bool deplacerHD(Terrain & t);
		bool deplacerD(Terrain & t);
		bool deplacerBD(Terrain & t);
		bool deplacerB(Terrain & t);
		bool deplacerBG(Terrain & t);
		bool deplacerG(Terrain & t);
		bool deplacerHG(Terrain & t);

	public:
		Soldat();
		Soldat(unsigned int Px, unsigned int Py, Couleur Pcouleur, Type Stype);
		~Soldat();

		Type getType() const;
		Piece* getSiege() const;
		void setSiege(Piece* Ssiege);

		bool deplacer(Terrain & t, const std::string & s);

		void testRegression();
};

#endif

