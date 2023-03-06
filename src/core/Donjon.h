#ifndef DONJON_H
#define DONJON_H

#include "Piece.h"
#include "Terrain.h"

class Donjon: public Piece
{
	private:
		unsigned int menace;
		void rMenace(Terrain & t, Piece* p, Type ty);
		void regardeMenace(Terrain & t); // quand est-ce qu'on l'appelle ?

	public:
		Donjon();
		Donjon(unsigned int Px, unsigned int Py, Couleur Pcouleur);

		unsigned int getMenace() const;

		void testRegression(Terrain & t);
};

#endif
