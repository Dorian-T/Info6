#include "../core/Piece.h"
#include <vector>

class Joueur {
	private:
		Couleur couleur;
		bool robot;
		// vector<Piece*> pieces; // les pieces du joueur

		bool coordonneesValides(Terrain & t, int x, int y);
		void joueHumain(Terrain & t);
		unsigned int hChoixCoordonnees(Terrain & t);
		string hChoixDirection();

		void joueRobot(Terrain & t);

	public:
		Joueur(Couleur c, bool r);
		void Joue(Terrain & t);
};