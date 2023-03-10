#include "Jeu.h"
#include "../core/Piece.h"
#include <iostream>
using namespace std;

Jeu::Jeu() {
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
	affiche();
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
		affiche();
	}
	finDePartie();
}

void Jeu::joueurSuivant() {
	joueur1 = !joueur1;
}

void Jeu::affiche() {
	Piece* P;
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 7; j++) {
			P = terrain.getPiece(j, i);
			if (P == NULL)
				cout << "  ";
			else
				switch (P->getType()) {
					case donjon:
						cout << "D ";
						break;
					case tour_de_siege:
						cout << "T ";
						break;
					case fantassin:
						cout << "F ";
						break;
					case paladin:
						cout << "P ";
						break;
					case archer:
						cout << "A ";
						break;
				}
		}
	cout << endl;
}

void Jeu::finDePartie() {
	// TODO
}