#include "Jeu.h"
#include "../core/Piece.h"
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

Jeu::Jeu() {
	time_t tmm = time(NULL);
	string dt = ctime(&tmm);
	nomFichierSauvegarde = "data/sauvegarde - " + dt + ".txt";
	char c;
	cout << "Est-ce que le joueur 1 est un robot ? (o/n) ";
	cin >> c;
	if(c == 'o') J1 = Joueur(rouge, true); // mettre un mutateur à la place
	cout << "Est-ce que le joueur 2 est un robot ? (o/n) ";
	cin >> c;
	if(c == 'o') J2 = Joueur(noir, true);
	joueur1 = true;
	fin = false;
}

void Jeu::boucle() {
	cout << terrain;
	sauvegarde(nomFichierSauvegarde);
	while (!fin) {
		if (joueur1) {
			cout << "Joueur 1 : ";
			J1.Joue(terrain);
		}
		else {
			cout << "Joueur 2 : ";
			J2.Joue(terrain);
		}
		joueurSuivant();
		cout << terrain;
		sauvegarde(nomFichierSauvegarde);
	}
	finDePartie();
}

void Jeu::joueurSuivant() {
	joueur1 = !joueur1;
}

void Jeu::finDePartie() {
	cout << endl << endl << "Bravo au gagnant !";
}

void Jeu::sauvegarde(const string & nomFichier) {
	ofstream fichier(nomFichier.c_str(), ios::app);
	if(fichier) {
		fichier << terrain;
		fichier << endl << endl;
		fichier.close();
	}
	else
		cout << "Impossible d'ouvrir le fichier " << nomFichier << endl;
}
