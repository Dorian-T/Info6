#include "core/Piece.h"
#include "core/Terrain.h"
#include "game/Robot.h"
#include "game/Jeu.h"

#include <assert.h>
#include <iostream>
#include <string>

using namespace std;


void testCalculMenace() {
	Terrain T("data/terrains/testGetMenace.txt");
	T.getPiece(1, 6)->deplacer(T, "h");
	assert(T.getPiece(1, 8)->getMenace(T) == 3);

	cout << "Test getMenace : OK" << endl;
}

int main() {
	Piece P(1, 2, rouge, paladin);
	P.testRegression();
	testCalculMenace();
	// testDeplacement();

	Terrain T("data/terrains/classique.txt");
	// modifier pour faire des tests sur les deplacements des pieces
	T.testRegression();

	Robot R(rouge);
	R.testRegression();

	cout << "Tests : OK" << endl;

	return 0;
}