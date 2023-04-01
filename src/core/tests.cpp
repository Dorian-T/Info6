#include "Piece.h"
#include "Terrain.h"
#include "../game/Jeu.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
	Piece P;
	P.testRegression();

	Terrain T; // modifier pour faire des tests sur les deplacements des pieces
	T.testRegression();

	Jeu J;
	string date;
	J.date(date);
	cout << date << endl;


	cout << "Tests : OK" << endl;

	return 0;
}