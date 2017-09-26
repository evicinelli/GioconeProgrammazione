#include <iostream>
#include <ncurses.h>
#include "Stanza.hpp"
using namespace std;

class Drawer{
	protected:
		//Stanza* stanza;
	
	public:
		Drawer(Stanza* s);
		void disegna(Stanza* s);
		void disegnaStanza(Stanza* s, WINDOW* win);
	
};
