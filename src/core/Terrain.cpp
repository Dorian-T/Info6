#include "Piece.h"
#include "Soldat.h"
#include "Siege.h"
#include "Donjon.h"
#include "Terrain.h"
#include <iostream>
#include <assert.h>
using namespace std;

Terrain::Terrain() {
	grille[0][0] = new Soldat(0, 0, noir, fantassin); // Est-ce qu'on aurait pas inversé lignes et colonnes ?
	grille[1][0] = new Donjon(1, 0, noir);
	grille[2][0] = new Soldat(2, 0, noir, fantassin);
	grille[3][0] = new Soldat(3, 0, noir, archer);
	grille[4][0] = new Soldat(4, 0, noir, fantassin);
	grille[5][0] = new Donjon(5, 0, noir);
	grille[6][0] = new Soldat(6, 0, noir, fantassin);

	grille[0][1] = new Soldat(0, 1, noir, paladin);
	grille[1][1] = new Soldat(1, 1, noir, archer);
	grille[2][1] = new Soldat(2, 1, noir, paladin);
	grille[3][1] = new Soldat(3, 1, noir, fantassin);
	grille[4][1] = new Soldat(4, 1, noir, paladin);
	grille[5][1] = new Soldat(5, 1, noir, archer);
	grille[6][1] = new Soldat(6, 1, noir, paladin);

	grille[0][2] = new Soldat(0, 2, noir, fantassin);
	grille[1][2] = new Soldat(1, 2, noir, paladin);
	grille[2][2] = new Soldat(2, 2, noir, fantassin);
	grille[3][2] = new Siege(3, 2, noir);
	grille[4][2] = new Soldat(4, 2, noir, fantassin);
	grille[5][2] = new Soldat(5, 2, noir, paladin);
	grille[6][2] = new Soldat(6, 2, noir, fantassin);

	for(int i = 0; i < 7; i++)
		for(int j = 3; j < 6; j++)
			grille[i][j] = NULL;

	grille[0][6] = new Soldat(0, 6, rouge, fantassin);
	grille[1][6] = new Soldat(1, 6, rouge, paladin);
	grille[2][6] = new Soldat(2, 6, rouge, fantassin);
	grille[3][6] = new Siege(3, 6, rouge);
	grille[4][6] = new Soldat(4, 6, rouge, fantassin);
	grille[5][6] = new Soldat(5, 6, rouge, paladin);
	grille[6][6] = new Soldat(6, 6, rouge, fantassin);

	grille[0][7] = new Soldat(0, 7, rouge, paladin);
	grille[1][7] = new Soldat(1, 7, rouge, archer);
	grille[2][7] = new Soldat(2, 7, rouge, paladin);
	grille[3][7] = new Soldat(3, 7, rouge, fantassin);
	grille[4][7] = new Soldat(4, 7, rouge, paladin);
	grille[5][7] = new Soldat(5, 7, rouge, archer);
	grille[6][7] = new Soldat(6, 7, rouge, paladin);

	grille[0][8] = new Soldat(0, 8, rouge, fantassin);
	grille[1][8] = new Donjon(1, 8, rouge);
	grille[2][8] = new Soldat(2, 8, rouge, fantassin);
	grille[3][8] = new Soldat(3, 8, rouge, archer);
	grille[4][8] = new Soldat(4, 8, rouge, fantassin);
	grille[5][8] = new Donjon(5, 8, rouge);
	grille[6][8] = new Soldat(6, 8, rouge, fantassin);
}


Terrain::~Terrain() {
	for(int i = 0; i < 7; i++)
		for(int j = 0; j < 9; j++) delete grille[i][j];
}

Piece* Terrain::getPiece(unsigned int x, unsigned int y) const {
	assert(x >= 0 && x < 7 && y >= 0 && y < 9);
	return grille[x][y];
}

bool Terrain::verifieCase(unsigned int ax, unsigned int ay, unsigned int nx, unsigned int ny, bool recule) {
	bool quitteSiege = false;
	if(nx < 0 || nx > 7 || ny < 0 || ny > 9) // si la case n'est pas dans le terrain
		return false;
	else { // si la case est dans le terrain
		if(grille[nx][ny] == NULL) { // si la case est vide
			if(recule)
				return false;
		}
		else { // si la case n'est pas vide
			if(grille[nx][ny]->getCouleur() == grille[ax][ay]->getCouleur()) { // si la case est de la couleur alliee
				if(grille[nx][ny]->getType() == tour_de_siege) { // si la case est un siege
					if(grille[nx][ny]->getSoldat() == NULL) {
						grille[nx][ny]->setSoldat(grille[ax][ay]);
						quitteSiege = true;
					}
					else if(grille[nx][ny]->getSoldat()->getCouleur() == grille[ax][ay]->getCouleur())
						return false;
					else {
						delete grille[nx][ny]->getSoldat();
						grille[nx][ny]->setSoldat(grille[ax][ay]);
						quitteSiege = true;
					}
				}
				else // si la case n'est pas un siege
					return false;
			}
			else { // si la case est de la couleur adverse
				if(grille[nx][ny]->getType() == fantassin || grille[nx][ny]->getType() == paladin || grille[nx][ny]->getType() == archer) { // si la case est un soldat
					delete grille[nx][ny];
					quitteSiege = true;
				}
				else if(grille[nx][ny]->getType() == tour_de_siege) { // si la case est un siege
					if(grille[nx][ny]->getSoldat() == NULL)
						return false;
					else if(grille[nx][ny]->getSoldat()->getCouleur() == grille[ax][ay]->getCouleur())
						return false;
					else {
						delete grille[nx][ny]->getSoldat();
						grille[nx][ny]->setSoldat(grille[ax][ay]);
						quitteSiege = true;
					}
				}
				else if(grille[nx][ny]->getType() == donjon) { // si la case est un donjon
					if(grille[nx][ny]->getCouleur() == grille[ax][ay]->getCouleur())
						return false;
					else {
						if(grille[nx][ny]->regardeMenace() > 1) {
							delete grille[nx][ny];
							quitteSiege = true;
						}
						else
							return false;
					// ne pas oublier que si les 2 donjons sont detruits, c'est la fin de partie
					}
				}
			}
		}
		if(quitteSiege && grille[ax][ay]->getSiege() != NULL) {
			grille[nx][ny] = grille[ax][ay];
			grille[ax][ay] = grille[nx][ny]->getSiege();
			grille[nx][ny]->setSiege(NULL);
			grille[ax][ay]->setSoldat(NULL);
		}
		else {
			grille[nx][ny] = grille[ax][ay];
			grille[ax][ay] = NULL;
		}
		return true;
	}
}

void Terrain::testRegression() {
	cout << "Test de la classe Terrain" << endl;
}
