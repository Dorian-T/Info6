#include "Piece.h"
#include "Soldat.h"
#include "Siege.h"
#include "Terrain.h"
#include <iostream>
#include <assert.h>
#include <string>
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

Piece* Soldat::getSiege() const {
	return siege;
}

void Soldat::setSiege(Piece * Ssiege) {
	assert(Ssiege->getType() == tour_de_siege);
	siege = Ssiege;
}

bool Soldat::deplacer(Terrain & t, const string & s) {
	if(s == "h") {cout << "je suis la" << endl; return deplacerH(t);  }
	else if(s == "hd") return deplacerHD(t);
	else if(s == "d") return deplacerD(t);
	else if(s == "bd") return deplacerBD(t);
	else if(s == "b") return deplacerB(t);
	else if(s == "bg") return deplacerBG(t);
	else if(s == "g") return deplacerG(t);
	else if(s == "hg") return deplacerHG(t);
	else return false;
}

bool Soldat::deplacerH(Terrain & t) { cout << "0";
	if(type == fantassin || type == archer) { cout << "1";
		if(couleur == rouge) { cout << "2";
			if(t.verifieCase(x, y, x, y-1, false)) y--;
			else return false;}
		else
			if(t.verifieCase(x, y, x, y+1, false)) y++;
			else return false;}
	else { cout << "3"; return false;}
	return true;
}

bool Soldat::deplacerHD(Terrain & t) {
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

bool Soldat::deplacerD(Terrain & t) {
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

bool Soldat::deplacerBD(Terrain & t) {
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

bool Soldat::deplacerB(Terrain & t) {
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

bool Soldat::deplacerBG(Terrain & t) {
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

bool Soldat::deplacerG(Terrain & t) {
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

bool Soldat::deplacerHG(Terrain & t) {
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

	Terrain t("data/testTerrain.txt");    
    assert(Sr.deplacerH(t));

	cout << "Test de la classe Soldat : OK" << endl << endl;
}
