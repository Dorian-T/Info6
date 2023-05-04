#include "../core/Piece.h"
#include "../core/Terrain.h"
#include "Robot.h"

#include <assert.h>
#include <iostream>
#include <math.h>
#include <string>
#include <vector>

using namespace std;


// constructeur et destructeur :

Robot::Robot(Couleur c) {
	couleur = c;
	copieTerrain = NULL;
	for(int i=0; i<4; i++) donjons[i] = NULL;
	meilleurCoupDepart = -1;
	meilleurCoupArrivee = -1;
	meilleurScore = -1000000;
}

Robot::~Robot() {
	if(copieTerrain != NULL) delete copieTerrain;
}



void Robot::joue(Terrain & t) {
	trouverDonjon(t);
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
	cout << "meilleurCoup (dans joue) : " << meilleurCoupDepart << " -> " << meilleurCoupArrivee << endl;
	if(meilleurCoupDepart != -1 && meilleurCoupArrivee != -1)
		t.verifieCoup(meilleurCoupDepart%10, meilleurCoupDepart/10, meilleurCoupArrivee%10, meilleurCoupArrivee/10, false); // pas toujours à false
	else
		cout << "pas de coup trouvé" << endl;
}


// déplacements :

void Robot::deplacerFantassin(const Terrain & t, unsigned int x, unsigned int y) {
	copieTerrain = new Terrain(t);
	if(couleur == rouge) {
		if(y >= 1 && copieTerrain->verifieCoup(x, y, x, y-1, false)) {
			evaluer(x*10+y, x*10+y-1);
			delete copieTerrain;
			copieTerrain = NULL;
		}
		if(copieTerrain == NULL) copieTerrain = new Terrain(t);
		if(y+1 < 9 && copieTerrain->verifieCoup(x, y, x, y+1, true)) {
			evaluer(x*10+y, x*10+y+1);
			delete copieTerrain;
			copieTerrain = NULL;
		}
	}
	else {
		if(y+1 < 9 && copieTerrain->verifieCoup(x, y, x, y+1, false)) {
			evaluer(x*10+y, x*10+y+1);
			delete copieTerrain;
			copieTerrain = NULL;
		}
		if(copieTerrain == NULL) copieTerrain = new Terrain(t);
		if(y >= 1 && copieTerrain->verifieCoup(x, y, x, y-1, true)) {
			evaluer(x*10+y, x*10+y-1);
			delete copieTerrain;
			copieTerrain = NULL;
		}
	}
	if(copieTerrain == NULL) copieTerrain = new Terrain(t);
	if(x+1 < 7 && copieTerrain->verifieCoup(x, y, x+1, y, false)) {
		evaluer(x*10+y, (x+1)*10+y);
		delete copieTerrain;
		copieTerrain = NULL;
	}
	if(copieTerrain == NULL) copieTerrain = new Terrain(t);
	if(x >= 1 && copieTerrain->verifieCoup(x, y, x-1, y, false)) {
		evaluer(x*10+y, (x-1)*10+y);
		delete copieTerrain;
		copieTerrain = NULL;
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
			evaluer(x*10+y, (x+1)*10+y-1);
			delete copieTerrain; copieTerrain = NULL;
		}
		if(copieTerrain == NULL) copieTerrain = new Terrain(t);
		if(x >= 1 && y >= 1 && copieTerrain->verifieCoup(x, y, x-1, y-1, false)) {
			evaluer(x*10+y, (x-1)*10+y-1);
			delete copieTerrain; copieTerrain = NULL;
		}
		if(copieTerrain == NULL) copieTerrain = new Terrain(t);
		if(x+1 < 7 && y+1 < 9 && copieTerrain->verifieCoup(x, y, x+1, y+1, true)) {
			evaluer(x*10+y, (x+1)*10+y+1);
			delete copieTerrain; copieTerrain = NULL;
		}
		if(copieTerrain == NULL) copieTerrain = new Terrain(t);
		if(x >= 1 && y+1 < 9 && copieTerrain->verifieCoup(x, y, x-1, y+1, true)) {
			evaluer(x*10+y, (x-1)*10+y+1);
			delete copieTerrain; copieTerrain = NULL;
		}
	}
	else {
		if(x+1 < 7 && y+1 < 9 && copieTerrain->verifieCoup(x, y, x+1, y+1, false)) {
			evaluer(x*10+y, (x+1)*10+y+1);
			delete copieTerrain; copieTerrain = NULL;
		}
		if(copieTerrain == NULL) copieTerrain = new Terrain(t);
		if(x >= 1 && y+1 < 9 && copieTerrain->verifieCoup(x, y, x-1, y+1, false)) {
			evaluer(x*10+y, (x-1)*10+y+1);
			delete copieTerrain; copieTerrain = NULL;
		}
		if(copieTerrain == NULL) copieTerrain = new Terrain(t);
		if(x+1 < 7 && y >= 1 && copieTerrain->verifieCoup(x, y, x+1, y-1, true)) {
			evaluer(x*10+y, (x+1)*10+y-1);
			delete copieTerrain; copieTerrain = NULL;
		}
		if(copieTerrain == NULL) copieTerrain = new Terrain(t);
		if(x >= 1 && y >= 1 && copieTerrain->verifieCoup(x, y, x-1, y-1, true)) {
			evaluer(x*10+y, (x-1)*10+y-1);
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
		evaluer(x*10+y, x*10+y-1);
		delete copieTerrain; copieTerrain = NULL;
	}
	if(copieTerrain == NULL) copieTerrain = new Terrain(t);
	if(x+1 < 7 && y >= 1 && copieTerrain->verifieCoup(x, y, x+1, y-1, false)) {
		evaluer(x*10+y, (x+1)*10+y-1);
		delete copieTerrain; copieTerrain = NULL;
	}
	if(copieTerrain == NULL) copieTerrain = new Terrain(t);
	if(x+1 < 7 && copieTerrain->verifieCoup(x, y, x+1, y, false)) {
		evaluer(x*10+y, (x+1)*10+y);
		delete copieTerrain; copieTerrain = NULL;
	}
	if(copieTerrain == NULL) copieTerrain = new Terrain(t);
	if(x+1 < 7 && y+1 < 9 && copieTerrain->verifieCoup(x, y, x+1, y+1, false)) {
		evaluer(x*10+y, (x+1)*10+y+1);
		delete copieTerrain; copieTerrain = NULL;
	}
	if(copieTerrain == NULL) copieTerrain = new Terrain(t);
	if(y+1 < 9 && copieTerrain->verifieCoup(x, y, x, y+1, false)) {
		evaluer(x*10+y, x*10+y+1);
		delete copieTerrain; copieTerrain = NULL;
	}
	if(copieTerrain == NULL) copieTerrain = new Terrain(t);
	if(x >= 1 && y+1 < 9 && copieTerrain->verifieCoup(x, y, x-1, y+1, false)) {
		evaluer(x*10+y, (x-1)*10+y+1);
		delete copieTerrain; copieTerrain = NULL;
	}
	if(copieTerrain == NULL) copieTerrain = new Terrain(t);
	if(x >= 1 && copieTerrain->verifieCoup(x, y, x-1, y, false)) {
		evaluer(x*10+y, (x-1)*10+y);
		delete copieTerrain; copieTerrain = NULL;
	}
	if(copieTerrain == NULL) copieTerrain = new Terrain(t);
	if(x >= 1 && y >= 1 && copieTerrain->verifieCoup(x, y, x-1, y-1, false)) {
		evaluer(x*10+y, (x-1)*10+y-1);
		delete copieTerrain; copieTerrain = NULL;
	}
	if(copieTerrain != NULL) {
		delete copieTerrain;
		copieTerrain = NULL;
	}
}


