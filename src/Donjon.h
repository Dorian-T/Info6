#ifndef DONJON_H
#define DONJON_H

#include "Piece.h"

class Donjon: public Piece
{
	private:
		unsigned int menace;
		unsigned int regardeMenace();

	public:
		Donjon(unsigned int Px, unsigned int Py, Couleur Pcouleur);
		unsigned int getMenace() const;
		void testRegression();
};

#endif
