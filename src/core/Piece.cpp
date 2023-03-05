#include "Piece.h"
#include "Soldat.h"
#include "Siege.h"
#include <assert.h>
#include <iostream>
using namespace std;

Piece::Piece() {}

Piece::Piece(unsigned int Px, unsigned int Py) {
	x = Px;
	y = Py;
}

Piece::Piece(unsigned int Px, unsigned int Py, Couleur Pcouleur): Piece(Px, Py) {
	couleur = Pcouleur;
}

Couleur Piece::getCouleur() const {
	return couleur;
}

Type Piece::getType() const {
	return type;
}

Piece* Piece::getSiege() const {return NULL;}

Piece* Piece::getSoldat() const {return NULL;}

void Piece::setSoldat(Piece* Ssoldat) {}

void Piece::testRegression() {
	cout << "Test Piece" << endl;
	cout << "\tTest constructeur par defaut : OK" << endl;
	Piece P(1, 2);
	assert(P.x == 1); assert(P.y == 2);
	cout << "\tTest constructeur parametre 1 : OK" << endl;
	Piece P2(2, 3, rouge);
	assert(P2.x == 2); assert(P2.y == 3); assert(P2.getCouleur() == rouge);
	cout << "\tTest constructeur parametre 2 : OK" << endl;
	cout << "\tTest getCouleur : OK" << endl;
	cout << "Test Piece : OK" << endl << endl;
}