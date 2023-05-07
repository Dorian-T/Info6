#ifndef ROBOT_H
#define ROBOT_H

#include "../core/Piece.h"
#include "../core/Terrain.h"

#include <string>

// classe représentant un joueur robot
class Robot {
	private:
		Couleur couleur;			// couleur du joueur

		// pour les évaluations :
		Terrain *copieTerrain;		// copie du terrain (pour tester les coups)
		Piece *donjons[4];			// tableau des donjons

		// coup à jouer :
		int score;					// score du coup à jouer
		int departX;				// coordonnée x de la pièce à déplacer
		int departY;				// coordonnée y de la pièce à déplacer
		int arriveeX;				// coordonnée x de la case d'arrivée
		int arriveeY;				// coordonnée y de la case d'arrivée

		void trouverDonjon(const Terrain & t);

		// fonctions spécifiques de déplacement des soldats
		void deplacerFantassin(const Terrain & t, unsigned int x, unsigned int y);
		void deplacerPaladin(const Terrain & t, unsigned int x, unsigned int y);
		void deplacerArcher(const Terrain & t, unsigned int x, unsigned int y);

		// évaluation :
		void trouveMeilleurCoup(unsigned int dx, unsigned int dy, unsigned int ax, unsigned int ay); // compare le coup actuel avec le meilleur coup
		int evaluer(); // évalue le terrain
		int evaluerPiece(Type t); // renvoie la valeur d'une pièce en fonction de son type
		int evaluerAttaque(const Piece & P); // renvoie le score des attaques faisables par une pièce
		int evaluerUneAttaque(unsigned int x, unsigned int y, Couleur c);
		int evaluerSiege(const Piece & P); // détermine si une pièce est sur une tour de siège
		int evaluerPosition(const Piece & P); // renvoie le score de la position d'une pièce en focntion de sa distance aux donjons adverses
		int distance(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);

	public:
		// constructeur et destructeur
		Robot(Couleur c);
		~Robot();

		// fonction principale permettant de jouer un tour
		void joue(Terrain & t);

		// tests de non-régression
		void testRegression();
};

#endif