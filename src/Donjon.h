#ifndef DONJON_H
#define DONJON_H

enum Couleur {
    rouge,
    noir
};

class Donjon
{
    private :
    
    unsigned int x,y;
    Couleur couleur;
    unsigned int menace;
    unsigned int regardeMenace();
    
    public :
    
    Donjon(unsigned int Dx, unsigned int Dy, Couleur Pcouleur);
    ~Donjon();
    Couleur getCouleur() const;
    unsigned int getMenace() const;
    
};

#endif
