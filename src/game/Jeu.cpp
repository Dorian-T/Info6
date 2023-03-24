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

void Jeu::affiche() { // A mofifier pour mettre en minuscule les pieces noires
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