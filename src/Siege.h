#ifndef SIEGE_H
#define SIEGE_H

enum c {rouge,noir};

class Siege
{
    private :
    
    c couleur;
    c couleurSoldat;
    void* soldat;
    
    public :
    
    Siege(c Scouleur);
    ~Siege();
    c getCouleur();
    c getCouleurSoldat();
    void* getSoldat();
};

#endif

