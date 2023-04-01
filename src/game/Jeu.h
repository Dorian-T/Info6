#include "Joueur.h"
#include "../core/Terrain.h"
#include <string>

class Jeu {
	private:
		Joueur J1 = Joueur(rouge, false);
		Joueur J2 = Joueur(noir, false);

		bool joueur1;
		bool fin;

		Terrain terrain;

		std::string nomFichierSauvegarde;

		void joueurSuivant(); // change le joueur courant
		void finDePartie(); // affiche le gagnant

		void mois(std::string & mois); // renvoie le mois en chiffres
		void date(std::string & date); // renvoie la date et l'heure actuelle formatee
		void sauvegarde(const std::string & nomFichier); // sauvegarde la partie

	public:
		Jeu();
		void boucle();
};