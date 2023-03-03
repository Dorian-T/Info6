#include "Donjon.h"
#include "Piece.h"
#include "Terrain.h"
#include <iostream>
#include <assert.h>
using namespace std;

Donjon::Donjon() {}

Donjon::Donjon(unsigned int Px, unsigned int Py, Couleur Pcouleur): Piece(Px, Py, Pcouleur) {
	menace = 0;
}

unsigned int Donjon::getMenace() const {
	return menace;
}
/*
unsigned int Donjon::regardeMenace() {
	if (couleur == rouge) { // ne regarde pas les mêmes cases en fonctions de la couleur
		// Regarder une case autours du donjon puis récupérer le type, sa couleur et si il est sur un siège pour ajouter sur menace.
	}
}
*/
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