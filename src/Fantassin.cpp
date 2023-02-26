#include "Fantassin.h"
#include <iostream>

Fantassin::Fantassin(unsigned int Fx, unsigned int Fy, c Fcouleur )
{
    x = Fx;
    y = Fy;
    couleur = Fcouleur;
    siege = null;
}

Fantassin:~Fantassin()
{
    delete siege; // Utile ???
    siege = null;
}

c Fantassin::getCouleur()
{
    
    return couleur;
}

Siege* Fantassin::getSiege()
{
    
    return siege;
    
}

void Fantassin::setSiege(Siege Fsiege) {
    
    siege = Fsiege;
}

void Fantassin::deplacerH( const Terrain &t)
{
    if (couleur == noir)
    {
        verifiecase(x,y+1);
    }
    if (couleur == rouge)
    {
        verifiecase(x,y-1);
    }
}

void Fantassin::deplacerD( const Terrain &t)
{
    if (couleur == noir)
    {
        verifiecase(x-1,y);
    }
    if (couleur == rouge)
    {
        verifiecase(x+1,y);
    }
}

void Fantassin::deplacerB( const Terrain &t)
{
    if (couleur == noir)
    {
        verifiecase(x,y-1);
    }
    if (couleur == rouge)
    {
        verifiecase(x,y+1);
    }
}

void Fantassin::deplacerG( const Terrain &t)
{
    if (couleur == noir)
    {
        verifiecase(x+1,y);
    }
    if (couleur == rouge)
    {
        verifiecase(x-1,y);
    }
}

