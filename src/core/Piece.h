#ifndef PIECE_H
#define PIECE_H

#include "Terrain.h"
#include <string>

class Terrain;

// type énuméré pour la couleur des pièces
enum Couleur {
	rouge,
	noir
};

// type énuméré pour le type des pièces
// les fantassins, paladins et archers sont des soldats
enum Type {
	donjon,
	tour_de_siege,
	fantassin,
	paladin,
	archer
};

// classe représentant une pièce
class Piece {

	private:
		unsigned int x, y;		// position
		Couleur couleur;		// couleur
		Type type;				// type
		Piece* siege;			// pointeur vers une tour de siege (uniquement pour les soldats)
		unsigned int menace;	// nombre de menaces que recoit un donjon

		// fonctions spécifiques de déplacement des soldats
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
		// constructeurs et destructeur
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


		// fonction principale de déplacement des soldats
		bool deplacer(Terrain & t, const std::string & s);

		// tests de non-régression
		void testRegression();
};

#endif