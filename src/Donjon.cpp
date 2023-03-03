#include "Donjon.h"
#include "Piece.h"
#include "Terrain.h"
#include <iostream>
#include <assert.h>
using namespace std;

Donjon::Donjon(unsigned int Px, unsigned int Py, Couleur Pcouleur): Piece(Px, Py, Pcouleur) {
	menace = 0;
}

unsigned int Donjon::getMenace() const {
	return menace;
}

unsigned int Donjon::regardeMenace() {
	if (couleur == rouge) { // ne regarde pas les mêmes cases en fonctions de la couleur
		// Regarder une case autours du donjon puis récupérer le type, sa couleur et si il est sur un siège pour ajouter sur menace.
	}
}

void Donjon::testRegression() {
	cout << "Test Donjon" << endl;
	Donjon D(1,2,rouge);
	assert(D.x == 1); assert(D.y == 2);
	assert(D.couleur == rouge);
	assert(D.getMenace() == 0);
	cout << "\tTest getMenace : OK" << endl;
	cout << "\tTest constructeur : OK" << endl;
	// TODO : test regardeMenace
	cout << "Test Donjon : OK" << endl << endl;
}