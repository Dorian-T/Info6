#ifndef ROBOT_H
#define ROBOT_H

#include "../core/Piece.h"
#include "../core/Terrain.h"

#include <string>
#include <vector>


class Robot {
	private:
		Couleur couleur;

		// pour les évaluations :
		Terrain *copieTerrain;
		Piece *donjon1;
		Piece *donjon2;

		// coup à jouer :
		unsigned int meilleurCoupDepart;
		unsigned int meilleurCoupArrivee;
		float meilleurScore;

		void deplacerFantassin(Terrain & t, unsigned int x, unsigned int y);
		void deplacerPaladin(Terrain & t, unsigned int x, unsigned int y);
		void deplacerArcher(Terrain & t, unsigned int x, unsigned int y);

		void evaluer(const Terrain & t);
		void trouverDonjon(const Terrain & t);
		int evaluerPiece(Type t);
		int evaluerSiege(const Piece & P);
		int evaluerPosition(const Piece & P, const Terrain & t);
		int distance(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);

	public:
		Robot(Couleur c);
		~Robot();

		void joue(Terrain & t);

		void testRegression();
};

#endif