#include "../core/Piece.h"
#include "Jeu.h"

#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;


// constructeur

Jeu::Jeu(const string & filename) {
	string dt;
	date(dt);
	nomFichierSauvegarde = "data/sauvegardes/" + dt + ".txt";
	terrain = new Terrain(filename);
	joueur1 = true;
	fin = false;
}


// fonctions permettant de jouer une partie

void Jeu::boucle() {
	cout << *terrain;
	infoPartie();
	sauvegarde();
	while (!fin) {
		if (joueur1) {
			cout << "Joueur 1 :" << endl;
			J1.joue(*terrain);
		}
		else {
			cout << "Joueur 2 :" << endl;
			J2.joue(*terrain);
		}
		joueurSuivant();
		cout << *terrain;
		sauvegarde();
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


// fonctions permettant de sauvegarder la partie

void Jeu::jour(string & jour) {
	if(jour[1] == '\0') jour = "0" + jour;
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

void Jeu::sauvegarde() { // sauvegarde le terrain dans un fichier texte
	ofstream fichier(nomFichierSauvegarde.c_str(), ios::app);
	if(fichier) {
		fichier << *terrain;
		fichier.close();
	}
	else
		cout << "Impossible d'ouvrir le fichier " << nomFichierSauvegarde << endl;
}

void Jeu::infoPartie() {
	ofstream fichier(nomFichierSauvegarde.c_str());
	if(fichier) {
		fichier << "Joueur 1 : Humain (rouge)" << endl;
		fichier << "Joueur 2 : Robot (noir)" << endl << endl;
		fichier.close();
	}
	else
		cout << "Impossible d'ouvrir le fichier " << nomFichierSauvegarde << endl;
}