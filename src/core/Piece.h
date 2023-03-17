#ifndef PIECE_H
#define PIECE_H

#include <string>

class Soldat;
class Siege;
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
	protected:
		unsigned int x,y;
		Couleur couleur;
		Type type;

	public:
		Piece(); // utile ?
		Piece(unsigned int Px, unsigned int Py); // utile ?
		Piece(unsigned int Px, unsigned int Py, Couleur Pcouleur);

		Couleur getCouleur() const;
		Type getType() const;

		unsigned int getX() const { // chut
			return x;
		}
		unsigned int getY() const {
			return y;
		}

		Piece* getSiege() const;
		Piece* getSoldat() const;
		void setSiege(Piece* Ssiege);
		void setSoldat(Piece* Ssoldat);
		unsigned int regardeMenace() const;
		bool deplacer(Terrain & t, const std::string & s);

		void testRegression();
};

#endif