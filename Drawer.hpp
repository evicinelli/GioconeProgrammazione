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
		WINDOW *win1; //Finestra statistiche
		WINDOW *win2; //Finestra messaggi
		WINDOW *win3; //Finestra stanza
		WINDOW *win4; //Finestra livello
		WINDOW *win5; //Finestra equipaggiamento
		WINDOW *win6; //Finestra pop up
	public:

		Drawer();

		//disegna la stanza nell'apposita finestra
		void disegnaStanza(Stanza* s);

		//disegno iniziale
		void disegna(Giocatore* g, Livello* l, Stanza* s);

		//disegna le statisctiche del personaggio nell'apposita finestra
		void disegnaStat(Giocatore* g);

		//disegna l'equipaggiamento del personaggio nell'apposita finestra
		void disegnaEquip(Giocatore* g);
		
		//scrive le stanze già visitate nel livello nell'apposita finestra
		void disegnaLiv(Livello* l, int nLiv);

		//scrive il messaggio, dato in input, nell'apposita finestra
		void disegnaMess(char msg[100]);
		
		//disegna la finestra pop up, con il messaggio da scrivere, l'elemento selezionato e il numero di stringhe escluso il titolo
		void disegnaPopUp(char msg[20][40], int selected, int nStringhe);

		//mette uno spazio nelle coordinate della matrice della stanza
		void liberaPosizione(Stanza* s, int y, int x);

		//aggiorna la posizione del giocatore nella stanza
		void posizionaGiocatore(Stanza* s, Giocatore* g);

	private:
		//date dimensioni e coordinate in input, viene creata e visualizzata la finestra 
		WINDOW* creaWin(int height, int width, int starty, int startx);

};
