#ifndef CASE_H
#define CASE_H // est-ce qu'il y a besoin de cette classe ?

enum c {
	rouge = 0,
	noir = 1
};

enum t {
	fantassin = 1,
	paladin = 2,
	archer = 3,
	siege = 4,
	donjon = 5
};

class Case {
	private:
		t type;
		c couleur;
		void* piece;
	public:
		Case();
		Case(t Ctype, c Ccouleur, void* Cpiece);
		~Case();
};

#endif