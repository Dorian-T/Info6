#include "../core/Terrain.h"
#include "Humain.h"
#include "Robot.h"

#include <string>


class Jeu {
	private:
		Humain J1 = Humain(rouge);
		Robot J2 = Robot(noir);

		bool joueur1;
		bool fin;

		Terrain *terrain;

		std::string nomFichierSauvegarde;

		void joueurSuivant(); // change le joueur courant
		void finDePartie(); // affiche le gagnant

		void jour(std::string & jour); // renvoie le jour sur deux chiffres
		void mois(std::string & mois); // renvoie le mois en chiffres
		void date(std::string & date); // renvoie la date et l'heure actuelle formatee
		void sauvegarde(const std::string & nomFichier); // sauvegarde la partie

	public:
		Jeu(const std::string & filename);
		void boucle();
};