#ifndef PALADIN_H
#define PALADIN_H

#include "Siege.h"
#include "Terrain.h"

enum c {rouge,noir};

class Paladin
{
    private :
    unsigned int x,y;
    Siege *siege;
    c couleur;
    
    public :
    Paladin(unsigned int Px, unsigned int Py, c Pcouleur );
    ~Paladin();
    c getCouleur();
    Siege* getSiege();
    void setSiege(Siege Psiege);
    void deplacerHD( const Terrain &t);
    void deplacerHG( const Terrain &t);
    void deplacerBD( const Terrain &t);
    void deplacerBG( const Terrain &t);
};

#endif
