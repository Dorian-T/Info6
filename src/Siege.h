#ifndef SIEGE_H
#define SIEGE_H

#include "Piece.h"

class Soldat;

class Siege : public Piece {
	private:
		Couleur couleurSoldat;
		Soldat* soldat;

	public:
		Siege();
		Siege(unsigned int Px, unsigned int Py, Couleur Pcouleur);
		~Siege();

		Couleur getCouleurSoldat() const;
		Soldat* getSoldat() const;
		void setCouleurSoldat(Couleur ScouleurSoldat);
		void setSoldat(Soldat* Ssoldat);

		void testRegression();
};

#endif

