#include "Robot.h"

#include <assert.h>
#include <iostream>
#include <math.h>

using namespace std;


// constructeur et destructeur :

Robot::Robot(Couleur c) {
	couleur = c;
	copieTerrain = NULL;
	for(int i=0; i<4; i++) donjons[i] = NULL;
	score = -100000;
	departX = -1;
	departY = -1;
	arriveeX = -1;
	arriveeY = -1;
}

Robot::~Robot() {
	if(copieTerrain != NULL) delete copieTerrain;
}



void Robot::joue(Terrain & t) {
	trouverDonjon(t);
	score = -10000; departX = -1; departY = -1; arriveeX = -1; arriveeY = -1;
	Piece * P;
	for(unsigned int y = 0; y < 9; y++)
		for(unsigned int x = 0; x < 7; x++) {
			P = t.getPiece(x, y);
			if(P != NULL && P->getCouleur() == couleur && P->getType() != donjon && P->getType() != tour_de_siege) {
				if(P->getType() == fantassin) deplacerFantassin(t, x, y);
				else if(P->getType() == paladin) deplacerPaladin(t, x, y);
				else deplacerArcher(t, x, y);
			}
		}
	if(departX != -1 && departY != -1 && arriveeX != -1 && arriveeY != -1)
		t.verifieCoup(departX, departY, arriveeX, arriveeY, false);
	else
		cout << "pas de coup trouve" << endl;
}


// déplacements :

void Robot::deplacerFantassin(const Terrain & t, unsigned int x, unsigned int y) {
	copieTerrain = new Terrain(t);
	if(couleur == rouge) {
		if(y >= 1 && copieTerrain->verifieCoup(x, y, x, y-1, false)) {
			trouveMeilleurCoup(x, y, x, y-1);
			delete copieTerrain; copieTerrain = NULL;
		}

		if(copieTerrain == NULL) copieTerrain = new Terrain(t);
		if(y+1 < 9 && copieTerrain->verifieCoup(x, y, x, y+1, true)) {
			trouveMeilleurCoup(x, y, x, y+1);
			delete copieTerrain; copieTerrain = NULL;
		}
	}
	else {
		if(y+1 < 9 && copieTerrain->verifieCoup(x, y, x, y+1, false)) {
			trouveMeilleurCoup(x, y, x, y+1);
			delete copieTerrain; copieTerrain = NULL;
		}

		if(copieTerrain == NULL) copieTerrain = new Terrain(t);
		if(y >= 1 && copieTerrain->verifieCoup(x, y, x, y-1, true)) {
			trouveMeilleurCoup(x, y, x, y-1);
			delete copieTerrain; copieTerrain = NULL;
		}
	}

	if(copieTerrain == NULL) copieTerrain = new Terrain(t);
	if(x+1 < 7 && copieTerrain->verifieCoup(x, y, x+1, y, false)) {
		trouveMeilleurCoup(x, y, x+1, y);
		delete copieTerrain; copieTerrain = NULL;
	}

	if(copieTerrain == NULL) copieTerrain = new Terrain(t);
	if(x >= 1 && copieTerrain->verifieCoup(x, y, x-1, y, false)) {
		trouveMeilleurCoup(x, y, x-1, y);
		delete copieTerrain; copieTerrain = NULL;
	}

	if(copieTerrain != NULL) {
		delete copieTerrain;
		copieTerrain = NULL;
	}
}

