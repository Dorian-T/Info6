#include "Piece.h"
#include "Terrain.h"
#include "Joueur.h"
#include <iostream>
#include <string.h>
using namespace std;

Joueur::Joueur(Couleur c, bool r) {
	robot = false;
	couleur = c;
}

void Joueur::Joue(Terrain & t) {
	if (robot) {
		// TODO
	} else {
		unsigned int i;
		cout << "Entrez les coordonnees de la piece a deplacer (yx) : ";
		do {
			cin >> i;
		} while (!coordonneesValides(t, i % 10, i / 10));
		Piece* P = t.getPiece(i % 10, i / 10);
		string s;
		cout << "Entrez une direction (h, hd, d, bd, b, bg, g, hg) : ";
		do {
			cin >> s;
		} while (s != "h" && s != "hd" && s != "d" && s != "bd" && s != "b" && s != "bg" && s != "g" && s != "hg");
		// TODO : deplacer la piece
	}
}

bool Joueur::coordonneesValides(Terrain & t, int x, int y) {
	if(x < 0 || x > 6 || y < 0 || y > 8) return false;
	Piece* P = t.getPiece(x, y);
	if(P == NULL) return false;
	if(P->getCouleur() != couleur) return false;
	if(P->getType() == donjon || P->getType() == tour_de_siege) return false;
	return true;
}