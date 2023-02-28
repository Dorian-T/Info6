#ifndef SIEGE_H
#define SIEGE_H

enum Couleur {
	rouge,
	noir
};

class Siege
{
	private:
		Couleur couleur;
		Couleur couleurSoldat;
		void* soldat;

	public:
		Siege(Couleur Scouleur);
		~Siege();
		Couleur getCouleur();
		Couleur getCouleurSoldat();
		void* getSoldat();
};

#endif