void Robot::deplacerPaladin(const Terrain & t, unsigned int x, unsigned int y) {
	copieTerrain = new Terrain(t);
	if(couleur == rouge) {
		if(x+1 < 7 && y >= 1 && copieTerrain->verifieCoup(x, y, x+1, y-1, false)) {
			trouveMeilleurCoup(x, y, x+1, y-1);
			delete copieTerrain; copieTerrain = NULL;
		}

		if(copieTerrain == NULL) copieTerrain = new Terrain(t);
		if(x >= 1 && y >= 1 && copieTerrain->verifieCoup(x, y, x-1, y-1, false)) {
			trouveMeilleurCoup(x, y, x-1, y-1);
			delete copieTerrain; copieTerrain = NULL;
		}

		if(copieTerrain == NULL) copieTerrain = new Terrain(t);
		if(x+1 < 7 && y+1 < 9 && copieTerrain->verifieCoup(x, y, x+1, y+1, true)) {
			trouveMeilleurCoup(x, y, x+1, y+1);
			delete copieTerrain; copieTerrain = NULL;
		}

		if(copieTerrain == NULL) copieTerrain = new Terrain(t);
		if(x >= 1 && y+1 < 9 && copieTerrain->verifieCoup(x, y, x-1, y+1, true)) {
			trouveMeilleurCoup(x, y, x-1, y+1);
			delete copieTerrain; copieTerrain = NULL;
		}
	}
	else {
		if(x+1 < 7 && y+1 < 9 && copieTerrain->verifieCoup(x, y, x+1, y+1, false)) {
			trouveMeilleurCoup(x, y, x+1, y+1);
			delete copieTerrain; copieTerrain = NULL;
		}

		if(copieTerrain == NULL) copieTerrain = new Terrain(t);
		if(x >= 1 && y+1 < 9 && copieTerrain->verifieCoup(x, y, x-1, y+1, false)) {
			trouveMeilleurCoup(x, y, x-1, y+1);
			delete copieTerrain; copieTerrain = NULL;
		}

		if(copieTerrain == NULL) copieTerrain = new Terrain(t);
		if(x+1 < 7 && y >= 1 && copieTerrain->verifieCoup(x, y, x+1, y-1, true)) {
			trouveMeilleurCoup(x, y, x+1, y-1);
			delete copieTerrain; copieTerrain = NULL;
		}

		if(copieTerrain == NULL) copieTerrain = new Terrain(t);
		if(x >= 1 && y >= 1 && copieTerrain->verifieCoup(x, y, x-1, y-1, true)) {
			trouveMeilleurCoup(x, y, x-1, y-1);
			delete copieTerrain; copieTerrain = NULL;
		}
	}

	if(copieTerrain != NULL) {
		delete copieTerrain;
		copieTerrain = NULL;
	}
}

void Robot::deplacerArcher(const Terrain & t, unsigned int x, unsigned int y) {
	copieTerrain = new Terrain(t);
	if(y >= 1 && copieTerrain->verifieCoup(x, y, x, y-1, false)) {
		trouveMeilleurCoup(x, y, x, y-1);
		delete copieTerrain; copieTerrain = NULL;
	}

	if(copieTerrain == NULL) copieTerrain = new Terrain(t);
	if(x+1 < 7 && y >= 1 && copieTerrain->verifieCoup(x, y, x+1, y-1, false)) {
		trouveMeilleurCoup(x, y, x+1, y-1);
		delete copieTerrain; copieTerrain = NULL;
	}

	if(copieTerrain == NULL) copieTerrain = new Terrain(t);
	if(x+1 < 7 && copieTerrain->verifieCoup(x, y, x+1, y, false)) {
		trouveMeilleurCoup(x, y, x+1, y);
		delete copieTerrain; copieTerrain = NULL;
	}

	if(copieTerrain == NULL) copieTerrain = new Terrain(t);
	if(x+1 < 7 && y+1 < 9 && copieTerrain->verifieCoup(x, y, x+1, y+1, false)) {
		trouveMeilleurCoup(x, y, x+1, y+1);
		delete copieTerrain; copieTerrain = NULL;
	}

	if(copieTerrain == NULL) copieTerrain = new Terrain(t);
	if(y+1 < 9 && copieTerrain->verifieCoup(x, y, x, y+1, false)) {
		trouveMeilleurCoup(x, y, x, y+1);
		delete copieTerrain; copieTerrain = NULL;
	}

	if(copieTerrain == NULL) copieTerrain = new Terrain(t);
	if(x >= 1 && y+1 < 9 && copieTerrain->verifieCoup(x, y, x-1, y+1, false)) {
		trouveMeilleurCoup(x, y, x-1, y+1);
		delete copieTerrain; copieTerrain = NULL;
	}

	if(copieTerrain == NULL) copieTerrain = new Terrain(t);
	if(x >= 1 && copieTerrain->verifieCoup(x, y, x-1, y, false)) {
		trouveMeilleurCoup(x, y, x-1, y);
		delete copieTerrain; copieTerrain = NULL;
	}

	if(copieTerrain == NULL) copieTerrain = new Terrain(t);
	if(x >= 1 && y >= 1 && copieTerrain->verifieCoup(x, y, x-1, y-1, false)) {
		trouveMeilleurCoup(x, y, x-1, y-1);
		delete copieTerrain; copieTerrain = NULL;
	}

	if(copieTerrain != NULL) {
		delete copieTerrain;
		copieTerrain = NULL;
	}
}


