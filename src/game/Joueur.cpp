#include "../core/Piece.h"
#include "../core/Soldat.h"
#include "../core/Terrain.h"
#include "Joueur.h"
#include <iostream>
#include <string.h>
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
	string s;
	Piece* P;
	do {
		do {
			i = hChoixCoordonnees(t);
			P = t.getPiece(i % 10, i / 10);
		} while(P->getType() == donjon || P->getType() == tour_de_siege);
		Soldat S(i%10, i/10, P->getCouleur(), P->getType()); // deplace pas le bon soldat !
		s = hChoixDirection();
		if(S.deplacer(t, s)) cout << "deplacement reussi" << endl;
		else cout << "deplacement impossible" << endl;
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

string Joueur::hChoixDirection() {
	string s;
	cout << "Entrez une direction (h, hd, d, bd, b, bg, g, hg) : ";
	do {
		cin >> s;
	} while (s != "h" && s != "hd" && s != "d" && s != "bd" && s != "b" && s != "bg" && s != "g" && s != "hg");
	return s;
}

void Joueur::joueRobot(Terrain & t) {
	// TODO
}