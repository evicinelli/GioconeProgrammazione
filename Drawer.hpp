#include <iostream>
#include <ncurses.h>
#include "Stanza.hpp"
#include "Giocatore.hpp"
#include "Arma.hpp"
#include "Livello.hpp"
#include <string>

using namespace std;

class Drawer{
	protected:
		//Stanza* stanza;

	public:

		Drawer();

		void disegna(int idStanza, Giocatore* g, Livello* l);

		void disegnaStanza(int idStanza, Livello* l, WINDOW* win);

		void disegnaStat(Giocatore* g, WINDOW* win);

		void disegnaEquip(Giocatore* g, WINDOW* win);

		void disegnaLiv(Livello* l, WINDOW* win, int nLiv);

		void disegnaMess(char msg[100], WINDOW* win);

};
