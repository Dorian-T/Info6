#include "Piece.h"
#include "Soldat.h"
#include "Siege.h"
#include "Donjon.h"
#include "Terrain.h"
#include <iostream>
#include <assert.h>
using namespace std;

Terrain::Terrain() {
	grille = new Piece*[63]; // oblige de faire un tableau 1D avec new
	Soldat* f; Soldat* p; Soldat* a; Siege* s; Donjon* d;

	f = new Soldat(1,2,noir, fantassin); grille[0] = f;
	d = new Donjon(1,3,noir); grille[1] = d;
	f = new Soldat(1,4,noir, fantassin); grille[2] = f;
	a = new Soldat(1,5,noir, archer); grille[3] = a;
	f = new Soldat(1,6,noir, fantassin); grille[4] = f;
	d = new Donjon(1,7,noir); grille[5] = d;
	f = new Soldat(1,8,noir, fantassin); grille[6] = f;

	p = new Soldat(2,2,noir, paladin); grille[7] = p;
	a = new Soldat(2,3,noir, archer); grille[8] = a;
	p = new Soldat(2,4,noir, paladin); grille[9] = p;
	f = new Soldat(2,5,noir, fantassin); grille[10] = f;
	p = new Soldat(2,6,noir, paladin); grille[11] = p;
	a = new Soldat(2,7,noir, archer); grille[12] = a;
	p = new Soldat(2,8,noir, paladin); grille[13] = p;

	f = new Soldat(3,2,noir, fantassin); grille[14] = f;
	p = new Soldat(3,3,noir, paladin); grille[15] = p;
	f = new Soldat(3,4,noir, fantassin); grille[16] = f;
	s = new Siege(3,5,noir); grille[17] = s;
	f = new Soldat(3,6,noir, fantassin); grille[18] = f;
	p = new Soldat(3,7,noir, paladin); grille[19] = p;
	f = new Soldat(3,8,noir, fantassin); grille[20] = f;

	for(int i = 21; i < 42; i++) grille[i] = NULL;

	f = new Soldat(6,2,rouge, fantassin); grille[42] = f;
	p = new Soldat(6,3,rouge, paladin); grille[43] = p;
	f = new Soldat(6,4,rouge, fantassin); grille[44] = f;
	s = new Siege(6,5,rouge); grille[45] = s;
	f = new Soldat(6,6,rouge, fantassin); grille[46] = f;
	p = new Soldat(6,7,rouge, paladin); grille[47] = p;
	f = new Soldat(6,8,rouge, fantassin); grille[48] = f;

	p = new Soldat(7,2,rouge, paladin); grille[49] = p;
	a = new Soldat(7,3,rouge, archer); grille[50] = a;
	p = new Soldat(7,4,rouge, paladin); grille[51] = p;
	f = new Soldat(7,5,rouge, fantassin); grille[52] = f;
	p = new Soldat(7,6,rouge, paladin); grille[53] = p;
	a = new Soldat(7,7,rouge, archer); grille[54] = a;
	p = new Soldat(7,8,rouge, paladin); grille[55] = p;

	f = new Soldat(8,2,rouge, fantassin); grille[56] = f;
	d = new Donjon(8,3,rouge); grille[57] = d;
	f = new Soldat(8,4,rouge, fantassin); grille[58] = f;
	a = new Soldat(8,5,rouge, archer); grille[59] = a;
	f = new Soldat(8,6,rouge, fantassin); grille[60] = f;
	d = new Donjon(8,7,rouge); grille[61] = d;
	f = new Soldat(8,8,rouge, fantassin); grille[62] = f;
}

Terrain::~Terrain() {
	for(int i = 0; i < 63; i++) delete grille[i];
	delete[] grille;
	grille = NULL;
}

bool Terrain::verifieCase(unsigned int x, unsigned int y) {
	if(x < 0 || x > 7 || y < 0 || y > 9) return false;
	// autres tests
	return true;
}

void Terrain::testRegression() {
	cout << "Test de la classe Terrain" << endl;
}