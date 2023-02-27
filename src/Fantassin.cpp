#include "Fantassin.h"
#include <iostream>

Fantassin::Fantassin(unsigned int Fx, unsigned int Fy, c Fcouleur ) {
	x = Fx;
	y = Fy;
	couleur = Fcouleur;
	siege = NULL;
}

Fantassin::~Fantassin() {
	delete siege; // Utile ???
	siege = NULL;
}

c Fantassin::getCouleur() {
	
	return couleur;
}

Siege* Fantassin::getSiege() {
	
	return siege;
	
}

void Fantassin::setSiege(Siege * Fsiege) {
	
	siege = Fsiege;
}

void Fantassin::deplacerH(const Terrain & t) {
	if (couleur == noir)
	{
		verifieCase(x,y+1);
	}
	if (couleur == rouge)
	{
		verifieCase(x,y-1);
	}
}

void Fantassin::deplacerD( const Terrain &t) {
	if (couleur == noir)
	{
		verifieCase(x-1,y);
	}
	if (couleur == rouge)
	{
		verifieCase(x+1,y);
	}
}

void Fantassin::deplacerB( const Terrain &t) {
	if (couleur == noir)
	{
		verifieCase(x,y-1);
	}
	if (couleur == rouge)
	{
		verifieCase(x,y+1);
	}
}

void Fantassin::deplacerG( const Terrain &t) {
	if (couleur == noir) verifieCase(x+1,y);
	else verifieCase(x-1,y);
}