#ifndef PIECE_H
#define PIECE_H

enum Couleur {
	rouge,
	noir
};

enum Type {
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
		Piece();
		Piece(unsigned int Px, unsigned int Py);
		Piece(unsigned int Px, unsigned int Py, Couleur Pcouleur);
		Piece(unsigned int Px, unsigned int Py, Couleur Pcouleur, Type Ptype);

		Couleur getCouleur() const;
		Type getType() const;

		void testRegression();
};

#endif