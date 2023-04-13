#include "Jeu.h"
#include "../core/Terrain.h"
#include <iostream>
using namespace std;

int main() {
	Jeu J("data/tour_de_siege.txt");
	J.boucle();
	return 0;
}