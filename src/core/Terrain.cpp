#include "Piece.h"
#include "Soldat.h"
#include "Siege.h"
#include "Donjon.h"
#include "Terrain.h"
#include <assert.h>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

Terrain::Terrain() {
	grille[0][0] = new Soldat(0, 0, noir, fantassin);
	grille[0][1] = new Donjon(1, 0, noir);
	grille[0][2] = new Soldat(2, 0, noir, fantassin);
	grille[0][3] = new Soldat(3, 0, noir, archer);
	grille[0][4] = new Soldat(4, 0, noir, fantassin);
	grille[0][5] = new Donjon(5, 0, noir);
	grille[0][6] = new Soldat(6, 0, noir, fantassin);

	grille[1][0] = new Soldat(0, 1, noir, paladin);
	grille[1][1] = new Soldat(1, 1, noir, archer);
	grille[1][2] = new Soldat(2, 1, noir, paladin);
	grille[1][3] = new Soldat(3, 1, noir, fantassin);
	grille[1][4] = new Soldat(4, 1, noir, paladin);
	grille[1][5] = new Soldat(5, 1, noir, archer);
	grille[1][6] = new Soldat(6, 1, noir, paladin);

	grille[2][0] = new Soldat(0, 2, noir, fantassin);
	grille[2][1] = new Soldat(1, 2, noir, paladin);
	grille[2][2] = new Soldat(2, 2, noir, fantassin);
	grille[2][3] = new Siege(3, 2, noir);
	grille[2][4] = new Soldat(4, 2, noir, fantassin);
	grille[2][5] = new Soldat(5, 2, noir, paladin);
	grille[2][6] = new Soldat(6, 2, noir, fantassin);

	for(int i = 3; i < 6; i++)
		for(int j = 0; j < 9; j++)
			grille[i][j] = NULL;

	grille[6][0] = new Soldat(0, 6, rouge, fantassin);
	grille[6][1] = new Soldat(1, 6, rouge, paladin);
	grille[6][2] = new Soldat(2, 6, rouge, fantassin);
	grille[6][3] = new Siege(3, 6, rouge);
	grille[6][4] = new Soldat(4, 6, rouge, fantassin);
	grille[6][5] = new Soldat(5, 6, rouge, paladin);
	grille[6][6] = new Soldat(6, 6, rouge, fantassin);

	grille[7][0] = new Soldat(0, 7, rouge, paladin);
	grille[7][1] = new Soldat(1, 7, rouge, archer);
	grille[7][2] = new Soldat(2, 7, rouge, paladin);
	grille[7][3] = new Soldat(3, 7, rouge, fantassin);
	grille[7][4] = new Soldat(4, 7, rouge, paladin);
	grille[7][5] = new Soldat(5, 7, rouge, archer);
	grille[7][6] = new Soldat(6, 7, rouge, paladin);

	grille[8][0] = new Soldat(0, 8, rouge, fantassin);
	grille[8][1] = new Donjon(1, 8, rouge);
	grille[8][2] = new Soldat(2, 8, rouge, fantassin);
	grille[8][3] = new Soldat(3, 8, rouge, archer);
	grille[8][4] = new Soldat(4, 8, rouge, fantassin);
	grille[8][5] = new Donjon(5, 8, rouge);
	grille[8][6] = new Soldat(6, 8, rouge, fantassin);
}

Terrain::Terrain(const string & fichier) { // majuscule = rouge, minuscule = noir
	ifstream f(fichier);
	if(f.is_open()) {
		char c;
		for(int i = 0; i < 9; i++)
			for(int j = 0; j < 7; j++) {
				f >> c;
				if(c == 'F') grille[i][j] = new Soldat(j, i, rouge, fantassin);
				else if(c == 'A') grille[i][j] = new Soldat(j, i, rouge, archer);
				else if(c == 'P') grille[i][j] = new Soldat(j, i, rouge, paladin);
				else if(c == 'S') grille[i][j] = new Siege(j, i, rouge);
				else if(c == 'D') grille[i][j] = new Donjon(j, i, rouge);
				else if(c == 'f') grille[i][j] = new Soldat(j, i, noir, fantassin);
				else if(c == 'a') grille[i][j] = new Soldat(j, i, noir, archer);
				else if(c == 'p') grille[i][j] = new Soldat(j, i, noir, paladin);
				else if(c == 's') grille[i][j] = new Siege(j, i, noir);
				else if(c == 'd') grille[i][j] = new Donjon(j, i, noir);
				else grille[i][j] = NULL;
			}
	}
	else cout << "Erreur lors de l'ouverture du fichier " << fichier << endl;
}

