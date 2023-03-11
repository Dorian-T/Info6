#ifndef SIEGE_H
#define SIEGE_H

class Piece;
class Soldat;

class Siege : public Piece {
	private:
		Couleur couleurSoldat; // je m'en sers pas
		Piece* soldat;

	public:
		Siege();
		Siege(unsigned int Px, unsigned int Py, Couleur Pcouleur);
		~Siege();

		Couleur getCouleurSoldat() const; // utile ?
		Piece* getSoldat() const;
		void setCouleurSoldat(Couleur ScouleurSoldat); // utile ?
		void setSoldat(Piece* Ssoldat);

		void testRegression();
};

#endif

