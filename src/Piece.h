#ifndef PIECE_H
#define PIECE_H

enum Couleur {
	rouge,
	noir
};

class Piece {
	protected:
		unsigned int x,y;
		Couleur couleur;

	public:
		Piece();
		Piece(unsigned int Px, unsigned int Py);
		Piece(unsigned int Px, unsigned int Py, Couleur Pcouleur);

		Couleur getCouleur() const;

		void testRegression();
};

#endif