#include "Piece.h"
#include "Terrain.h"
#include <assert.h>
#include <iostream>
#include <string>
using namespace std;

Piece::Piece(unsigned int X, unsigned int Y, Couleur C, Type T) {
	x = X;
	y = Y;
	couleur = C;
	type = T;
}

Piece::~Piece() {
	if(siege != NULL) delete siege;
}

Couleur Piece::getCouleur() const {
	return couleur;
}

Type Piece::getType() const {
	return type;
}

Piece* Piece::getSiege() const {
	assert(type != donjon);
	return siege;
}

unsigned int Piece::getMenace(Terrain & t) {
	assert(type == donjon);
	calculMenace(t);
	return menace;
}

void Piece::setSiege(Piece* S) {
	if(type == fantassin || type == paladin || type == archer) {
		assert(S->getType() == tour_de_siege);
		siege = S;
	}
	else if(type == tour_de_siege) {
		assert(S->getType() == fantassin || S->getType() == paladin || S->getType() == archer);
		siege = S;
	}
	else assert(false);
}

bool Piece::deplacer(Terrain & t, const string & s) {
	if(type == fantassin || type == paladin || type == archer) {
		if(s == "h") return deplacerH(t);
		else if(s == "hd") return deplacerHD(t);
		else if(s == "d") return deplacerD(t);
		else if(s == "bd") return deplacerBD(t);
		else if(s == "b") return deplacerB(t);
		else if(s == "bg") return deplacerBG(t);
		else if(s == "g") return deplacerG(t);
		else if(s == "hg") return deplacerHG(t);
		else return false;
	}
	else return false;
}

bool Piece::deplacerH(Terrain & t) {
	if(type == fantassin || type == archer)
		if(couleur == rouge)
			if(t.verifieCase(x, y, x, y-1, false)) y--;
			else return false;
		else
			if(t.verifieCase(x, y, x, y+1, false)) y++;
			else return false;
	else return false;
	return true;
}

bool Piece::deplacerHD(Terrain & t) {
	if(type == paladin || type == archer)
		if(couleur == rouge)
			if(t.verifieCase(x, y, x+1, y-1, false)) {
				x++;
				y--;
			}
			else return false;
		else
			if(t.verifieCase(x, y, x-1, y+1, false)) {
				x--;
				y++;
			}
			else return false;
	else return false;
	return true;
}

bool Piece::deplacerD(Terrain & t) {
	if(type == fantassin || type == archer)
		if(couleur == rouge)
			if(t.verifieCase(x, y, x+1, y, false)) x++;
			else return false;
		else
			if(t.verifieCase(x, y, x+1, y, false)) x--;
			else return false;
	else return false;
	return true;
}

bool Piece::deplacerBD(Terrain & t) {
	if(type == paladin)
		if(couleur == rouge)
			if(t.verifieCase(x, y, x+1, y+1, true)) {
				x++;
				y++;
			}
			else return false;
		else
			if(t.verifieCase(x, y, x-1, y-1, true)) {
				x--;
				y--;
			}
			else return false;
	else if(type == archer)
		if(couleur == rouge)
			if(t.verifieCase(x, y, x+1, y+1, false)) {
				x++;
				y++;
			}
			else return false;
		else
			if(t.verifieCase(x, y, x-1, y-1, false)) {
				x--;
				y--;
			}
			else return false;
	else return false;
	return true;
}

bool Piece::deplacerB(Terrain & t) {
	if(type == fantassin)
		if(couleur == rouge)
			if(t.verifieCase(x, y, x, y+1, true)) y++;
			else return false;
		else
			if(t.verifieCase(x, y, x, y-1, true)) y--;
			else return false;
	else if(type == archer)
		if(couleur == rouge)
			if(t.verifieCase(x, y, x, y+1, false)) y++;
			else return false;
		else
			if(t.verifieCase(x, y, x, y-1, false)) y--;
			else return false;
	else return false;
	return true;
}

bool Piece::deplacerBG(Terrain & t) {
	if(type == paladin)
		if(couleur == rouge)
			if(t.verifieCase(x, y, x-1, y+1, true)) {
				x--;
				y++;
			}
			else return false;
		else
			if(t.verifieCase(x, y, x+1, y-1, true)) {
				x++;
				y--;
			}
			else return false;
	else if(type == archer)
		if(couleur == rouge)
			if(t.verifieCase(x, y, x-1, y+1, false)) {
				x--;
				y++;
			}
			else return false;
		else
			if(t.verifieCase(x, y, x+1, y-1, false)) {
				x++;
				y--;
			}
			else return false;
	else return false;
	return true;
}

bool Piece::deplacerG(Terrain & t) {
	if(type == fantassin || type == archer) {
		if(couleur == rouge)
			if(t.verifieCase(x, y, x-1, y, false)) x--;
			else return false;
		else
			if(t.verifieCase(x, y, x+1, y, false)) x++;
			else return false;
	}
	else return false;
	return true;
}

bool Piece::deplacerHG(Terrain & t) {
	if(type == paladin || type == archer) {
		if(couleur == rouge)
			if(t.verifieCase(x, y, x-1, y-1, false)) {
				x--;
				y--;
			}
			else return false;
		else
			if(t.verifieCase(x, y, x+1, y+1, false)) {
				x++;
				y++;
			}
			else return false;
		}
	else return false;
	return true;
}

void Piece::calculMenace(Terrain & t) {
	if (couleur == rouge) {
		calculMenaceCase(t, t.getPiece(x-1, y), fantassin);
		calculMenaceCase(t, t.getPiece(x-1, y-1), paladin);
		calculMenaceCase(t, t.getPiece(x, y-1), fantassin);
		calculMenaceCase(t, t.getPiece(x+1, y-1), paladin);
		calculMenaceCase(t, t.getPiece(x+1, y), fantassin);
	}
	else {
		calculMenaceCase(t, t.getPiece(x-1, y), fantassin);
		calculMenaceCase(t, t.getPiece(x-1, y+1), paladin);
		calculMenaceCase(t, t.getPiece(x, y+1), fantassin);
		calculMenaceCase(t, t.getPiece(x+1, y+1), paladin);
		calculMenaceCase(t, t.getPiece(x+1, y), fantassin);
	}
}

void Piece::calculMenaceCase(Terrain & t, Piece * p, Type ty) {
	if(p != NULL)
		if(p->getCouleur() != couleur)
			if(p->getType() == ty || p->getType() == archer)
				if(p->getSiege() == NULL) menace++;
				else menace += 2;
}

// void Piece::testRegression() {
// 	cout << "Test Piece" << endl;

// 	cout << "\tTest constructeur par defaut : OK" << endl;

// 	Piece P(1, 2);
// 	assert(P.x == 1); assert(P.y == 2);
// 	cout << "\tTest constructeur parametre 1 : OK" << endl;

// 	Piece P2(2, 3, rouge);
// 	assert(P2.x == 2); assert(P2.y == 3); assert(P2.couleur == rouge);
// 	cout << "\tTest constructeur parametre 2 : OK" << endl;

// 	assert(P2.getCouleur() == rouge);
// 	cout << "\tTest getCouleur : OK" << endl;

// 	cout << "Test Piece : OK" << endl << endl;
// }