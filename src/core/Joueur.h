#include "Piece.h"
#include <vector>

class Joueur {
	private:
		bool couleur;
		bool robot;
		// vector<Piece*> pieces; // les pieces du joueur

		bool coordonneesValides(Terrain & t, int x, int y);
	public:
		Joueur(Couleur c, bool r);
		void Joue(Terrain & t);
};