#include "Piece.h"
#include "Soldat.h"
#include "Siege.h"
#include "Donjon.h"
#include "Terrain.h"

Terrain::Terrain() {
	grille = new Piece[63]; // oblige de faire un tableau 1D avec new
	Soldat* S = new Soldat(1,2,noir, fantassin);
	// grille[0] = S; // probleme ! je veux faire un tableau de pointeurs pas un pointeur sur un tableau !
}

Terrain::~Terrain() {
	delete[] grille;
}

bool Terrain::verifieCase(unsigned int x, unsigned int y) {
	if(x < 0 || x > 7 || y < 0 || y > 9) return false;
	// autres tests
	return true;
}