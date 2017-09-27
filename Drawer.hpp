#include <iostream>
#include <ncurses.h>
#include "Stanza.hpp"
#include "Giocatore.hpp"
#include "Arma.hpp"
using namespace std;

class Drawer{
	protected:
		//Stanza* stanza;
	
	public:
		Drawer(Stanza* s, Giocatore* g);
		void disegna(Stanza* s, Giocatore* g);
		void disegnaStanza(Stanza* s, WINDOW* win);
		void disegnaStat(Giocatore* g, WINDOW* win);
		void disegnaEquip(Giocatore* g, WINDOW* win);
	
};