// évaluation :

void Robot::trouveMeilleurCoup(unsigned int dx, unsigned int dy, unsigned int ax, unsigned int ay) {
	// cout << "evaluation de x=" << dx << " y=" << dy << " -> x=" << ax << " y=" << ay << endl; // DEBUG
	int s = evaluer();
	// cout << "total : " << s << " meilleur score : " << score << endl; // DEBUG
	if(s > score || (s == score && rand()%2 == 0)) { // si le score est meilleur, on le garde; si égalité, on choisit aléatoirement
		score = s;
		departX = dx;
		departY = dy;
		arriveeX = ax;
		arriveeY = ay;
		// cout << "nouveau meilleur score : " << score << "\tcoup : x=" << departX << " y=" << departY << " -> x=" << arriveeX << " y=" << arriveeY << endl; // DEBUG
	}
}

int Robot::evaluer() {
	int s, total = 0;
	for(unsigned int y = 0; y < 9; y++)
		for(unsigned int x = 0; x < 7; x++) {
			Piece * P = copieTerrain->getPiece(x, y);
			if(P != NULL && P->getType() != tour_de_siege) {
				s = evaluerPiece(P->getType());	// cout << "\tp=" << s; // DEBUG
				s += evaluerAttaque(*P);		// cout << " a=" << s; // DEBUG
				s += evaluerSiege(*P);			// cout << " s=" << s; // DEBUG
				s += evaluerPosition(*P);		// cout << " p=" << s; // DEBUG

				if(P->getCouleur() == couleur) total += s;
				else total -= s;
				// cout << "\tscore de la piece x=" << x << " y=" << y << " : " << s << "\ttotal temporaire : " << total << endl; // DEBUG
			}
		}
	return total;
}

void Robot::trouverDonjon(const Terrain & t) {
	for(int i=0; i<4; i++) donjons[i] = NULL;

	for(unsigned int y = 0; y < 9; y++)
		for(unsigned int x = 0; x < 7; x++)
			if(t.getPiece(x, y) != NULL && t.getPiece(x, y)->getType() == donjon) {
				if(t.getPiece(x, y)->getCouleur() != couleur) {	// si c'est un donjon adverse
					if(donjons[0] == NULL) donjons[0] = t.getPiece(x, y);
					else donjons[1] = t.getPiece(x, y);
				}
				else {											// si c'est un donjon allié
					if(donjons[2] == NULL) donjons[2] = t.getPiece(x, y);
					else donjons[3] = t.getPiece(x, y);
				}
			}
}

int Robot::evaluerPiece(Type t) {
	switch (t) {
		case donjon:
			return 1000;
		case archer:
			return 400;
		case fantassin:
			return 200;
		case paladin:
			return 140;
		default:
			return 0;
	}
}

