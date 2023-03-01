#include "Piece.h"
#include <assert.h>
#include <iostream>
using namespace std;

Piece::Piece() {}

Piece::Piece(unsigned int Px, unsigned int Py) {
	x = Px;
	y = Py;
}

Piece::Piece(unsigned int Px, unsigned int Py, Couleur Pcouleur, Type Ptype) {
	x = Px;
	y = Py;
	couleur = Pcouleur;
	type = Ptype;
}

Couleur Piece::getCouleur() const {
	return couleur;
}

Type Piece::getType() const {
	return type;
}

void Piece::testRegression() {
	cout << "Test Piece" << endl;
	cout << "\tTest constructeur par defaut : OK" << endl;
	Piece P(1,2);
	assert(P.x == 1); assert(P.y == 2);
	cout << "\tTest constructeur par parametre 1 : OK" << endl;
	Piece P2(1,2,rouge,fantassin);
	assert(P.getCouleur() == rouge);
	cout << "\tTest getCouleur : OK" << endl;
	assert(P.getType() == fantassin);
	cout << "\tTest getType : OK" << endl;
	cout << "\tTest constructeur par parametre 2 : OK" << endl;
	cout << "Test Piece : OK" << endl << endl;
}