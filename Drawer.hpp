#include <iostream>
#include <ncurses.h>
#include "Stanza.hpp"
#include "Personaggio.hpp"
using namespace std;

class Drawer{
	protected:
		//Stanza* stanza;
	
	public:
		Drawer(Stanza* s, Personaggio* p);
		void disegna(Stanza* s, Personaggio* p);
		void disegnaStanza(Stanza* s, WINDOW* win);
		void disegnaStat(Personaggio* p, WINDOW* win);
	
};
