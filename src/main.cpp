#include "game/Jeu.h"

#include <stdlib.h>
#include <time.h>


int main() {
	srand(time(NULL)); // initialisation de rand

	Jeu J("data/terrains/classique.txt");
	J.boucle();

	return 0;
}