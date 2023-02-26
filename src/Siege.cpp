#include "Siege.h"
#include <iostream>

Siege::Siege(char Scouleur)
{
    couleur = Scouleur;
    couleursoldat = 'o';
    soldat = &
}

Siege::~Siege()
{
    delete soldat;
}

char Siege::getCouleur()
{
    return couleur;
}

char Siege::getCouleurSoldat()
{
    return couleursoldat;
}

*void Siege::getSoldat()
{
    return
}