Terrain::~Terrain() {
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 7; j++) delete grille[i][j];
}

Piece* Terrain::getPiece(unsigned int x, unsigned int y) const {
	assert(x >= 0 && x < 7 && y >= 0 && y < 9);
	return grille[y][x];
}

bool Terrain::verifieCase(unsigned int ax, unsigned int ay, unsigned int nx, unsigned int ny, bool recule) {
	bool quitteSiege = false;
	if(nx < 0 || nx > 7 || ny < 0 || ny > 9) // si la case n'est pas dans le terrain
		return false;
	else { // si la case est dans le terrain
		if(grille[nx][nx] == NULL) { // si la case est vide
			if(recule)
				return false;
		}
		else { // si la case n'est pas vide
			cout << "case non vide"; // pourquoi ca s'affiche pas ???
			if(grille[ny][nx]->getCouleur() == grille[ax][ay]->getCouleur()) { // si la case est de la couleur alliee
				if(grille[ny][nx]->getType() == tour_de_siege) { // si la case est un siege
					if(grille[ny][nx]->getSoldat() == NULL) {
						grille[ny][nx]->setSoldat(grille[ax][ay]);
						quitteSiege = true;
					}
					else if(grille[ny][nx]->getSoldat()->getCouleur() == grille[ax][ay]->getCouleur())
						return false;
					else {
						delete grille[ny][nx]->getSoldat();
						grille[ny][nx]->setSoldat(grille[ax][ay]);
						quitteSiege = true;
					}
				}
				else // si la case n'est pas un siege
					return false;
			}
			else { // si la case est de la couleur adverse
				if(grille[ny][nx]->getType() == fantassin || grille[ny][nx]->getType() == paladin || grille[ny][nx]->getType() == archer) { // si la case est un soldat
					delete grille[ny][nx];
					quitteSiege = true;
				}
				else if(grille[ny][nx]->getType() == tour_de_siege) { // si la case est un siege
					if(grille[ny][nx]->getSoldat() == NULL)
						return false;
					else if(grille[ny][nx]->getSoldat()->getCouleur() == grille[ax][ay]->getCouleur())
						return false;
					else {
						delete grille[ny][nx]->getSoldat();
						grille[ny][nx]->setSoldat(grille[ax][ay]);
						quitteSiege = true;
					}
				}
				else if(grille[ny][nx]->getType() == donjon) { // si la case est un donjon
					if(grille[ny][nx]->getCouleur() == grille[ax][ay]->getCouleur())
						return false;
					else {
						if(grille[ny][nx]->regardeMenace() > 1) {
							delete grille[ny][nx];
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
			grille[ny][nx] = grille[ax][ay];
			grille[ax][ay] = grille[ny][nx]->getSiege();
			grille[ny][nx]->setSiege(NULL);
			grille[ax][ay]->setSoldat(NULL);
		}
		else {
			grille[ny][nx] = grille[ax][ay];
			grille[ax][ay] = NULL;
		}
		return true;
	}
}

void Terrain::testRegression() {
	cout << "Test de la classe Terrain" << endl;

	assert(getPiece(0, 0)->getType() == fantassin);
	assert(getPiece(3, 4) == NULL);
	assert(getPiece(6, 8)->getType() == fantassin);
	cout << "\tTest constructeur par defaut : OK" << endl;

	Terrain test("data/testTerrain.txt");
	assert(test.getPiece(1, 1)->getType() == fantassin);
	cout << "\tTest constructeur parametre : OK" << endl;

	cout << "\tTest getPiece : OK" << endl;

	cout << "affiche toi STP !"; // ca s'affiche pas !!
	if(test.getPiece(1, 0) == NULL) cout << "oui oui c'est vide";
	else cout << "probleme";
	assert(test.verifieCase(1, 1, 1, 0, false));
	cout << "\tTest verifieCase() : OK" << endl;

	cout << "Test Terrain : OK" << endl << endl;
}
