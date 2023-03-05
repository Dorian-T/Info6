#include "Piece.h"
#include "Soldat.h"
#include "Siege.h"
#include "Terrain.h"
#include <iostream>
#include <assert.h>
using namespace std;

Soldat::Soldat() {
	siege = NULL;
}

Soldat::Soldat(unsigned int Px, unsigned int Py, Couleur Pcouleur, Type Ptype) : Piece(Px, Py, Pcouleur) {
	type = Ptype;
	siege = NULL;
}

Soldat::~Soldat() {
	if(siege != NULL) delete siege;
	siege = NULL;
}

Type Soldat::getType() const {
	return type;
}

Siege* Soldat::getSiege() const {
	return siege;
}

void Soldat::setSiege(Siege * Ssiege) {
	siege = Ssiege;
}

// il faut verifier quand on vas en arriere que c'est bien pour manger

void Soldat::deplacerH(Terrain & t) {
	if(type == fantassin || type == archer) {
		if(couleur == rouge)
			if(t.verifieCase(x,y-1)) y--;
		else
			if(t.verifieCase(x,y+1)) y++;
	}
}

void Soldat::deplacerHD(Terrain & t) {
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

void Soldat::deplacerD(Terrain & t) {
	if(type == fantassin || type == archer) {
		if(couleur == rouge)
			if(t.verifieCase(x+1,y)) x++;
		else
			if(t.verifieCase(x+1,y)) x--;
	}
}

void Soldat::deplacerBD(Terrain & t) {
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

void Soldat::deplacerB(Terrain & t) {
	if(type == fantassin || type == archer) {
		if(couleur == rouge)
			if(t.verifieCase(x,y+1)) y++;
		else
			if(t.verifieCase(x,y-1)) y--;
	}
}

void Soldat::deplacerBG(Terrain & t) {
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

void Soldat::deplacerG(Terrain & t) {
	if(type == fantassin || type == archer) {
		if(couleur == rouge)
			if(t.verifieCase(x-1,y)) x--;
		else
			if(t.verifieCase(x+1,y)) x++;
	}
}

void Soldat::deplacerHG(Terrain & t) {
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

void Soldat::testRegression() {
	cout << "Test de la classe Soldat" << endl;
	assert(siege == NULL);
	cout << "\tTest du constructeur : OK" << endl;
	Soldat Sr(1, 1, rouge, fantassin);
	Soldat Sn(2, 2, noir, paladin);
	assert(Sr.x == 1); assert(Sr.y == 1); assert(Sn.x == 2); assert(Sn.y == 2);
	assert(Sr.couleur == rouge); assert(Sn.couleur == noir);
	assert(Sr.getType() == fantassin); assert(Sn.getType() == paladin);
	assert(Sr.siege == NULL && Sn.siege == NULL);
	cout << "\tTest du constructeur parametre : OK" << endl;
	cout << "\tTest de getType : OK" << endl;
	Siege* Si = new Siege;
	Sr.setSiege(Si);
	assert(Sr.getSiege() == Si);
	cout << "\tTest de setSiege et getSiege : OK" << endl;

	// rajouter les tests de deplacement

	cout << "Test de la classe Soldat : OK" << endl << endl;
}