#ifndef JEU_H
#define JEU_H

#include "../core/Terrain.h"
#include "Humain.h"
#include "Robot.h"

#include <string>

// classe rassemblant les joueurs et le terrain
class Jeu {
	private:
		Humain J1 = Humain(rouge);			// joueur 1 (humain)
		Robot J2 = Robot(noir);				// joueur 2 (robot)
		bool joueur1;						// booléen indiquant si c'est au tour du joueur 1
		bool fin;							// booléen indiquant si la partie est finie
		Terrain *terrain;					// terrain de jeu
		std::string nomFichierSauvegarde;	// nom du fichier de sauvegarde

		void joueurSuivant(); // change le joueur courant
		void finDePartie(); // affiche le gagnant

		// fonctions permettant de sauvegarder la partie
		void jour(std::string & jour); // renvoie le jour sur deux chiffres
		void mois(std::string & mois); // renvoie le mois sur deux chiffres
		void date(std::string & date); // renvoie la date et l'heure actuelle formatée
		void sauvegarde();
		void infoPartie(); // sauvegarde les informations de la partie en début de fichier

	public:
		// constructeur
		Jeu(const std::string & filename);

		// fonction principale permettant de jouer une partie
		void boucle();
};

#endif