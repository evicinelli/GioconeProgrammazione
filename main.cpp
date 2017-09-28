#include <iostream>
#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "GeneratoreLivelli.hpp"
#include "GestoreLivelli.hpp"
#include "Controller.hpp"
#include <string.h>
using namespace std;

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *st)
{	int length, x, y;
	float temp;

	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;


	length = strlen(st);
	temp = (width - length)/ 2;
	x = startx + (int)temp;
	mvwprintw(win, y, x, "%s", st);

}

int main()
{

    //Creazione di un solo livello 3


    //Creazione e collegamento fino al terzo livello


    GestoreLivelli gestore = GestoreLivelli();
  /*  GestoreLivelli gestore = GestoreLivelli();

>>>>>>> Stashed changes
	cout<<"Livello 2"<<endl;
	gestore.creaLivello(gestore.getLevN() + 1);
	cout<<"Livello 3"<<endl;
	gestore.creaLivello(gestore.getLevN() + 1);
	cout<<"Livello 4"<<endl;
	gestore.creaLivello(gestore.getLevN() + 1);
	gestore.creaLivello(gestore.getLevN() + 1);

	gestore.creaLivello(gestore.getLevN() + 1);

<<<<<<< Updated upstream
	gestore.creaLivello(gestore.getLevN() + 1);

	gestore.creaLivello(gestore.getLevN() + 1);

	gestore.creaLivello(gestore.getLevN() + 1);

	gestore.creaLivello(gestore.getLevN() + 1);

	gestore.creaLivello(gestore.getLevN() + 1);


    gestore.stampaCollegamentiLivelli();

    //cout<<gestore.getLevN();
	*/

	//Stanza* st= new Stanza();
	Giocatore* player=new Giocatore();
    //int c[4]={-1,2,9,-2};
    //st->riempiMatrice(50,c);
    //l->setStanza(1, st);
	Controller c = Controller(gestore, player);
	c.gioca();
	//d.disegna(0, player, l);

	return 0;
}


