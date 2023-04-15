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
	for(unsigned int y = 0; y < 9; y++)
		for(unsigned int x = 0; x < 7; x++) {
			P = t.getPiece(x, y);
			if(P != NULL && P->getCouleur() == couleur && P->getType() != donjon && P->getType() != tour_de_siege) {
				copieTerrain = new Terrain(t);
				if(P->getType() == fantassin) deplacerFantassin(t, x, y);
				else if(P->getType() == paladin) deplacerPaladin(t, x, y);
				else deplacerArcher(t, x, y);
				delete copieTerrain;
				copieTerrain = NULL;
			}
		}
	cout << "meilleurCoup (dans joue) : " << meilleurCoupDepart << " -> " << meilleurCoupArrivee << endl;
	t.verifieCoup(meilleurCoupDepart%10, meilleurCoupDepart/10, meilleurCoupArrivee%10, meilleurCoupArrivee/10, false);
}

void Robot::deplacerFantassin(const Terrain & t, unsigned int x, unsigned int y) {
	assert(copieTerrain->getPiece(x, y) != NULL && copieTerrain->getPiece(x, y)->getType() == fantassin);
	if(couleur == rouge) {
		if(y >= 1 && copieTerrain->verifieCoup(x, y, x, y-1, false)) {
			evaluer(x*10+y, x*10+y-1);
			delete copieTerrain;
			copieTerrain = new Terrain(t);
		}
		if(y+1 < 9 && copieTerrain->verifieCoup(x, y, x, y+1, true)) {
			evaluer(x*10+y, x*10+y+1);
			delete copieTerrain;
			copieTerrain = new Terrain(t);
		}
	}
	else {
		if(y+1 < 9 && copieTerrain->verifieCoup(x, y, x, y+1, false)) {
			evaluer(x*10+y, x*10+y+1);
			delete copieTerrain;
			copieTerrain = new Terrain(t);
		}
		if(y >= 1 && copieTerrain->verifieCoup(x, y, x, y-1, true)) {
			evaluer(x*10+y, x*10+y-1);
			delete copieTerrain;
			copieTerrain = new Terrain(t);
		}
	}
	if(x+1 < 7 && copieTerrain->verifieCoup(x, y, x+1, y, false)) {
		evaluer(x*10+y, (x+1)*10+y);
		delete copieTerrain;
		copieTerrain = new Terrain(t);
	}
	if(x >= 1 && copieTerrain->verifieCoup(x, y, x-1, y, false)) {
		evaluer(x*10+y, (x-1)*10+y);
		delete copieTerrain;
		copieTerrain = new Terrain(t);
	}
}

void Robot::deplacerPaladin(const Terrain & t, unsigned int x, unsigned int y) {
	assert(copieTerrain->getPiece(x, y) != NULL && copieTerrain->getPiece(x, y)->getType() == paladin);
	if(couleur == rouge) {
		if(x+1 < 7 && y >= 1 && copieTerrain->verifieCoup(x, y, x+1, y-1, false)) {
			evaluer(x*10+y, (x+1)*10+y-1);
			delete copieTerrain;
			copieTerrain = new Terrain(t);
		}
		if(x >= 1 && y >= 1 && copieTerrain->verifieCoup(x, y, x-1, y-1, false)) {
			evaluer(x*10+y, (x-1)*10+y-1);
			delete copieTerrain;
			copieTerrain = new Terrain(t);
		}
		if(x+1 < 7 && y+1 < 9 && copieTerrain->verifieCoup(x, y, x+1, y+1, true)) {
			evaluer(x*10+y, (x+1)*10+y+1);
			delete copieTerrain;
			copieTerrain = new Terrain(t);
		}
		if(x >= 1 && y+1 < 9 && copieTerrain->verifieCoup(x, y, x-1, y+1, true)) {
			evaluer(x*10+y, (x-1)*10+y+1);
			delete copieTerrain;
			copieTerrain = new Terrain(t);
		}
	}
	else {
		if(x+1 < 7 && y+1 < 9 && copieTerrain->verifieCoup(x, y, x+1, y+1, false)) {
			evaluer(x*10+y, (x+1)*10+y+1);
			delete copieTerrain;
			copieTerrain = new Terrain(t);
		}
		if(x >= 1 && y+1 < 9 && copieTerrain->verifieCoup(x, y, x-1, y+1, false)) {
			evaluer(x*10+y, (x-1)*10+y+1);
			delete copieTerrain;
			copieTerrain = new Terrain(t);
		}
		if(x+1 < 7 && y >= 1 && copieTerrain->verifieCoup(x, y, x+1, y-1, true)) {
			evaluer(x*10+y, (x+1)*10+y-1);
			delete copieTerrain;
			copieTerrain = new Terrain(t);
		}
		if(x >= 1 && y >= 1 && copieTerrain->verifieCoup(x, y, x-1, y-1, true)) {
			evaluer(x*10+y, (x-1)*10+y-1);
			delete copieTerrain;
			copieTerrain = new Terrain(t);
		}
	}
}

