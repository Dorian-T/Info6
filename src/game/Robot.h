#ifndef ROBOT_H
#define ROBOT_H

#include "../core/Piece.h"
#include "../core/Terrain.h"

#include <string>
#include <vector>


struct Coup {
	Piece * piece;
	std::string direction;
	int score;
};

class Robot {
	private:
		Couleur couleur;
		Terrain *copieTerrain;
		unsigned int meilleurCoupDepart;
		unsigned int meilleurCoupArrivee;
		float meilleurScore;

		void deplacerFantassin(Terrain & t, unsigned int x, unsigned int y);
		void deplacerPaladin(Terrain & t, unsigned int x, unsigned int y);
		void deplacerArcher(Terrain & t, unsigned int x, unsigned int y);

		void evaluer(const Terrain & t);

	public:
		Robot(Couleur c);
		~Robot();

		void joue(Terrain & t);
};

#endif