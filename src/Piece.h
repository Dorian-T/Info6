#ifndef PIECE_H
#define PIECE_H

class Siege;

enum Couleur {
	rouge,
	noir
};

enum Type {
	donjon,
	siege,
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

		Siege* getSiege() const;

		void testRegression();
};

#endif