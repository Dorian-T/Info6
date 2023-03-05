#include "Piece.h"
#include "Soldat.h"
#include "Siege.h"
#include "Donjon.h"
#include "Terrain.h"
#include <iostream>
#include <assert.h>
using namespace std;

Terrain::Terrain() {
	// grille = new Piece*[63]; // oblige de faire un tableau 1D avec new
	Soldat* f; Soldat* p; Soldat* a; Siege* s; Donjon* d;

	f = new Soldat(1,2,noir, fantassin); grille[0][0] = f;
	d = new Donjon(1,3,noir); grille[0][1] = d;
	f = new Soldat(1,4,noir, fantassin); grille[0][2] = f;
	a = new Soldat(1,5,noir, archer); grille[0][3] = a;
	f = new Soldat(1,6,noir, fantassin); grille[0][4] = f;
	d = new Donjon(1,7,noir); grille[0][5] = d;
	f = new Soldat(1,8,noir, fantassin); grille[0][6] = f;

	p = new Soldat(2,2,noir, paladin); grille[1][0] = p;
	a = new Soldat(2,3,noir, archer); grille[1][1] = a;
	p = new Soldat(2,4,noir, paladin); grille[1][2] = p;
	f = new Soldat(2,5,noir, fantassin); grille[1][3] = f;
	p = new Soldat(2,6,noir, paladin); grille[1][4] = p;
	a = new Soldat(2,7,noir, archer); grille[1][5] = a;
	p = new Soldat(2,8,noir, paladin); grille[1][6] = p;

	f = new Soldat(3,2,noir, fantassin); grille[2][0] = f;
	p = new Soldat(3,3,noir, paladin); grille[2][1] = p;
	f = new Soldat(3,4,noir, fantassin); grille[2][2] = f;
	s = new Siege(3,5,noir); grille[2][3] = s;
	f = new Soldat(3,6,noir, fantassin); grille[2][4] = f;
	p = new Soldat(3,7,noir, paladin); grille[2][5] = p;
	f = new Soldat(3,8,noir, fantassin); grille[2][6] = f;

	for(int i = 3; i < 6; i++)
		for(int j = 2; j < 9; j++) grille[i][j] = NULL;

	f = new Soldat(6,2,rouge, fantassin); grille[6][0] = f;
	p = new Soldat(6,3,rouge, paladin); grille[6][1] = p;
	f = new Soldat(6,4,rouge, fantassin); grille[6][2] = f;
	s = new Siege(6,5,rouge); grille[6][3] = s;
	f = new Soldat(6,6,rouge, fantassin); grille[6][4] = f;
	p = new Soldat(6,7,rouge, paladin); grille[6][5] = p;
	f = new Soldat(6,8,rouge, fantassin); grille[6][6] = f;

	p = new Soldat(7,2,rouge, paladin); grille[7][0] = p;
	a = new Soldat(7,3,rouge, archer); grille[7][1] = a;
	p = new Soldat(7,4,rouge, paladin); grille[7][2] = p;
	f = new Soldat(7,5,rouge, fantassin); grille[7][3] = f;
	p = new Soldat(7,6,rouge, paladin); grille[7][4] = p;
	a = new Soldat(7,7,rouge, archer); grille[7][5] = a;
	p = new Soldat(7,8,rouge, paladin); grille[7][6] = p;

	f = new Soldat(8,2,rouge, fantassin); grille[8][0] = f;
	d = new Donjon(8,3,rouge); grille[8][1] = d;
	f = new Soldat(8,4,rouge, fantassin); grille[8][2] = f;
	a = new Soldat(8,5,rouge, archer); grille[8][3] = a;
	f = new Soldat(8,6,rouge, fantassin); grille[8][4] = f;
	d = new Donjon(8,7,rouge); grille[8][5] = d;
	f = new Soldat(8,8,rouge, fantassin); grille[8][6] = f;
}

Terrain::~Terrain() {
	for(int i = 0; i < 7; i++)
		for(int j = 0; j < 9; j++) delete grille[i][j];
}

Piece* Terrain::getPiece(unsigned int x, unsigned int y) const {
	assert(x >= 0 && x < 7 && y >= 0 && y < 9);
	return grille[x][y];
}

bool Terrain::verifieCase(unsigned int ax, unsigned int ay, unsigned int nx, unsigned int ny) {
	if(nx < 0 || nx > 7 || ny < 0 || ny > 9) // test si la case est dans le terrain
		return false;
	else {
		if(grille[nx][ny]->getCouleur() == grille[ax][ay]->getCouleur()) { // test si la case est de la même couleur
			if(grille[nx][ny]->getType() == siege) { // test si la case est un siege
				if(grille[nx][ny]->getSoldat() == NULL)
					grille[nx][ny]->setSoldat(grille[ax][ay]);
				else if(grille[nx][ny]->getSoldat()->getCouleur() == grille[ax][ay]->getCouleur())
					return false;
				else {
					delete grille[nx][ny]->getSoldat();
					grille[nx][ny]->setSoldat(grille[ax][ay]);
				}
			}
			else
				return false;
		}
		else {
			if(grille[nx][ny]->getType() == fantassin || grille[nx][ny]->getType() == paladin || grille[nx][ny]->getType() == archer)
				delete grille[nx][ny];
			else if(grille[nx][ny]->getType() == siege) {
				if(grille[nx][ny]->getSoldat() == NULL)
					return false;
				else if(grille[nx][ny]->getSoldat()->getCouleur() == grille[ax][ay]->getCouleur())
					return false;
				else {
					delete grille[nx][ny]->getSoldat();
					grille[nx][ny]->setSoldat(grille[ax][ay]);
				}
			}
			else if(grille[nx][ny]->getType() == donjon) {
				// a faire
				// ne pas oublier que si les 2 donjons sont detruits, c'est la fin de partie
			}
		}
		// faut pas oublier de remmetre le siege si on le quitte (si siege adverse ou si on mange une piece)
		grille[nx][ny] = grille[ax][ay];
		grille[ax][ay] = NULL;
		return true;
	}
}

void Terrain::testRegression() {
	cout << "Test de la classe Terrain" << endl;
}