// évaluation :

void Robot::evaluer(unsigned int depart, unsigned int arrivee) {
	cout << "evaluation du coup " << depart << " -> " << arrivee << endl;
	int score, total = 0;
	for(unsigned int y = 0; y < 9; y++)
		for(unsigned int x = 0; x < 7; x++) {
			Piece * P = copieTerrain->getPiece(x, y);
			if(P != NULL && P->getType() != tour_de_siege) {
				score = evaluerPiece(P->getType()); cout << "\t\tpiece : " << score << endl;
				score -= evaluerMenace(*P); cout << "\t\tmenace : " << score << endl;
				score += evaluerAttaque(*P); cout << "\t\tattaque : " << score << endl;
				score += evaluerSiege(*P); cout << "\t\tsiege : " << score << endl;
				score += evaluerPosition(*P); cout << "\t\tposition : " << score << endl;

				if(P->getCouleur() == couleur) total += score;
				else total -= score;
				cout << "\tscore de la piece " << x << " " << y << " : " << score << endl;
				cout << "\ttotal temporaire : " << total << endl;
			}
		}
	cout << "total : " << total << " meilleur score : " << meilleurScore << endl;
	if(total > meilleurScore) {
		meilleurScore = total;
		meilleurCoupDepart = depart;
		meilleurCoupArrivee = arrivee;
		cout << "nouveau meilleur score : " << meilleurScore << endl;
		cout << "nouveau meilleur coup : " << meilleurCoupDepart << " -> " << meilleurCoupArrivee << endl;
	}
	else if(total == meilleurScore) {
		if(rand()%2 == 0) {
			meilleurScore = total;
			meilleurCoupDepart = depart;
			meilleurCoupArrivee = arrivee;
			cout << "nouveau meilleur score : " << meilleurScore << endl;
			cout << "nouveau meilleur coup : " << meilleurCoupDepart << " -> " << meilleurCoupArrivee << endl;
		}
	}
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

int Robot::evaluerMenace(const Piece & P) {
	int score = 0;
	Piece *E[8] = {NULL};

	if(P.getY() >= 1)						E[0] = copieTerrain->getPiece(P.getX(), P.getY()-1);
	if(P.getX()+1 < 7 && P.getY() >= 1)		E[1] = copieTerrain->getPiece(P.getX()+1, P.getY()-1);
	if(P.getX()+1 < 7)						E[2] = copieTerrain->getPiece(P.getX()+1, P.getY());
	if(P.getX()+1 < 7 && P.getY()+1 < 9)	E[3] = copieTerrain->getPiece(P.getX()+1, P.getY()+1);
	if(P.getY()+1 < 9)						E[4] = copieTerrain->getPiece(P.getX(), P.getY()+1);
	if(P.getX() >= 1 && P.getY()+1 < 9)		E[5] = copieTerrain->getPiece(P.getX()-1, P.getY()+1);
	if(P.getX() >= 1)						E[6] = copieTerrain->getPiece(P.getX()-1, P.getY());
	if(P.getX() >= 1 && P.getY() >= 1)		E[7] = copieTerrain->getPiece(P.getX()-1, P.getY()-1);

	if((E[0] != NULL && E[0]->getCouleur() != P.getCouleur() && (E[0]->getType() == archer || E[0]->getType() == fantassin))
		|| (E[1] != NULL && E[1]->getCouleur() != P.getCouleur() && (E[1]->getType() == archer || E[1]->getType() == paladin))
		|| (E[2] != NULL && E[2]->getCouleur() != P.getCouleur() && (E[2]->getType() == archer || E[2]->getType() == fantassin))
		|| (E[3] != NULL && E[3]->getCouleur() != P.getCouleur() && (E[3]->getType() == archer || E[3]->getType() == paladin))
		|| (E[4] != NULL && E[4]->getCouleur() != P.getCouleur() && (E[4]->getType() == archer || E[4]->getType() == fantassin))
		|| (E[5] != NULL && E[5]->getCouleur() != P.getCouleur() && (E[5]->getType() == archer || E[5]->getType() == paladin))
		|| (E[6] != NULL && E[6]->getCouleur() != P.getCouleur() && (E[6]->getType() == archer || E[6]->getType() == fantassin))
		|| (E[7] != NULL && E[7]->getCouleur() != P.getCouleur() && (E[7]->getType() == archer || E[7]->getType() == paladin)))
		score = evaluerPiece(P.getType()) * 0.75;

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

	return score;
}

int Robot::evaluerSiege(const Piece & P) {
	if(P.getType() != donjon && P.getSiege() != NULL && P.getSiege()->getCouleur() == P.getCouleur()) return 20;
	else return 0;
}

int Robot::evaluerPosition(const Piece & P) {
	assert((donjons[0] != NULL || donjons[1] != NULL) && (donjons[2] != NULL || donjons[3] != NULL));
	if(P.getType() == donjon) return 0;
	else {
		int score = 0;
		if(P.getCouleur() == couleur) {	// Si la pièce est de la couleur du robot
			if(donjons[0] != NULL) score += 11 - (int) distance(P.getX(), P.getY(), donjons[0]->getX(), donjons[0]->getY());
			if(donjons[1] != NULL) score += 11 - (int) distance(P.getX(), P.getY(), donjons[1]->getX(), donjons[1]->getY());
			return score;
		}
		else {							// Si la pièce est de la couleur de l'adversaire
			if(donjons[2] != NULL) score += 11 - (int) distance(P.getX(), P.getY(), donjons[2]->getX(), donjons[2]->getY());
			if(donjons[3] != NULL) score += 11 - (int) distance(P.getX(), P.getY(), donjons[3]->getX(), donjons[3]->getY());
			return score;
		}
	}
}

int Robot::distance(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2) {
	return (int) sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}



void Robot::testRegression() {
	cout << endl << "Test de Robot" << endl;

	assert(couleur == noir);
	assert(copieTerrain == NULL);
	for(int i=0; i<4; i++) assert(donjons[i] == NULL);
	assert(meilleurCoupDepart == -1); assert(meilleurCoupArrivee == -1); assert(meilleurScore == -1000000);
	cout << "\tTest constructeur parametre : OK" << endl;

	assert(evaluerPiece(donjon) == 1000);
	assert(evaluerPiece(archer) == 400);
	assert(evaluerPiece(fantassin) == 200);
	assert(evaluerPiece(paladin) == 140);
	assert(evaluerPiece(tour_de_siege) == 0);
	cout << "\tTest evaluerPiece : OK" << endl;

	Terrain T1("data/terrains/testEvaluerMenace.txt");
	T1.getPiece(5, 6)->deplacer(T1, "h");
	copieTerrain = new Terrain(T1);
	assert(evaluerMenace(*T1.getPiece(1, 1)) == 150);
	assert(evaluerMenace(*T1.getPiece(5, 1)) == 0);
	assert(evaluerMenace(*T1.getPiece(5, 4)) == 150);
	assert(evaluerMenace(*T1.getPiece(1, 7)) == 0);
	assert(evaluerMenace(*T1.getPiece(5, 7)) == 150);
	delete copieTerrain; copieTerrain = NULL;
	cout << "\tTest evaluerMenace : OK" << endl;

	Terrain T2("data/terrains/testEvaluerAttaque.txt");
	copieTerrain = new Terrain(T2);
	assert(evaluerAttaque(*T2.getPiece(3, 1)) == 100);
	cout << "\tTest evaluerAttaqueFantassin : OK" << endl;
	assert(evaluerAttaque(*T2.getPiece(3, 4)) == 100);
	cout << "\tTest evaluerAttaquePaladin : OK" << endl;
	assert(evaluerAttaque(*T2.getPiece(3, 7)) == 200);
	cout << "\tTest evaluerAttaqueArcher : OK" << endl;
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
	copieTerrain = new Terrain(T4); meilleurScore = -1000000; meilleurCoupDepart = -1; meilleurCoupArrivee = -1;
	evaluer(33, 34);
	assert(meilleurScore == -188);
	assert(meilleurCoupDepart == 33); assert(meilleurCoupArrivee == 34);
	delete copieTerrain; copieTerrain = NULL;
	cout << "\tTest evaluer : OK" << endl;

	Terrain T5("data/terrains/testDeplacerFantassin.txt");
	meilleurScore = -1000000; meilleurCoupDepart = -1; meilleurCoupArrivee = -1;
	deplacerFantassin(T5, 3, 4);
	assert(meilleurCoupArrivee == 35);
	cout << "\tTest deplacerFantassin : OK" << endl;

	Terrain T6("data/terrains/testDeplacerPaladin.txt");
	meilleurScore = -1000000; meilleurCoupDepart = -1; meilleurCoupArrivee = -1;
	deplacerPaladin(T6, 3, 4);
	assert(meilleurCoupArrivee == 45);
	cout << "\tTest deplacerPaladin : OK" << endl;

	Terrain T7("data/terrains/testDeplacerArcher.txt");
	meilleurScore = -1000000; meilleurCoupDepart = -1; meilleurCoupArrivee = -1;
	deplacerArcher(T7, 3, 4);
	assert(meilleurCoupArrivee == 24);
	cout << "\tTest deplacerArcher : OK" << endl;

	cout << "Test de Robot : OK" << endl;
}