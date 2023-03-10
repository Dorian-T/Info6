#include "Joueur.h"
#include "Terrain.h"

class Jeu {
	private:
		Joueur J1 = Joueur(rouge, false);
		Joueur J2 = Joueur(noir, false);

		bool joueur1;
		bool fin;

		Terrain terrain;

		void joueurSuivant(); // change le joueur courant
		void affiche(); // affiche le plateau
		void finDePartie(); // affiche le gagnant

	public:
		Jeu();
		void boucle();
};