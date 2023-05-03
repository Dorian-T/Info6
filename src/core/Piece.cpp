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
	siege = NULL;
	menace = 0;
}

Piece::Piece(const Piece & P) {
	x = P.x;
	y = P.y;
	couleur = P.couleur;
	type = P.type;
	if(P.siege != NULL) siege = new Piece(*(P.siege));
	else siege = NULL;
	menace = P.menace;
}

Piece::~Piece() {
	if(siege != NULL) delete siege;
}

unsigned int Piece::getX() const {
	return x;
}

unsigned int Piece::getY() const {
	return y;
}

Couleur Piece::getCouleur() const {
	return couleur;
}

Type Piece::getType() const {
	return type;
}

Piece* Piece::getSiege() const {
	assert(type != donjon && type != tour_de_siege);
	return siege;
}

unsigned int Piece::getMenace(Terrain & t) {
	assert(type == donjon);
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
	return menace;
}

void Piece::calculMenaceCase(Terrain & t, Piece * p, Type ty) {
	if(p != NULL)
		if(p->getCouleur() != couleur)
			if(p->getType() == ty || p->getType() == archer) {
				if(p->getSiege() == NULL) menace++;
				else menace += 2;
			}
}

void Piece::setSiege(Piece* S) {
	assert(type != donjon && type != tour_de_siege);
	assert(S == NULL || S->getType() == tour_de_siege);
	siege = S;
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
			if(t.verifieCoup(x, y, x, y-1, false)) y--;
			else return false;
		else
			if(t.verifieCoup(x, y, x, y+1, false)) y++;
			else return false;
	else return false;
	return true;
}

bool Piece::deplacerHD(Terrain & t) {
	if(type == paladin || type == archer)
		if(couleur == rouge)
			if(t.verifieCoup(x, y, x+1, y-1, false)) {
				x++;
				y--;
			}
			else return false;
		else
			if(t.verifieCoup(x, y, x-1, y+1, false)) {
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
			if(t.verifieCoup(x, y, x+1, y, false)) x++;
			else return false;
		else
			if(t.verifieCoup(x, y, x-1, y, false)) x--;
			else return false;
	else return false;
	return true;
}

bool Piece::deplacerBD(Terrain & t) {
	if(type == paladin)
		if(couleur == rouge)
			if(t.verifieCoup(x, y, x+1, y+1, true)) {
				x++;
				y++;
			}
			else return false;
		else
			if(t.verifieCoup(x, y, x-1, y-1, true)) {
				x--;
				y--;
			}
			else return false;
	else if(type == archer)
		if(couleur == rouge)
			if(t.verifieCoup(x, y, x+1, y+1, false)) {
				x++;
				y++;
			}
			else return false;
		else
			if(t.verifieCoup(x, y, x-1, y-1, false)) {
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
			if(t.verifieCoup(x, y, x, y+1, true)) y++;
			else return false;
		else
			if(t.verifieCoup(x, y, x, y-1, true)) y--;
			else return false;
	else if(type == archer)
		if(couleur == rouge)
			if(t.verifieCoup(x, y, x, y+1, false)) y++;
			else return false;
		else
			if(t.verifieCoup(x, y, x, y-1, false)) y--;
			else return false;
	else return false;
	return true;
}

bool Piece::deplacerBG(Terrain & t) {
	if(type == paladin)
		if(couleur == rouge)
			if(t.verifieCoup(x, y, x-1, y+1, true)) {
				x--;
				y++;
			}
			else return false;
		else
			if(t.verifieCoup(x, y, x+1, y-1, true)) {
				x++;
				y--;
			}
			else return false;
	else if(type == archer)
		if(couleur == rouge)
			if(t.verifieCoup(x, y, x-1, y+1, false)) {
				x--;
				y++;
			}
			else return false;
		else
			if(t.verifieCoup(x, y, x+1, y-1, false)) {
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
			if(t.verifieCoup(x, y, x-1, y, false)) x--;
			else return false;
		else
			if(t.verifieCoup(x, y, x+1, y, false)) x++;
			else return false;
	}
	else return false;
	return true;
}

bool Piece::deplacerHG(Terrain & t) {
	if(type == paladin || type == archer) {
		if(couleur == rouge)
			if(t.verifieCoup(x, y, x-1, y-1, false)) {
				x--;
				y--;
			}
			else return false;
		else
			if(t.verifieCoup(x, y, x+1, y+1, false)) {
				x++;
				y++;
			}
			else return false;
		}
	else return false;
	return true;
}

void Piece::testRegression() {
	cout << endl << "Test Piece" << endl;

	assert(x == 1); assert(y == 2);
	assert(couleur == rouge); assert(type == paladin);
	assert(siege == NULL);
	cout << "\tTest constructeur parametre : OK" << endl;

	assert(getX() == x); assert(getY() == y);
	cout << "\tTest getX et getY : OK" << endl;

	assert(getCouleur() == couleur); assert(getType() == type);
	cout << "\tTest getCouleur et getType : OK" << endl;

	assert(getSiege() == siege);
	cout << "\tTest getSiege : OK" << endl;

	Piece *S = new Piece(1, 2, rouge, tour_de_siege);
	setSiege(S);
	assert(siege == S);
	cout << "\tTest setSiege : OK" << endl;

	Piece copie(*this);
	assert(copie.getX() == x); assert(copie.getY() == y);
	assert(copie.getCouleur() == couleur); assert(copie.getType() == type);
	assert(copie.getSiege() != NULL);
	assert(copie.getSiege()->getX() == S->getX()); assert(copie.getSiege()->getY() == S->getY());
	assert(copie.getSiege()->getCouleur() == S->getCouleur()); assert(copie.getSiege()->getType() == S->getType());
	cout << "\tTest constructeur par copie : OK" << endl;

	cout << "Test Piece : OK" << endl;
}