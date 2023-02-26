#ifndef PALADIN_H
#define PALADIN_H

#include "Siege.h"
#include "Terrain.h"


class Paladin
{
    private :
    unsigned int x,y;
    enum couleur {rouge,noir};
    Siege *siege;
    
    public :
    Paladin(unsigned int Px, unsigned int Py, enum couleur Pcouleur );
    ~Paladin();
    enum couleur getCouleur();
    Siege* getSiege();
    void setSiege();
    void deplacerHD( const Terrain &t);
    void deplacerHG( const Terrain &t);
    void deplacerBD( const Terrain &t);
    void deplacerBG( const Terrain &t);
}

#endif
