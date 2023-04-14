#include "core/Piece.h"
#include "core/Terrain.h"
#include "game/Jeu.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
	Piece P;
	P.testRegression();

	Terrain T; // modifier pour faire des tests sur les deplacements des pieces
	T.testRegression();

	cout << "Tests : OK" << endl;

	return 0;
}