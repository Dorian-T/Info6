#include "game/Jeu.h"
#include "core/Terrain.h"
#include <iostream>
using namespace std;

int main() {
	// Jeu J("data/terrains/debug.txt");
	// J.boucle();

	Terrain T("data/terrains/classique.txt");
	Robot R(noir);
	R.joue(T);

	return 0;
}