int Robot::evaluerAttaque(const Piece & P) {
	int s = 0, n = 0;

	if((P.getType() == archer || P.getType() == fantassin) && P.getY() >= 1) { // on vérifie que la pièce à le droit d'attaquer en fonction de son type
		n = evaluerUneAttaque(P.getX(), P.getY()-1, P.getCouleur());
		if(n > s) s = n;
	}

	if((P.getType() == archer || P.getType() == paladin) && P.getX()+1 < 7 && P.getY() >= 1) {
		n = evaluerUneAttaque(P.getX()+1, P.getY()-1, P.getCouleur());
		if(n > s) s = n;
	}

	if((P.getType() == archer || P.getType() == fantassin) && P.getX()+1 < 7) {
		n = evaluerUneAttaque(P.getX()+1, P.getY(), P.getCouleur());
		if(n > s) s = n;
	}

	if((P.getType() == archer || P.getType() == paladin) && P.getX()+1 < 7 && P.getY()+1 < 9) {
		n = evaluerUneAttaque(P.getX()+1, P.getY()+1, P.getCouleur());
		if(n > s) s = n;
	}

	if((P.getType() == archer || P.getType() == fantassin) && P.getY()+1 < 9) {
		n = evaluerUneAttaque(P.getX(), P.getY()+1, P.getCouleur());
		if(n > s) s = n;
	}

	if((P.getType() == archer || P.getType() == paladin) && P.getX() >= 1 && P.getY()+1 < 9) {
		n = evaluerUneAttaque(P.getX()-1, P.getY()+1, P.getCouleur());
		if(n > s) s = n;
	}

	if((P.getType() == archer || P.getType() == fantassin) && P.getX() >= 1) {
		n = evaluerUneAttaque(P.getX()-1, P.getY(), P.getCouleur());
		if(n > s) s = n;
	}

	if((P.getType() == archer || P.getType() == paladin) && P.getX() >= 1 && P.getY() >= 1) {
		n = evaluerUneAttaque(P.getX()-1, P.getY()-1, P.getCouleur());
		if(n > s) s = n;
	}

	return s;
}

int Robot::evaluerUneAttaque(unsigned int x, unsigned int y, Couleur c) {
	int n = 0;
	Piece *P = copieTerrain->getPiece(x, y);
	if(P != NULL && P->getCouleur() != c) {
		if(c == couleur)
			n = evaluerPiece(P->getType()) * 0.5;	// si on attaque une pièce adverse
		else
			n = evaluerPiece(P->getType()) * 0.75;	// si une pièce adverse nous attaque
	}
	return n;
}

int Robot::evaluerSiege(const Piece & P) {
	if(P.getType() != donjon && P.getSiege() != NULL && P.getSiege()->getCouleur() == P.getCouleur()) return 20;
	else return 0;
}

int Robot::evaluerPosition(const Piece & P) {
	assert((donjons[0] != NULL || donjons[1] != NULL) && (donjons[2] != NULL || donjons[3] != NULL));
	if(P.getType() == donjon) return 0;
	else {
		int s = 0;
		if(P.getCouleur() == couleur) {	// Si la pièce est de la couleur du robot
			if(donjons[0] != NULL) s += 11 - (int) distance(P.getX(), P.getY(), donjons[0]->getX(), donjons[0]->getY());
			if(donjons[1] != NULL) s += 11 - (int) distance(P.getX(), P.getY(), donjons[1]->getX(), donjons[1]->getY());
			return s;
		}
		else {							// Si la pièce est de la couleur de l'adversaire
			if(donjons[2] != NULL) s += 11 - (int) distance(P.getX(), P.getY(), donjons[2]->getX(), donjons[2]->getY());
			if(donjons[3] != NULL) s += 11 - (int) distance(P.getX(), P.getY(), donjons[3]->getX(), donjons[3]->getY());
			return s;
		}
	}
}

int Robot::distance(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2) {
	return (int) sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)); // norme 2 sur R²
}