void Robot::deplacerArcher(const Terrain & t, unsigned int x, unsigned int y) {
	assert(copieTerrain->getPiece(x, y) != NULL && copieTerrain->getPiece(x, y)->getType() == archer);
	if(y >= 1 && copieTerrain->verifieCoup(x, y, x, y-1, false)) {
		evaluer(x*10+y, x*10+y-1);
		delete copieTerrain;
		copieTerrain = new Terrain(t);
	}
	if(x+1 < 7 && y >= 1 && copieTerrain->verifieCoup(x, y, x+1, y-1, false)) {
		evaluer(x*10+y, (x+1)*10+y-1);
		delete copieTerrain;
		copieTerrain = new Terrain(t);
	}
	if(x+1 < 7 && copieTerrain->verifieCoup(x, y, x+1, y, false)) {
		evaluer(x*10+y, (x+1)*10+y);
		delete copieTerrain;
		copieTerrain = new Terrain(t);
	}
	if(x+1 < 7 && y+1 < 9 && copieTerrain->verifieCoup(x, y, x+1, y+1, false)) {
		evaluer(x*10+y, (x+1)*10+y+1);
		delete copieTerrain;
		copieTerrain = new Terrain(t);
	}
	if(y+1 < 9 && copieTerrain->verifieCoup(x, y, x, y+1, false)) {
		evaluer(x*10+y, x*10+y+1);
		delete copieTerrain;
		copieTerrain = new Terrain(t);
	}
	if(x >= 1 && y+1 < 9 && copieTerrain->verifieCoup(x, y, x-1, y+1, false)) {
		evaluer(x*10+y, (x-1)*10+y+1);
		delete copieTerrain;
		copieTerrain = new Terrain(t);
	}
	if(x >= 1 && copieTerrain->verifieCoup(x, y, x-1, y, false)) {
		evaluer(x*10+y, (x-1)*10+y);
		delete copieTerrain;
		copieTerrain = new Terrain(t);
	}
	if(x >= 1 && y >= 1 && copieTerrain->verifieCoup(x, y, x-1, y-1, false)) {
		evaluer(x*10+y, (x-1)*10+y-1);
		delete copieTerrain;
		copieTerrain = new Terrain(t);
	}
}


// évaluation :

