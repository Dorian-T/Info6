#ifndef PIECE_H
#define PIECE_H

#include "Terrain.h"
#include <string>

class Terrain;

enum Couleur {
	rouge,
	noir
};

enum Type {
	donjon,
	tour_de_siege,
	fantassin,
	paladin,
	archer
};

class Piece {

	private:
		unsigned int x, y; // position
		Couleur couleur; // couleur
		Type type; // type
		Piece* siege; // pointeur vers la tour de siege du soldat
		unsigned int menace; // nombre de menaces que recoit le donjon

		// fonctions de deplacement des fantassins, paladins et archers
		bool deplacerH(Terrain & t);
		bool deplacerHD(Terrain & t);
		bool deplacerD(Terrain & t);
		bool deplacerBD(Terrain & t);
		bool deplacerB(Terrain & t);
		bool deplacerBG(Terrain & t);
		bool deplacerG(Terrain & t);
		bool deplacerHG(Terrain & t);

		// calcul la menace d'une case
		void calculMenaceCase(Terrain & t, Piece * p, Type ty);

	public:
		Piece(unsigned int X, unsigned int Y, Couleur C, Type T);
		Piece(const Piece & P);
		~Piece();

		// accesseurs
		unsigned int getX() const;
		unsigned int getY() const;
		Couleur getCouleur() const;
		Type getType() const;
		Piece* getSiege() const;
		unsigned int getMenace(Terrain & t); // calcul la menace d'un donjon et la retourne

		// mutateur
		void setSiege(Piece* S);


		// deplace les fantassins, paladins et archers
		bool deplacer(Terrain & t, const std::string & s);

		void testRegression();
};

#endif