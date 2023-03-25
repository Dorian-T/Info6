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
	if(c == 'o') J1 = Joueur(rouge, true);
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

void Jeu::affiche() {
	Piece* P;
	for(int i = 0; i < 9; i++) {
		for(int j = 0; j < 7; j++) {
			P = terrain.getPiece(j, i);
			if (P == NULL)
				cout << ".  ";
			else
				if(P->getCouleur() == rouge)
					switch (P->getType()) {
						case donjon:
							cout << "D  ";
							break;
						case tour_de_siege:
							cout << "T  ";
							break;
						case fantassin:
							cout << "F  ";
							break;
						case paladin:
							cout << "P  ";
							break;
						case archer:
							cout << "A  ";
							break;
					}
				else
					switch (P->getType()) {
						case donjon:
							cout << "d  ";
							break;
						case tour_de_siege:
							cout << "t  ";
							break;
						case fantassin:
							cout << "f  ";
							break;
						case paladin:
							cout << "p  ";
							break;
						case archer:
							cout << "a  ";
							break;
					}
		}
		cout << endl;
	}
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