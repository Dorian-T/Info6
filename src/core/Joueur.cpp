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
	if (robot) JoueRobot(t);
	else joueHumain(t);
}

void Joueur::joueHumain(Terrain & t) {
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
	if(s == "h") P->deplacer(t, 0);
	else if(s == "hd") P->deplacer(t, 1);
	else if(s == "d") P->deplacer(t, 2);
	else if(s == "bd") P->deplacer(t, 3);
	else if(s == "b") P->deplacer(t, 4);
	else if(s == "bg") P->deplacer(t, 5);
	else if(s == "g") P->deplacer(t, 6);
	else if(s == "hg") P->deplacer(t, 7);
}

bool Joueur::coordonneesValides(Terrain & t, int x, int y) {
	if(x < 0 || x > 6 || y < 0 || y > 8) return false;
	Piece* P = t.getPiece(x, y);
	if(P == NULL) return false;
	if(P->getCouleur() != couleur) return false;
	if(P->getType() == donjon || P->getType() == tour_de_siege) return false;
	return true;
}