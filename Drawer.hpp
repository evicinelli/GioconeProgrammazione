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
		WINDOW *win1;
		WINDOW *win2;
		WINDOW *win3;
		WINDOW *win4;
		WINDOW *win5;
	public:

		Drawer();

		void disegnaStanza(Stanza* s);

		void disegna(Giocatore* g, Livello* l, Stanza* s);

		void disegnaStat(Giocatore* g, WINDOW* win);

		void disegnaEquip(Giocatore* g, WINDOW* win);

		void disegnaLiv(Livello* l, int nLiv);

		void disegnaMess(char msg[100]);

		void liberaPosizione(Stanza* s, int y, int x);

		void posizionaGiocatore(Stanza* s, Giocatore* g);

	private:

		WINDOW* creaWin(int height, int width, int starty, int startx);

};
