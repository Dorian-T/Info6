#include "Paladin.h"
#include <iostream>

Paladin::Paladin(unsigned int Px, unsigned int Py, c Pcouleur )
{
    x = Px;
    y = Py;
    couleur = Pcouleur;
    siege = null;
}

Paladin::~Paladin()
{
    delete siege; // Utile ???
    siege = null;
}

c Paladin::getCouleur()
{
    
    return couleur;
}

Siege* Paladin::getSiege()
{
    
    return siege;
    
}

void Paladin::setSiege(Siege Psiege) {
    
    siege = Psiege;
}

void Paladin::deplacerHD( const Terrain &t)
{
    if (couleur == noir)
    {
        verifiecase(x-1,y+1);
    }
    if (couleur == rouge)
    {
        verifiecase(x+1,y-1);
    }
}

void Paladin::deplacerHG( const Terrain &t)
{
    if (couleur == noir)
    {
        verifiecase(x+1,y+1);
    }
    if (couleur == rouge)
    {
        verifiecase(x-1,y-1);
    }
}

void Paladin::deplacerBD( const Terrain &t)
{
    if (couleur == noir)
    {
        verifiecase(x-1,y-1);
    }
    if (couleur == rouge)
    {
        verifiecase(x+1,y+1);
    }
}

void Paladin::deplacerBG( const Terrain &t)
{
    if (couleur == noir)
    {
        verifiecase(x+1,y-1);
    }
    if (couleur == rouge)
    {
        verifiecase(x-1,y+1);
    }
}
