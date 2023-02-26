#ifndef SIEGE_H
#define SIEGE_H

class Siege
{
    private :
    
    char couleur;
    char couleurSoldat;
    void* soldat;
    
    public :
    
    Siege(char Scouleur);
    ~Siege();
    char getCouleur();
    char getCouleurSoldat();
    void* getSoldat();
}






#endif

