#include "core/Piece.h"
#include "core/Terrain.h"
#include "game/Robot.h"

#include <assert.h>
#include <iostream>

using namespace std;


void testCalculMenace() { // test de la fonction Piece nécessitant un terrain
	Terrain T("data/terrains/testGetMenace.txt");
	T.getPiece(1, 6)->deplacer(T, "h");
	assert(T.getPiece(1, 8)->getMenace(T) == 3);

	cout << "Test getMenace : OK" << endl;
}

int main() {
	Piece P(1, 2, rouge, paladin);
	P.testRegression();
	testCalculMenace();

	Terrain T("data/terrains/classique.txt");
	T.testRegression();

	Robot R(noir);
	R.testRegression();

	cout << endl << "Tests : OK" << endl;

	return 0;
}