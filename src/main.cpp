#include "game/Jeu.h"
#include "core/Terrain.h"
#include <iostream>
using namespace std;

int main() {
	Jeu J("data/classique.txt");
	J.boucle();
	return 0;
}