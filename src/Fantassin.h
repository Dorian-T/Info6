#ifndef FANTASSIN_H
#define FANTASSIN_H

#include "Siege.h"
#include "Terrain.h"

enum c {rouge, noir};

class Fantassin
{
    private :
        unsigned int x,y;
        Siege* siege;
        c couleur;
    
    public :
        Fantassin(unsigned int Fx, unsigned int Fy, c Fcouleur );
        ~Fantassin();
        c getCouleur();
        Siege* getSiege();
        void setSiege(Siege* Fsiege);
        void deplacerH(const Terrain & t);
        void deplacerD(const Terrain & t);
        void deplacerB(const Terrain & t);
        void deplacerG(const Terrain & t);
};

#endif

