#include "Piece.h"
#include "Soldat.h"
#include "Siege.h"
#include "Donjon.h"
#include "Terrain.h"

int main() {
	Piece P;
	P.testRegression();

	Soldat So;
	So.testRegression();

	Siege Si;
	Si.testRegression();

	Terrain T;

	Donjon D;
	D.testRegression(T);

	return 0;
}