#include "Piece.h"
#include "Soldat.h"
#include "Siege.h"
#include "Donjon.h"
#include "TerrainTest.h"
#include <iostream>
#include <assert.h>
using namespace std;

Terrain::TerrainTest() {
    grilleTest[0][0] = new Soldat(0, 0, noir, fantassin);
    grilleTest[0][1] = new Donjon(0, 1, noir);
    grilleTest[0][2] = new Soldat(0, 2, noir, archer);

    grilleTest[1][0] = new Soldat(1, 0, noir, paladin);
    grilleTest[1][1] = new Siege(1, 1, noir);
    grilleTest[1][2] = new Soldat(1, 2, noir, fantassin);

    grilleTest[2][0] = NULL;
    grilleTest[2][1] = NULL;
    grilleTest[2][2] = NULL;

    grilleTest[3][0] = new Soldat(3, 0, rouge, fantassin);
    grilleTest[3][1] = new Siege(3, 1, rouge);
    grilleTest[3][2] = new Soldat(3, 2, rouge, paladin);
    
    grilleTest[4][0] = new Soldat(4, 0, rouge, archer);
    grilleTest[4][1] = new Donjon(4, 1, rouge);
    grilleTest[4][2] = new Soldat(4, 2, rouge, fantassin);
}


Terrain::~TerrainTest() {
    for(int i = 0; i < 5; i++)
        for(int j = 0; j < 3; j++) delete grille[i][j];
}

Piece* Terrain::getPieceTest(unsigned int x, unsigned int y) const {
    assert(x >= 0 && x < 5 && y >= 0 && y < 3);
    return grille[x][y];
}

bool Terrain::verifieCaseTest(unsigned int ax, unsigned int ay, unsigned int nx, unsigned int ny, bool recule) {
    bool quitteSiege = false;
    if(nx < 0 || nx > 5 || ny < 0 || ny > 3) // si la case n'est pas dans le terrain
        return false;
    else { // si la case est dans le terrain
        if(grille[nx][ny] == NULL) { // si la case est vide
            if(recule)
                return false;
        }
        else { // si la case n'est pas vide
            if(grille[nx][ny]->getCouleur() == grille[ax][ay]->getCouleur()) { // si la case est de la couleur alliee
                if(grille[nx][ny]->getType() == tour_de_siege) { // si la case est un siege
                    if(grille[nx][ny]->getSoldat() == NULL) {
                        grille[nx][ny]->setSoldat(grille[ax][ay]);
                        quitteSiege = true;
                    }
                    else if(grille[nx][ny]->getSoldat()->getCouleur() == grille[ax][ay]->getCouleur())
                        return false;
                    else {
                        delete grille[nx][ny]->getSoldat();
                        grille[nx][ny]->setSoldat(grille[ax][ay]);
                        quitteSiege = true;
                    }
                }
                else // si la case n'est pas un siege
                    return false;
            }
            else { // si la case est de la couleur adverse
                if(grille[nx][ny]->getType() == fantassin || grille[nx][ny]->getType() == paladin || grille[nx][ny]->getType() == archer) { // si la case est un soldat
                    delete grille[nx][ny];
                    quitteSiege = true;
                }
                else if(grille[nx][ny]->getType() == tour_de_siege) { // si la case est un siege
                    if(grille[nx][ny]->getSoldat() == NULL)
                        return false;
                    else if(grille[nx][ny]->getSoldat()->getCouleur() == grille[ax][ay]->getCouleur())
                        return false;
                    else {
                        delete grille[nx][ny]->getSoldat();
                        grille[nx][ny]->setSoldat(grille[ax][ay]);
                        quitteSiege = true;
                    }
                }
                else if(grille[nx][ny]->getType() == donjon) { // si la case est un donjon
                    if(grille[nx][ny]->getCouleur() == grille[ax][ay]->getCouleur())
                        return false;
                    else {
                        if(grille[nx][ny]->regardeMenace() > 1) {
                            delete grille[nx][ny];
                            quitteSiege = true;
                        }
                        else
                            return false;
                    // ne pas oublier que si les 2 donjons sont detruits, c'est la fin de partie
                    }
                }
            }
        }
        if(quitteSiege && grille[ax][ay]->getSiege() != NULL) {
            grille[nx][ny] = grille[ax][ay];
            grille[ax][ay] = grille[nx][ny]->getSiege();
            grille[nx][ny]->setSiege(NULL);
            grille[ax][ay]->setSoldat(NULL);
        }
        else {
            grille[nx][ny] = grille[ax][ay];
            grille[ax][ay] = NULL;
        }
        return true;
    }
}

void Terrain::testRegression() {
    cout << "Test de la classe Terrain" << endl;
    TerrainTest t;
    assert
    
}
