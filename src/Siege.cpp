#include "Siege.h"
#include <iostream>

Siege::Siege(c Scouleur)
{
    couleur = Scouleur;
    soldat = null;
}

Siege::~Siege()
{
    delete soldat;
}

c Siege::getCouleur()
{
    return couleur;
}

c Siege::getCouleurSoldat()
{
    return couleurSoldat;
}

*void Siege::getSoldat()
{
    return soldat;
}
