#include "Terrain.h"

Terrain::Terrain() {
	grille = new Piece[63]; // oblige de faire un tableau 1D avec new
	// probleme de constructeur de Piece
}

Terrain::~Terrain() {
	delete[] grille;
}

bool Terrain::verifieCase(unsigned int x, unsigned int y) {
	if(x < 0 || x > 7 || y < 0 || y > 9) return false;
	// autres tests
	return true;
}