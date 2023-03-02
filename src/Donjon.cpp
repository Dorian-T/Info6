#include "Donjon.h"
#include "Piece.h"
#include "Soldat.h"
#include "Siege.h"
#include "Terrain.h"
#include <iostream>

Donjon::Donjon(unsigned int Dx, unsigned int Dy, Couleur Pcouleur)
{
    x = Dx;
    y = Dy;
    couleur = Pcouleur;
    menace = 0;
}

Donjon::~Donjon()
{
}

Couleur Donjon::getCouleur() const
{
    return couleur;
}

unsigned int Donjon::getMenace() const
{
    return menace;
}

unsigned int Donjon::regardeMenace()
{
    if (couleur == rouge)
    {
        // Regarder une case autours du donjon puis récupérer le type, sa couleur et si il est sur un siège pour ajouter sur menace.
        if 
        
    }
}
