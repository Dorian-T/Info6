#include "Piece.h"
#include "Siege.h"
#include "Soldat.h"
#include <iostream>
#include <assert.h>
using namespace std;

Siege::Siege() {
	soldat = NULL;
}

Siege::~Siege() {
	if(soldat != NULL) delete soldat;
	soldat = NULL;
}

Couleur Siege::getCouleurSoldat() const {
	return couleurSoldat;
}

Soldat* Siege::getSoldat() const {
	return soldat;
}

void Siege::setCouleurSoldat(Couleur ScouleurSoldat) {
	couleurSoldat = ScouleurSoldat;
}

void Siege::setSoldat(Soldat* Ssoldat) {
	soldat = Ssoldat;
}

void Siege::testRegression() {
	cout << "Test Siege" << endl;
	Siege S;
	assert(S.soldat == NULL);
	cout << "\tTest constructeur : OK" << endl;
	S.setCouleurSoldat(rouge);
	assert(S.getCouleurSoldat() == rouge);
	cout << "\tTest setCouleurSoldat et getCouleurSoldat : OK" << endl;
	Soldat* So = new Soldat();
	S.setSoldat(So);
	assert(S.getSoldat() == So);
	cout << "\tTest setSoldat et getSoldat : OK" << endl;
	cout << "Test Siege : OK" << endl << endl;
}