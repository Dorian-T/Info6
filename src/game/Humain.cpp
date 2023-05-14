#include "Humain.h"

#include <iostream>

using namespace std;


// constructeur

Humain::Humain(Couleur c) {
	couleur = c;
}


// fonctions permettant de choisir et vérifier un coup

void Humain::joue(Terrain & t) {
	Piece *P;
	do {
		P = choixCoordonnees(t);
	} while(!choixDirection(t, P));
}

Piece* Humain::choixCoordonnees(Terrain & t) {
	unsigned int i;
	do {
		cout << "Entrez les coordonnees de la piece a deplacer (yx) : ";
		cin >> i;
	} while (!coordonneesValides(t, i % 10, i / 10));
	return t.getPiece(i % 10, i / 10);
}

bool Humain::coordonneesValides(Terrain & t, int x, int y) {
	if(x < 0 || x > 6 || y < 0 || y > 8) return false;
	Piece* P = t.getPiece(x, y);
	if(P == NULL) return false;
	if(P->getCouleur() != couleur) return false;
	if(P->getType() == donjon || P->getType() == tour_de_siege) return false;
	return true;
}

bool Humain::choixDirection(Terrain & t, Piece * P) {
	string s;
	do {
		cout << "Entrez une direction (";
		if(P->getType() == fantassin) {
			cout << "H, D, B, G) : ";
			cin >> s;
		}
		else if(P->getType() == paladin) {
			cout << "HD, BD, BG, HG) : ";
			cin >> s;
		}
		else {
			cout << "H, HD, D, BD, B, BG, G, HG) : ";
			cin >> s;
		}
	} while (s != "H" && s != "HD" && s != "D" && s != "BD" && s != "B" && s != "BG" && s != "G" && s != "HG");
	return P->deplacer(t, s);
}