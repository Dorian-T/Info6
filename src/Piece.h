#ifndef PIECE_H
#define PIECE_H

#include "Siege.h"
#include "Terrain.h"

enum Type {
	fantassin,
	paladin,
	archer
};

class Piece
{
	private:
		unsigned int x,y;
		Couleur couleur;
		Type type;
		Siege* siege;
	
	public:
		Piece(unsigned int Px, unsigned int Py, Couleur Pcouleur, Type Ptype);
		~Piece();

		Couleur getCouleur() const;
		Type getType() const;
		Siege* getSiege() const;
		void setSiege(Siege* Fsiege);

		void deplacerH(Terrain & t);
		void deplacerHD(Terrain & t);
		void deplacerD(Terrain & t);
		void deplacerBD(Terrain & t);
		void deplacerB(Terrain & t);
		void deplacerBG(Terrain & t);
		void deplacerG(Terrain & t);
		void deplacerHG(Terrain & t);
};

#endif

