#include "Paladin.h"
#include <iostream>

Paladin::Paladin(unsigned int Px, unsigned int Py, enum couleur Pcouleur ) {
    x = Px;
    y = Py;
    couleur = Pcouleur;
    siege = null;
}

Paladin::~Paladin() {
    delete siege; // Utile ???
    siege = null;
}

enum  couleur Paladin::getCouleur() {
    
}

Siege* Paladin::getSiege(){
    
    return *siege;
    
}

void Paladin::setSiege() {
    
    
}

void Paladin::deplacerHD( const Terrain &t){
    
    
}
