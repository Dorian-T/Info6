#include "game/Jeu.h"
#include "core/Terrain.h"
#include <iostream>
using namespace std;

int main() {
	Jeu J("data/debug.txt");
	J.boucle();
	return 0;
}