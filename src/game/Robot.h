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
		Piece *donjons[4];

		// coup à jouer :
		int score;
		int departX;
		int departY;
		int arriveeX;
		int arriveeY;


		void deplacerFantassin(const Terrain & t, unsigned int x, unsigned int y);
		void deplacerPaladin(const Terrain & t, unsigned int x, unsigned int y);
		void deplacerArcher(const Terrain & t, unsigned int x, unsigned int y);


		// évaluation :
		void trouveMeilleurCoup(unsigned int dx, unsigned int dy, unsigned int ax, unsigned int ay);
		int evaluer();
		void trouverDonjon(const Terrain & t);

		int evaluerPiece(Type t);

		int evaluerAttaque(const Piece & P);
		int evaluerUneAttaque(unsigned int x, unsigned int y, Couleur c);

		int evaluerSiege(const Piece & P);

		int evaluerPosition(const Piece & P);
		int distance(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);

	public:
		Robot(Couleur c);
		~Robot();

		void joue(Terrain & t);

		void testRegression();
};

#endif