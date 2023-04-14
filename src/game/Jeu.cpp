#include "../core/Piece.h"
#include "../core/Terrain.h"
#include "Humain.h"
#include "Robot.h"
#include "Jeu.h"

#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;


Jeu::Jeu() {
	string dt;
	date(dt);
	nomFichierSauvegarde = "data/sauvegardes/sauvegarde - " + dt + ".txt";
	terrain = new Terrain();
	J1 = new Humain(rouge);
	J2 = new Robot(noir);
	joueur1 = true;
	fin = false;
}

Jeu::Jeu(const string & s): Jeu() {
	terrain = new Terrain(s);
}

void Jeu::boucle() {
	cout << *terrain;
	sauvegarde(nomFichierSauvegarde);
	while (!fin) {
		if (joueur1) {
			cout << "Joueur 1 : ";
			J1->joue(*terrain);
		}
		else {
			cout << "Joueur 2 : ";
			J2->joue(*terrain);
		}
		joueurSuivant();
		cout << *terrain;
		sauvegarde(nomFichierSauvegarde);
		finDePartie();
	}
}

void Jeu::joueurSuivant() {
	joueur1 = !joueur1;
}

void Jeu::finDePartie() {
	Piece* P1 = terrain->getPiece(1, 0);
	Piece* P2 = terrain->getPiece(5, 0);
	if((P1 == NULL || P1->getType() != donjon) && (P2 == NULL || P2->getType() != donjon)) {
		cout << endl << endl << "Le joueur 1 a gagne !" << endl;
		fin = true;
	}
	P1 = terrain->getPiece(1, 8);
	P2 = terrain->getPiece(5, 8);
	if((P1 == NULL || P1->getType() != donjon) && (P2 == NULL || P2->getType() != donjon)) {
		cout << endl << endl << "Le joueur 2 a gagne !" << endl;
		fin = true;
	}
}

void Jeu::jour(string & jour) {
	if(jour[0] != '0') jour = "0" + jour;
}

void Jeu::mois(string & mois) {
	if(mois == "Jan") mois = "01";
	else if(mois == "Feb") mois = "02";
	else if(mois == "Mar") mois = "03";
	else if(mois == "Apr") mois = "04";
	else if(mois == "May") mois = "05";
	else if(mois == "Jun") mois = "06";
	else if(mois == "Jul") mois = "07";
	else if(mois == "Aug") mois = "08";
	else if(mois == "Sep") mois = "09";
	else if(mois == "Oct") mois = "10";
	else if(mois == "Nov") mois = "11";
	else if(mois == "Dec") mois = "12";
}

void Jeu::date(string & date) {
	time_t t = time(NULL);
	date = ctime(&t);
    vector<string> tab;
    string morceau;
	int i = 0;
	while(date[i] != '\0') {
		if(date[i] != ' ')
			morceau += date[i];
		else if(morceau != "") {
			tab.push_back(morceau);
			morceau = "";
		}
		i++;
	}
	tab.push_back(morceau);
	mois(tab[1]);
	jour(tab[2]);
	date = tab[1] + "-" + tab[2] + " " + tab[3];
}

void Jeu::sauvegarde(const string & nomFichier) {
	ofstream fichier(nomFichier.c_str(), ios::app);
	if(fichier) {
		fichier << *terrain;
		fichier << endl << endl;
		fichier.close();
	}
	else
		cout << "Impossible d'ouvrir le fichier " << nomFichier << endl;
}
