#include "Donjon.h"
#include "Piece.h"
#include "Terrain.h"
#include <iostream>
#include <assert.h>
using namespace std;

Donjon::Donjon() {}

Donjon::Donjon(unsigned int Px, unsigned int Py, Couleur Pcouleur): Piece(Px, Py, Pcouleur) {
	type = donjon;
	menace = 0;
}

unsigned int Donjon::getMenace() const {
	return menace;
}

void Donjon::rMenace(Terrain & t, Piece* p, Type ty) {
	if(p->getCouleur() != couleur) {
		if(p->getType() == ty || p->getType() == archer) {
			if(p->getSiege() == NULL) menace++;
			else menace += 2;
		}
	}
}

void Donjon::regardeMenace(Terrain & t) {
	if (couleur == rouge) {
		rMenace(t, t.getPiece(x-1, y), fantassin);
		rMenace(t, t.getPiece(x-1, y-1), paladin);
		rMenace(t, t.getPiece(x, y-1), fantassin);
		rMenace(t, t.getPiece(x+1, y-1), paladin);
		rMenace(t, t.getPiece(x+1, y), fantassin);
	}
	else {
		rMenace(t, t.getPiece(x-1, y), fantassin);
		rMenace(t, t.getPiece(x-1, y+1), paladin);
		rMenace(t, t.getPiece(x, y+1), fantassin);
		rMenace(t, t.getPiece(x+1, y+1), paladin);
		rMenace(t, t.getPiece(x+1, y), fantassin);
	}
}

void Donjon::testRegression() {
	cout << "Test Donjon" << endl;
	cout << "\tTest constructeur : OK" << endl;
	Donjon D(1,2,rouge);
	assert(D.x == 1 && D.y == 2 && D.couleur == rouge);
	assert(D.getMenace() == 0);
	cout << "\tTest constructeur parametre : OK" << endl;
	cout << "\tTest getMenace : OK" << endl;
	// ajouter test regardeMenace
	cout << "Test Donjon : OK" << endl << endl;
}