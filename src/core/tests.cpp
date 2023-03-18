#include "Piece.h"
#include "Soldat.h"
#include "Siege.h"
#include "Donjon.h"
#include "Terrain.h"
#include <iostream>
using namespace std;

int main() {
	Piece P;
	P.testRegression();

	Soldat So;
	// So.testRegression();

	Siege Si;
	Si.testRegression();

	Terrain T; // modifier pour faire des tests sur les deplacements des pieces
	T.testRegression();

	Donjon D;
	D.testRegression(T);

	cout << "Tests : OK" << endl;

	return 0;
}