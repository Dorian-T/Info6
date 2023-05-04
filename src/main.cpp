#include "game/Jeu.h"
#include "core/Terrain.h"
#include "game/Robot.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main() {
	srand(time(NULL));
	// Jeu J("data/terrains/classique.txt");
	// J.boucle();

	Terrain T("data/terrains/classique.txt");
	Robot R(noir);
	R.joue(T);

	return 0;
}