void Robot::evaluer(unsigned int depart, unsigned int arrivee) {
	cout << "evaluation du coup " << depart << " -> " << arrivee << endl;
	int score, total = 0;
	for(unsigned int y = 0; y < 9; y++)
		for(unsigned int x = 0; x < 7; x++) {
			cout << "\t" << x << " " << y << " evaluation" << endl;
			Piece * P = copieTerrain->getPiece(x, y);
			if(P != NULL && P->getType() != tour_de_siege) {
				score = evaluerPiece(P->getType());
				score += evaluerMenace(*P);
				score += evaluerAttaque(*P);
				score += evaluerSiege(*P);
				score += evaluerPosition(*P);

				if(P->getCouleur() == couleur) total += score;
				else total -= score;
				cout << "score de la piece " << x << " " << y << " : " << score << endl;
			}
		}
	if(total > meilleurScore) {
		meilleurCoupDepart = depart;
		meilleurCoupArrivee = arrivee;
		cout << "nouveau meilleur score : " << total << endl;
		cout << "nouveau meilleur coup : " << meilleurCoupDepart << " -> " << meilleurCoupArrivee << endl;
	}
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

int Robot::evaluerMenace(const Piece & P) {
	int score = 0;
	Piece *E1 = NULL, *E2 = NULL, *E3 = NULL, *E4 = NULL, *E5 = NULL, *E6 = NULL, *E7 = NULL, *E8 = NULL;

	cout << "type P : " << P.getType() << endl;
	cout << "couleur P : " << P.getCouleur() << endl;
	cout << "P.getX() : " << P.getX() << endl;
	cout << "P.getY() : " << P.getY() << endl;
	if(P.getY() >= 1)						E1 = copieTerrain->getPiece(P.getX(), P.getY()-1);
	if(P.getX()+1 < 7 && P.getY() >= 1)		E2 = copieTerrain->getPiece(P.getX()+1, P.getY()-1);
	if(P.getX()+1 < 7)						E3 = copieTerrain->getPiece(P.getX()+1, P.getY());
	if(P.getX()+1 < 7 && P.getY()+1 < 9)	E4 = copieTerrain->getPiece(P.getX()+1, P.getY()+1);
	if(P.getY()+1 < 9)						E5 = copieTerrain->getPiece(P.getX(), P.getY()+1);
	if(P.getX() >= 1 && P.getY()+1 < 9)		E6 = copieTerrain->getPiece(P.getX()-1, P.getY()+1);
	if(P.getX() >= 1)						E7 = copieTerrain->getPiece(P.getX()-1, P.getY());
	if(P.getX() >= 1 && P.getY() >= 1)		E8 = copieTerrain->getPiece(P.getX()-1, P.getY()-1);

	if((E1 != NULL && E1->getCouleur() != P.getCouleur() && (E1->getType() == archer || E1->getType() == fantassin))
		|| (E2 != NULL && E2->getCouleur() != P.getCouleur() && (E2->getType() == archer || E2->getType() == paladin))
		|| (E3 != NULL && E3->getCouleur() != P.getCouleur() && (E3->getType() == archer || E3->getType() == fantassin))
		|| (E4 != NULL && E4->getCouleur() != P.getCouleur() && (E4->getType() == archer || E4->getType() == paladin))
		|| (E5 != NULL && E5->getCouleur() != P.getCouleur() && (E5->getType() == archer || E5->getType() == fantassin))
		|| (E6 != NULL && E6->getCouleur() != P.getCouleur() && (E6->getType() == archer || E6->getType() == paladin))
		|| (E7 != NULL && E7->getCouleur() != P.getCouleur() && (E7->getType() == archer || E7->getType() == fantassin))
		|| (E8 != NULL && E8->getCouleur() != P.getCouleur() && (E8->getType() == archer || E8->getType() == paladin)))
		score = evaluerPiece(P.getType()) * 0.75;
	
	delete E1; delete E2; delete E3; delete E4; delete E5; delete E6; delete E7; delete E8;
	return score;
}

int Robot::evaluerAttaque(const Piece & P) {
	if(P.getType() == fantassin) return evaluerAttaqueFantassin(P);
	else if(P.getType() == paladin) return evaluerAttaquePaladin(P);
	else if(P.getType() == archer) return evaluerAttaqueArcher(P);
	else return 0;
}

int Robot::evaluerAttaqueFantassin(const Piece & P) {
	int score = 0;
	Piece *E = NULL;

	if(P.getY() >= 1) E = copieTerrain->getPiece(P.getX(), P.getY()-1);
	if(E != NULL && E->getCouleur() != P.getCouleur()) score += evaluerPiece(E->getType()) * 0.5;

	if(P.getX()+1 < 7) E = copieTerrain->getPiece(P.getX()+1, P.getY());
	if(E != NULL && E->getCouleur() != P.getCouleur()) score += evaluerPiece(E->getType()) * 0.5;

	if(P.getY()+1 < 9) E = copieTerrain->getPiece(P.getX(), P.getY()+1);
	if(E != NULL && E->getCouleur() != P.getCouleur()) score += evaluerPiece(E->getType()) * 0.5;

	if(P.getX() >= 1) E = copieTerrain->getPiece(P.getX()-1, P.getY());
	if(E != NULL && E->getCouleur() != P.getCouleur()) score += evaluerPiece(E->getType()) * 0.5;

	delete E;
	return score;
}

int Robot::evaluerAttaquePaladin(const Piece & P) {
	int score = 0;
	Piece *E = NULL;

	if(P.getX()+1 < 7 && P.getY() >= 1) E = copieTerrain->getPiece(P.getX()+1, P.getY()-1);
	if(E != NULL && E->getCouleur() != P.getCouleur()) score += evaluerPiece(E->getType()) * 0.5;

	if(P.getX()+1 < 7 && P.getY()+1 < 9) E = copieTerrain->getPiece(P.getX()+1, P.getY()+1);
	if(E != NULL && E->getCouleur() != P.getCouleur()) score += evaluerPiece(E->getType()) * 0.5;

	if(P.getX() >= 1 && P.getY()+1 < 9) E = copieTerrain->getPiece(P.getX()-1, P.getY()+1);
	if(E != NULL && E->getCouleur() != P.getCouleur()) score += evaluerPiece(E->getType()) * 0.5;

	if(P.getX() >= 1 && P.getY() >= 1) E = copieTerrain->getPiece(P.getX()-1, P.getY()-1);
	if(E != NULL && E->getCouleur() != P.getCouleur()) score += evaluerPiece(E->getType()) * 0.5;

	delete E;
	return score;
}

int Robot::evaluerAttaqueArcher(const Piece & P) {
	int score = 0;
	Piece *E = NULL;

	if(P.getY() >= 1) E = copieTerrain->getPiece(P.getX(), P.getY()-1);
	if(E != NULL && E->getCouleur() != P.getCouleur()) score += evaluerPiece(E->getType()) * 0.5;

	if(P.getX()+1 < 7 && P.getY() >= 1) E = copieTerrain->getPiece(P.getX()+1, P.getY()-1);
	if(E != NULL && E->getCouleur() != P.getCouleur()) score += evaluerPiece(E->getType()) * 0.5;

	if(P.getX()+1 < 7) E = copieTerrain->getPiece(P.getX()+1, P.getY());
	if(E != NULL && E->getCouleur() != P.getCouleur()) score += evaluerPiece(E->getType()) * 0.5;

	if(P.getX()+1 < 7 && P.getY()+1 < 9) E = copieTerrain->getPiece(P.getX()+1, P.getY()+1);
	if(E != NULL && E->getCouleur() != P.getCouleur()) score += evaluerPiece(E->getType()) * 0.5;

	if(P.getY()+1 < 9) E = copieTerrain->getPiece(P.getX(), P.getY()+1);
	if(E != NULL && E->getCouleur() != P.getCouleur()) score += evaluerPiece(E->getType()) * 0.5;

	if(P.getX() >= 1 && P.getY()+1 < 9) E = copieTerrain->getPiece(P.getX()-1, P.getY()+1);
	if(E != NULL && E->getCouleur() != P.getCouleur()) score += evaluerPiece(E->getType()) * 0.5;

	if(P.getX() >= 1) E = copieTerrain->getPiece(P.getX()-1, P.getY());
	if(E != NULL && E->getCouleur() != P.getCouleur()) score += evaluerPiece(E->getType()) * 0.5;

	if(P.getX() >= 1 && P.getY() >= 1) E = copieTerrain->getPiece(P.getX()-1, P.getY()-1);
	if(E != NULL && E->getCouleur() != P.getCouleur()) score += evaluerPiece(E->getType()) * 0.5;

	delete E;
	return score;
}

int Robot::evaluerSiege(const Piece & P) {
	if(P.getType() != donjon && P.getSiege() != NULL && P.getSiege()->getCouleur() == P.getCouleur()) return 20;
	else return 0;
}

int Robot::evaluerPosition(const Piece & P) {
	assert(donjon1 != NULL || donjon2 != NULL);
	if(P.getType() == donjon) return 0;
	else {
		int score = 0;
		if(donjon1 != NULL) score += distance(P.getX(), P.getY(), donjon1->getX(), donjon1->getY());
		if(donjon2 != NULL) score += distance(P.getX(), P.getY(), donjon2->getX(), donjon2->getY());
		return score;
	}
}

int Robot::distance(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2) {
	return (int) sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}


void Robot::testRegression() {
	cout << "Test de Robot" << endl;

	assert(couleur == rouge); assert(copieTerrain == NULL);
	cout << "\tTest constructeur : OK" << endl;

	assert(evaluerPiece(donjon) == 1000); assert(evaluerPiece(archer) == 400); assert(evaluerPiece(fantassin) == 200); assert(evaluerPiece(paladin) == 140); assert(evaluerPiece(tour_de_siege) == 0);
	cout << "\tTest evaluerPiece : OK" << endl;

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

	// TODO : test evaluerPosition

	assert(distance(4, 6, 3, 4) == (int) sqrt(5));
	cout << "\tTest distance : OK" << endl;
}