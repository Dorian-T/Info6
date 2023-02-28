#include "Piece.h"
#include "Siege.h"
#include "Terrain.h"
#include <iostream>

Piece::Piece(unsigned int Px, unsigned int Py, Couleur Pcouleur, Type Ptype) {
	x = Px;
	y = Py;
	couleur = Pcouleur;
	type = fantassin;
	siege = NULL;
}

Piece::~Piece() {
	if(siege != NULL) delete siege;
	siege = NULL;
}

Couleur Piece::getCouleur() const {
	return couleur;
}

Type Piece::getType() const {
	return type;
}

Siege* Piece::getSiege() const {
	return siege;
}

void Piece::setSiege(Siege * Fsiege) {
	siege = Fsiege;
}

// il faut verifier quand on vas en arriere que c'est bien pour manger

void Piece::deplacerH(Terrain & t) {
	if(type == fantassin || type == archer) {
		if(couleur == rouge)
			if(t.verifieCase(x,y-1)) y--;
		else
			if(t.verifieCase(x,y+1)) y++;
	}
}

void Piece::deplacerHD(Terrain & t) {
	if(type == paladin || type == archer) {
		if(couleur == rouge)
			if(t.verifieCase(x+1,y-1)) {
				x++;
				y--;
			}
		else
			if(t.verifieCase(x-1,y+1)) {
				x--;
				y++;
			}
	}
}

void Piece::deplacerD(Terrain & t) {
	if(type == fantassin || type == archer) {
		if(couleur == rouge)
			if(t.verifieCase(x+1,y)) x++;
		else
			if(t.verifieCase(x+1,y)) x--;
	}
}

void Piece::deplacerBD(Terrain & t) {
	if(type == paladin || type == archer) {
		if(couleur == rouge)
			if(t.verifieCase(x+1,y+1)) {
				x++;
				y++;
			}
		else
			if(t.verifieCase(x-1,y-1)) {
				x--;
				y--;
			}
	}
}

void Piece::deplacerB(Terrain & t) {
	if(type == fantassin || type == archer) {
		if(couleur == rouge)
			if(t.verifieCase(x,y+1)) y++;
		else
			if(t.verifieCase(x,y-1)) y--;
	}
}

void Piece::deplacerBG(Terrain & t) {
	if(type == paladin || type == archer) {
		if(couleur == rouge)
			if(t.verifieCase(x-1,y+1)) {
				x--;
				y++;
			}
		else
			if(t.verifieCase(x+1,y-1)) {
				x++;
				y--;
			}
	}
}

void Piece::deplacerG(Terrain & t) {
	if(type == fantassin || type == archer) {
		if(couleur == rouge)
			if(t.verifieCase(x-1,y)) x--;
		else
			if(t.verifieCase(x+1,y)) x++;
	}
}

void Piece::deplacerHG(Terrain & t) {
	if(type == paladin || type == archer) {
		if(couleur == rouge)
			if(t.verifieCase(x-1,y-1)) {
				x--;
				y--;
			}
		else
			if(t.verifieCase(x+1,y+1)) {
				x++;
				y++;
			}
	}
}