void Robot::testRegression() {
	cout << endl << "Test de Robot" << endl;

	assert(couleur == noir);
	assert(copieTerrain == NULL);
	for(int i=0; i<4; i++) assert(donjons[i] == NULL);
	assert(score == -100000);
	assert(departX == -1); assert(departY == -1); assert(arriveeX == -1); assert(arriveeY == -1);
	cout << "\tTest constructeur parametre : OK" << endl;

	assert(evaluerPiece(donjon) == 1000);
	assert(evaluerPiece(archer) == 400);
	assert(evaluerPiece(fantassin) == 200);
	assert(evaluerPiece(paladin) == 140);
	assert(evaluerPiece(tour_de_siege) == 0);
	cout << "\tTest evaluerPiece : OK" << endl;

	Terrain T2("data/terrains/testEvaluerAttaque.txt");
	copieTerrain = new Terrain(T2);
	assert(evaluerAttaque(*T2.getPiece(3, 1)) == 100);
	assert(evaluerAttaque(*T2.getPiece(3, 4)) == 100);
	assert(evaluerAttaque(*T2.getPiece(3, 7)) == 100);
	assert(evaluerAttaque(*T2.getPiece(3, 6)) == 300);
	delete copieTerrain; copieTerrain = NULL;
	cout << "\tTest evaluerAttaque : OK" << endl;

	Piece P(0, 0, rouge, archer);
	Piece * S1 = new Piece(0, 0, noir, tour_de_siege);
	Piece * S2 = new Piece(0, 0, rouge, tour_de_siege);
	assert(evaluerSiege(P) == 0);
	P.setSiege(S1);
	assert(evaluerSiege(P) == 0);
	delete S1; P.setSiege(NULL);
	P.setSiege(S2);
	assert(evaluerSiege(P) == 20);
	delete S2; P.setSiege(NULL);
	cout << "\tTest evaluerSiege : OK" << endl;

	assert(distance(4, 6, 3, 4) == (int) sqrt(5));
	cout << "\tTest distance : OK" << endl;

	Terrain T3("data/terrains/classique.txt");
	trouverDonjon(T3);
	assert(donjons[0] != NULL); assert(donjons[0]->getX() == 1 && donjons[0]->getY() == 8);
	assert(donjons[1] != NULL); assert(donjons[1]->getX() == 5 && donjons[1]->getY() == 8);
	assert(donjons[2] != NULL); assert(donjons[2]->getX() == 1 && donjons[2]->getY() == 0);
	assert(donjons[3] != NULL); assert(donjons[3]->getX() == 5 && donjons[3]->getY() == 0);
	cout << "\tTest trouverDonjon : OK" << endl;

	assert(evaluerPosition(*T3.getPiece(0, 2)) == 9);
	assert(evaluerPosition(*T3.getPiece(0, 6)) == 9);
	cout << "\tTest evaluerPosition : OK" << endl;

	Terrain T4("data/terrains/testEvaluer.txt");
	copieTerrain = new Terrain(T4);
	score = -100000;
	assert(evaluer() == -88);
	cout << "\tTest evaluer : OK" << endl;

	trouveMeilleurCoup(3, 3, 3, 4);
	assert(departX == 3 && departY == 3 && arriveeX == 3 && arriveeY == 4);
	cout << "\tTest trouveMeilleurCoup : OK" << endl;
	delete copieTerrain; copieTerrain = NULL;

	Terrain T5("data/terrains/testDeplacerFantassin.txt");
	score = -100000;
	deplacerFantassin(T5, 3, 4);
	assert(arriveeX == 3 && arriveeY == 5);
	cout << "\tTest deplacerFantassin : OK" << endl;

	Terrain T6("data/terrains/testDeplacerPaladin.txt");
	score = -100000;
	deplacerPaladin(T6, 3, 4);
	assert(arriveeX == 4 && arriveeY == 5);
	cout << "\tTest deplacerPaladin : OK" << endl;

	Terrain T7("data/terrains/testDeplacerArcher.txt");
	score = -100000;
	deplacerArcher(T7, 3, 4);
	assert(arriveeX == 2 && arriveeY == 4);
	cout << "\tTest deplacerArcher : OK" << endl;

	cout << "Test de Robot : OK" << endl;
}