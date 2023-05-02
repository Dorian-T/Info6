#include "Piece.h"
#include "Terrain.h"

#include <assert.h>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

Terrain::Terrain(const string & fichier) { // majuscule = rouge, minuscule = noir
	ifstream f(fichier);
	if(f.is_open()) {
		char c;
		for(int i = 0; i < 9; i++)
			for(int j = 0; j < 7; j++) {
				f >> c;
				if(c == 'F') grille[i][j] = new Piece(j, i, rouge, fantassin);
				else if(c == 'A') grille[i][j] = new Piece(j, i, rouge, archer);
				else if(c == 'P') grille[i][j] = new Piece(j, i, rouge, paladin);
				else if(c == 'T') grille[i][j] = new Piece(j, i, rouge, tour_de_siege);
				else if(c == 'D') grille[i][j] = new Piece(j, i, rouge, donjon);
				else if(c == 'f') grille[i][j] = new Piece(j, i, noir, fantassin);
				else if(c == 'a') grille[i][j] = new Piece(j, i, noir, archer);
				else if(c == 'p') grille[i][j] = new Piece(j, i, noir, paladin);
				else if(c == 't') grille[i][j] = new Piece(j, i, noir, tour_de_siege);
				else if(c == 'd') grille[i][j] = new Piece(j, i, noir, donjon);
				else grille[i][j] = NULL;
			}
	}
	else cout << "Erreur lors de l'ouverture du fichier " << fichier << endl;
}

Terrain::Terrain(const Terrain & t) {
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 7; j++) {
			if(t.grille[i][j] != NULL)
				grille[i][j] = new Piece(*t.grille[i][j]);
			else
				grille[i][j] = NULL;
		}
}

Terrain::~Terrain() {
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 7; j++) {
			delete grille[i][j];
		}
}

Piece* Terrain::getPiece(unsigned int x, unsigned int y) const {
	assert(x >= 0 && x < 7 && y >= 0 && y < 9);
	return grille[y][x];
}

bool Terrain::verifieCoup(unsigned int ax, unsigned int ay, unsigned int nx, unsigned int ny, bool recule) {
	Piece *temp = NULL;
	if(nx < 0 || nx > 7 || ny < 0 || ny > 9) // si la case n'est pas dans le terrain
		return false;
	else { // si la case est dans le terrain
		if(grille[ny][nx] == NULL) { // si la case est vide
			if(recule)
				return false;
			else {
				grille[ny][nx] = grille[ay][ax];
				if(grille[ny][nx]->getSiege() != NULL && grille[ny][nx]->getSiege()->getCouleur() != grille[ny][nx]->getCouleur()) { // segfault à la descente d'un donjon
					grille[ay][ax] = grille[ny][nx]->getSiege();
					grille[ny][nx]->setSiege(NULL);
				}
				else
					grille[ay][ax] = NULL;
			}
		}
		else { // si la case n'est pas vide
			if(grille[ny][nx]->getCouleur() == grille[ay][ax]->getCouleur()) { // si la case est de la couleur alliee
				if(grille[ny][nx]->getType() == tour_de_siege) { // si la case est un siege
						temp = grille[ay][ax]->getSiege();
						grille[ay][ax]->setSiege(grille[ny][nx]);
						grille[ny][nx] = grille[ay][ax];
						grille[ay][ax] = temp;
						temp = NULL;
				}
				else // si la case n'est pas un siege
					return false;
			}
			else { // si la case est de la couleur adverse
				if(grille[ny][nx]->getType() == fantassin || grille[ny][nx]->getType() == paladin || grille[ny][nx]->getType() == archer) { // si la case est un soldat
					temp = grille[ay][ax]->getSiege();
					grille[ay][ax]->setSiege(grille[ny][nx]->getSiege());
					delete grille[ny][nx];
					grille[ny][nx] = grille[ay][ax];
					grille[ay][ax] = temp;
					temp = NULL;
				}
				else if(grille[ny][nx]->getType() == donjon) { // si la case est un donjon
						if(grille[ny][nx]->getMenace(*this) >= 2) {
							delete grille[ny][nx];
							grille[ny][nx] = grille[ay][ax];
							grille[ay][ax] = grille[ny][nx]->getSiege();
							grille[ny][nx]->setSiege(NULL);
						}
						else
							return false;
				}
				else
					return false;
			}
		}
		return true;
	}
}

ostream &operator<<(ostream & os, const Terrain & t) {
	Piece* P;
	for(int i = 0; i < 9; i++) {
		for(int j = 0; j < 7; j++) {
			P = t.getPiece(j, i);
			if (P == NULL)
				os << " . ";
			else {
				if(P->getType() != donjon && P->getType() != tour_de_siege && P->getSiege() != NULL) os << "|";
				else os << " ";
				if(P->getCouleur() == rouge)
					switch (P->getType()) {
						case donjon:
							os << "D";
							break;
						case tour_de_siege:
							os << "T";
							break;
						case fantassin:
							os << "F";
							break;
						case paladin:
							os << "P";
							break;
						case archer:
							os << "A";
							break;
					}
				else
					switch (P->getType()) {
						case donjon:
							os << "d";
							break;
						case tour_de_siege:
							os << "t";
							break;
						case fantassin:
							os << "f";
							break;
						case paladin:
							os << "p";
							break;
						case archer:
							os << "a";
							break;
					}
				if(P->getType() != donjon && P->getType() != tour_de_siege && P->getSiege() != NULL) os << "|";
				else os << " ";
			}
		}
		os << endl;
	}
	return os;
}

void Terrain::testRegression() {
	cout << endl << "Test de la classe Terrain" << endl;

	assert(getPiece(0, 0)->getType() == fantassin);
	assert(getPiece(3, 4) == NULL);
	assert(getPiece(6, 8)->getType() == fantassin);
	cout << "\tTest constructeur par defaut : OK" << endl;

	Terrain test("data/testTerrain.txt");
	assert(test.getPiece(1, 1)->getType() == fantassin);
	cout << "\tTest constructeur parametre : OK" << endl;
	cout << "\tTest getPiece : OK" << endl;

	Terrain T("data/classique.txt");
	Terrain copie(T);
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 7; j++) {
			if(T.getPiece(j, i) == NULL)
				assert(copie.getPiece(j, i) == NULL);
			else {
				assert(copie.getPiece(j, i)->getType() == T.getPiece(j, i)->getType());
				assert(copie.getPiece(j, i)->getCouleur() == T.getPiece(j, i)->getCouleur());
				if(T.getPiece(j, i)->getType() != donjon && T.getPiece(j, i)->getType() != tour_de_siege && T.getPiece(j, i)->getSiege() != NULL) {
					assert(copie.getPiece(j, i)->getSiege()->getType() == T.getPiece(j, i)->getSiege()->getType());
					assert(copie.getPiece(j, i)->getSiege()->getCouleur() == T.getPiece(j, i)->getSiege()->getCouleur());
				}
			}
		}
	cout << "\tTest constructeur par copie : OK" << endl;

	assert(test.verifieCoup(1, 1, 1, 0, false));
	cout << "\tTest verifieCoup : OK" << endl;

	cout << "Test Terrain : OK" << endl << endl;
}
