#include "../core/Piece.h"
#include "../core/Terrain.h"
#include "Robot.h"

#include <assert.h>
#include <iostream>
#include <math.h>
#include <string>
#include <vector>

using namespace std;


Robot::Robot(Couleur c) {
	couleur = c;
	copieTerrain = NULL;
}

Robot::~Robot() {
	if(copieTerrain != NULL)
		delete copieTerrain;
}



// déplacements :

void Robot::joue(Terrain & t) {
	trouverDonjon(t);
	Piece * P;
	for(unsigned int y = 9; y > 0; y--)
		for(unsigned int x = 0; x < 7; x++) {
			P = t.getPiece(x, y);
			if(P != NULL && P->getCouleur() == couleur && P->getType() != donjon && P->getType() != tour_de_siege) {
				copieTerrain = new Terrain(t);
				if(P->getType() == fantassin) deplacerFantassin(*copieTerrain, x, y);
				else if(P->getType() == paladin) deplacerPaladin(*copieTerrain, x, y);
				else deplacerArcher(*copieTerrain, x, y);
				delete copieTerrain;
			}
		}
	t.verifieCoup(meilleurCoupDepart%10, meilleurCoupDepart/10, meilleurCoupArrivee%10, meilleurCoupArrivee/10, false);
}

void Robot::deplacerFantassin(Terrain & t, unsigned int x, unsigned int y) {
	assert(t.getPiece(x, y) != NULL && t.getPiece(x, y)->getType() == fantassin);
	if(couleur == rouge) {
		if(t.verifieCoup(x, y, x, y-1, false)) {
			evaluer(t);
			delete copieTerrain;
			copieTerrain = new Terrain(t);
		}
		if(t.verifieCoup(x, y, x, y+1, true)) {
			evaluer(t);
			delete copieTerrain;
			copieTerrain = new Terrain(t);
		}
	}
	else {
		if(t.verifieCoup(x, y, x, y+1, false)) {
			evaluer(t);
			delete copieTerrain;
			copieTerrain = new Terrain(t);
		}
		if(t.verifieCoup(x, y, x, y-1, true)) {
			evaluer(t);
			delete copieTerrain;
			copieTerrain = new Terrain(t);
		}
	}
	if(t.verifieCoup(x, y, x+1, y, false)) {
		evaluer(t);
		delete copieTerrain;
		copieTerrain = new Terrain(t);
	}
	if(t.verifieCoup(x, y, x-1, y, false)) {
		evaluer(t);
		delete copieTerrain;
		copieTerrain = new Terrain(t);
	}
}

void Robot::deplacerPaladin(Terrain & t, unsigned int x, unsigned int y) {
	assert(t.getPiece(x, y) != NULL && t.getPiece(x, y)->getType() == paladin);
	if(couleur == rouge) {
		if(t.verifieCoup(x, y, x+1, y-1, false)) {
			evaluer(t);
			delete copieTerrain;
			copieTerrain = new Terrain(t);
		}
		if(t.verifieCoup(x, y, x-1, y-1, false)) {
			evaluer(t);
			delete copieTerrain;
			copieTerrain = new Terrain(t);
		}
		if(t.verifieCoup(x, y, x+1, y+1, true)) {
			evaluer(t);
			delete copieTerrain;
			copieTerrain = new Terrain(t);
		}
		if(t.verifieCoup(x, y, x-1, y+1, true)) {
			evaluer(t);
			delete copieTerrain;
			copieTerrain = new Terrain(t);
		}
	}
	else {
		if(t.verifieCoup(x, y, x+1, y+1, false)) {
			evaluer(t);
			delete copieTerrain;
			copieTerrain = new Terrain(t);
		}
		if(t.verifieCoup(x, y, x-1, y+1, false)) {
			evaluer(t);
			delete copieTerrain;
			copieTerrain = new Terrain(t);
		}
		if(t.verifieCoup(x, y, x+1, y-1, true)) {
			evaluer(t);
			delete copieTerrain;
			copieTerrain = new Terrain(t);
		}
		if(t.verifieCoup(x, y, x-1, y-1, true)) {
			evaluer(t);
			delete copieTerrain;
			copieTerrain = new Terrain(t);
		}
	}
}

void Robot::deplacerArcher(Terrain & t, unsigned int x, unsigned int y) {
	assert(t.getPiece(x, y) != NULL && t.getPiece(x, y)->getType() == archer);
	if(t.verifieCoup(x, y, x, y-1, false)) {
		evaluer(t);
		delete copieTerrain;
		copieTerrain = new Terrain(t);
	}
	if(t.verifieCoup(x, y, x+1, y-1, false)) {
		evaluer(t);
		delete copieTerrain;
		copieTerrain = new Terrain(t);
	}
	if(t.verifieCoup(x, y, x+1, y, false)) {
		evaluer(t);
		delete copieTerrain;
		copieTerrain = new Terrain(t);
	}
	if(t.verifieCoup(x, y, x+1, y+1, false)) {
		evaluer(t);
		delete copieTerrain;
		copieTerrain = new Terrain(t);
	}
	if(t.verifieCoup(x, y, x, y+1, false)) {
		evaluer(t);
		delete copieTerrain;
		copieTerrain = new Terrain(t);
	}
	if(t.verifieCoup(x, y, x-1, y+1, false)) {
		evaluer(t);
		delete copieTerrain;
		copieTerrain = new Terrain(t);
	}
	if(t.verifieCoup(x, y, x-1, y, false)) {
		evaluer(t);
		delete copieTerrain;
		copieTerrain = new Terrain(t);
	}
	if(t.verifieCoup(x, y, x-1, y-1, false)) {
		evaluer(t);
		delete copieTerrain;
		copieTerrain = new Terrain(t);
	}
}


// évaluation :

void Robot::evaluer(const Terrain & t) {
	// TODO
}

void Robot::trouverDonjon(const Terrain & t) {
	donjon1 = NULL;
	donjon2 = NULL;
	for(unsigned int y = 0; y < 9; y++)
		for(unsigned int x = 0; x < 7; x++)
			if(t.getPiece(x, y) != NULL && t.getPiece(x, y)->getType() == donjon) {
				if(donjon1 == NULL) donjon1 = t.getPiece(x, y);
				else donjon2 = t.getPiece(x, y);
			}
}

int Robot::evaluerPosition(unsigned int x, unsigned int y, const Terrain & t) {
	return (11 - distance(x, y, donjon1->getX(), donjon1->getY())) + (11 - distance(x, y, donjon2->getX(), donjon2->getY()));
}

int Robot::distance(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2) {
	return (int) sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}


void Robot::testRegression() {
	cout << "Test de Robot" << endl;

	assert(couleur == rouge); assert(copieTerrain == NULL);
	cout << "\tTest constructeur : OK" << endl;

	assert(distance(4, 6, 3, 4) == (int) sqrt(5));
	cout << "\tTest distance : OK" << endl;
}