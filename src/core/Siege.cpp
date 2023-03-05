#include "Piece.h"
#include "Siege.h"
#include "Soldat.h"
#include <iostream>
#include <assert.h>
using namespace std;

Siege::Siege() {
	soldat = NULL;
}

Siege::Siege(unsigned int Px, unsigned int Py, Couleur Pcouleur) : Piece(Px, Py, Pcouleur) {
	type = siege;
	soldat = NULL;
}

Siege::~Siege() {
	if(soldat != NULL) delete soldat;
	soldat = NULL;
}

Couleur Siege::getCouleurSoldat() const {
	return couleurSoldat;
}

Piece* Siege::getSoldat() const {
	return soldat;
}

void Siege::setCouleurSoldat(Couleur ScouleurSoldat) {
	couleurSoldat = ScouleurSoldat;
}

void Siege::setSoldat(Piece* Ssoldat) {
	assert(Ssoldat->getType() == fantassin || Ssoldat->getType() == paladin || Ssoldat->getType() == archer);
	soldat = Ssoldat;
}

void Siege::testRegression() {
	cout << "Test Siege" << endl;
	assert(soldat == NULL);
	cout << "\tTest constructeur : OK" << endl;
	Siege S(1, 2, noir);
	assert(S.x == 1 && S.y == 2 && S.couleur == noir);
	cout << "\tTest constructeur parametre : OK" << endl;
	S.setCouleurSoldat(rouge);
	assert(S.getCouleurSoldat() == rouge);
	cout << "\tTest setCouleurSoldat et getCouleurSoldat : OK" << endl;
	Soldat* So = new Soldat();
	S.setSoldat(So);
	assert(S.getSoldat() == So);
	cout << "\tTest setSoldat et getSoldat : OK" << endl;
	cout << "Test Siege : OK" << endl << endl;
}