#include "../core/Piece.h"
#include "../core/Terrain.h"
#include "Joueur.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

Joueur::Joueur(Couleur c, bool r) {
	robot = false;
	couleur = c;
}

void Joueur::Joue(Terrain & t) {
	if (robot) joueRobot(t);
	else joueHumain(t);
}

bool Joueur::coordonneesValides(Terrain & t, int x, int y) {
	if(x < 0 || x > 6 || y < 0 || y > 8) return false;
	Piece* P = t.getPiece(x, y);
	if(P == NULL) return false;
	if(P->getCouleur() != couleur) return false;
	if(P->getType() == donjon || P->getType() == tour_de_siege) return false;
	return true;
}

void Joueur::joueHumain(Terrain & t) {
	unsigned int i;
	vector<string> v;
	string s;
	Piece * P;
	do {
		// coordonnees
		do {
			i = hChoixCoordonnees(t);
			P = t.getPiece(i % 10, i / 10);
			if(P->getType() == donjon || P->getType() == tour_de_siege) cout << "Cette piece n'est pas deplacable." << endl;
		} while(P->getType() == donjon || P->getType() == tour_de_siege);

		// direction
		cout << "Entrez une direction (";
		if(P->getType() == fantassin) {
			cout << "h, d, b, g) : ";
			do {
				cin >> s;
			} while (s != "h" && s != "d" && s != "b" && s != "g");
		}
		else if(P->getType() == paladin) {
			cout << "hd, bd, bg, hg) : ";
			do {
				cin >> s;
			} while (s != "hd" && s != "bd" && s != "bg" && s != "hg");
		}
		else {
			cout << "h, hd, d, bd, b, bg, g, hg) : ";
			do {
				cin >> s;
			} while (s != "h" && s != "hd" && s != "d" && s != "bd" && s != "b" && s != "bg" && s != "g" && s != "hg");
		}
	} while(!P->deplacer(t, s));
}

unsigned int Joueur::hChoixCoordonnees(Terrain & t) {
	unsigned int i;
	cout << "Entrez les coordonnees de la piece a deplacer (yx) : ";
	do {
		cin >> i;
	} while (!coordonneesValides(t, i % 10, i / 10));
	return i;
}

void Joueur::joueRobot(Terrain & t) {
	// TODO
}