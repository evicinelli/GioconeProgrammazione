#include "Drawer.hpp"
#include <sys/ioctl.h> //per centrare nello schermo
#include <unistd.h>
#include <stdio.h>

Drawer::Drawer(){

}

WINDOW* Drawer::creaWin(int height, int width, int starty, int startx){
	WINDOW* win = newwin(height, width, starty, startx);
	box(win, 0 , 0);
	//wrefresh(win);
	return win;
}

void Drawer::liberaPosizione(Stanza* s, int y, int x){
	
	WINDOW* win=win3;
	int posx, posy;

	double inizio=(MAXDIM-s->getDimensione())/2.0;
	
	//conversione in coordinate grafiche
	posy=(int)inizio+1+y;
	posx=(int)(2*(inizio+x))+1;
	
    init_pair(7, COLOR_BLACK, COLOR_BLACK);
    wattron(win, COLOR_PAIR(7));
	mvwprintw(win, posy, posx,"  ");//deve liberare 2 px
	wattroff(win, COLOR_PAIR(7));
	wrefresh(win);
}
void Drawer::posizionaGiocatore(Stanza* s, Giocatore* g){
	WINDOW* win=win3;
	int posx, posy;
	double inizio=(MAXDIM-s->getDimensione())/2.0;
	
	//conversione coordinate giocatore con quelle grafiche
	posy=(int)inizio+1+g->getPosY();
	posx=(int)(2*(inizio+g->getPosX()))+1;
	
	init_pair(6, COLOR_RED, COLOR_YELLOW);
    wattron(win, COLOR_PAIR(6));
    mvwprintw(win, posy, posx,"@ "); //deve occupare 2 px
	wattroff(win, COLOR_PAIR(6));
	wrefresh(win);
}

void Drawer::disegnaStanza(Stanza* s){
    WINDOW* win=win3;
    int centerx=getmaxx(win)/2;
    int posy;
    int posx;
	int dim=s->getDimensione(); //dimensione stanza
	int m[MAXDIM][MAXDIM]; //matrice stanza
	double inizio; //prima riga e colonna per iniziare a disegnare la stanza


	wclear(win);
	box(win, 0 , 0);
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	wattron(win, COLOR_PAIR(1));
	mvwprintw(win, 0, centerx-4, " STANZA %d ", s->getId());
	wattroff(win, COLOR_PAIR(1));
	s->getMatrice(m);
	//inizio assegnato in modo che la stanza venga centrata nella finestra a prescindere dalla sua dimensione
	inizio=(MAXDIM-dim)/2.0;
	//ogni elemento della matrice occupa 2 px in larghezza e 1 px in altezza
	posy=(int)inizio+1;
	posx=(int)(2*inizio)+1;
    for (int i=0; i<dim; i++){
		for (int j=0; j<dim; j++){
			wmove(win, posy, posx);
			//controllo la matrice per vedere cosa devo rappresentare
			switch(m[i][j])
			{
				case(0): //MURO
                    init_pair(9, COLOR_BLACK, COLOR_WHITE);
                    wattron(win, COLOR_PAIR(9));
					wprintw(win, "  ");
					wattroff(win, COLOR_PAIR(9));
					break;
				case(1): //MOSTRO
                    init_pair(2, COLOR_CYAN, COLOR_BLACK);
                    wattron(win, COLOR_PAIR(2));
					waddch(win, 'M');
					wattroff(win, COLOR_PAIR(2));
					break;
				case(2): //VENDITORE
                    init_pair(3, COLOR_GREEN, COLOR_BLACK);
                    wattron(win, COLOR_PAIR(3));
					waddch(win, 'V');
					wattroff(win, COLOR_PAIR(3));
					break;
				case(3): //BAULE
					init_pair(4, COLOR_YELLOW, COLOR_BLACK);
                    wattron(win, COLOR_PAIR(4));
					waddch(win, 'B');
					wattroff(win, COLOR_PAIR(4));
					break;
				case(4): //PORTA
					int p; //in quale porta sono?
					init_pair(5, COLOR_WHITE, COLOR_BLUE);
                    wattron(win, COLOR_PAIR(5));
					if (i==0) p=0;
					else if (i==(s->getDimensione()-1)) p=1;
					else if (j==0) p=2;
					else p=3;
					//con o senza passaggio a livello
					if (s->getColl(p)!=-2) 
						wprintw(win, "%d", s->getColl(p));
					else 
                        waddch(win, 'L');
                    //se non ha due cifre aggiungo uno spazio
					if (s->getColl(p)<10 ) waddch(win, ' ');
                    wattroff(win, COLOR_PAIR(5));
					break;
				default: //VIA LIBERA
					waddch(win, ' ');
					break;
				}
				if (m[i][j]!=0 && m[i][j]!=4) waddch(win, ' '); //aggiungo uno spazio (perchè 2 px)
				posx+=2; //mi sposto per rappresentare il nuovo elemento
		}
		//cambio riga
		posx=(int)(2*inizio)+1;
		posy++;
	}
    wrefresh(win);

}
void Drawer::disegnaStat(Giocatore* p){

        WINDOW* win=win1;
        int centerx=getmaxx(win)/2;
		wclear(win);
		box(win, 0 , 0);
        if(has_colors() == FALSE){
			endwin();
			printf("Your terminal does not support color\n");
			exit(1);
        }
        start_color();			/* Start color 			*/
        init_pair(1, COLOR_RED, COLOR_BLACK);

        wattron(win, COLOR_PAIR(1));

        mvwprintw(win, 3, centerx-6, "%s", "STATISTICHE:");
        wattroff(win, COLOR_PAIR(1));

		//elencate statistiche giocatore, prelevate dalla classe Giocatore
        char str[50];
        sprintf (str, "LEV:  %d / %d", p->getLev(), 100);
        mvwprintw(win, 6, 1, "%s", str);

        sprintf (str, "Hp:   %d / %d", p->getHp(), p->getHpmax());
        mvwprintw(win, 8, 1, "%s", str);

        sprintf (str, "Oro:  %d", p->getOro());
        mvwprintw(win, 10, 1, "%s", str);

        sprintf (str, "str:  %d", p->getStr());
        mvwprintw(win, 12, 1, "%s", str);

        sprintf (str, "dex:  %d", p->getDex());
        mvwprintw(win, 14, 1, "%s", str);

        sprintf (str, "con:  %d", p->getCon());
        mvwprintw(win, 16, 1, "%s", str);

        sprintf (str, "luck:  %d", p->getLuck());
        mvwprintw(win, 18, 1, "%s", str);

        sprintf (str, "exp:  %d / %d", p->getExp() , p->getNextExp());
        mvwprintw(win, 20, 1, "%s", str);

        sprintf (str, "act:  %d / %d", p->getAct(), 5);
        mvwprintw(win, 22, 1, "%s", str);

        wrefresh(win);
}

void Drawer::disegnaMess(char msg[100]){
        WINDOW* win=win2;

		wclear(win);
		box(win, 0 , 0);
        start_color();			/* Start color*/
        init_pair(1, COLOR_RED, COLOR_BLACK);

        wattron(win, COLOR_PAIR(1));
        //print_in_middle(stdscr, LINES / 2, 0, 0, "Viola !!! In color ...");

        mvwprintw(win, 1, 20, "%s", "MESSAGGI:");
        wattroff(win, COLOR_PAIR(1));
		
		//viene scritto il messaggio
        mvwprintw(win, 2, 1, "%s", msg);

        wrefresh(win);

}

void Drawer::disegnaLiv(Livello* l, int nLiv){

	WINDOW* win=win4;
	int centerx=getmaxx(win)/2;
	
	wclear(win);
	box(win, 0 , 0);
	start_color();	/* Start color 			*/
    init_pair(1, COLOR_RED, COLOR_BLACK);
    wattron(win, COLOR_PAIR(1));
    mvwprintw(win, 1, centerx-5,"LIVELLO %d", nLiv);
    wattroff(win, COLOR_PAIR(1));

	wmove(win, 3, 2);
    wprintw(win, "Stanze: ");
	
	//vengono elecate le stanze visitate (spaziate tra loro)
	for (int i=0; i<l->getNStanze(); i++){
		if ((l->getStanza(i)).isVisited()){
            wprintw(win, "%d ", i);
		}
	}
	wrefresh(win);

}

void Drawer::disegnaEquip(Giocatore* g){

	WINDOW* win=win5;
	int centerx=getmaxx(win)/2;

	wclear(win);
	box(win, 0 , 0);
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);

	wattron(win, COLOR_PAIR(1));
	mvwprintw(win,3 ,centerx-3, "%s","ZAINO:");
	wattroff(win, COLOR_PAIR(1));

	mvwprintw(win,6,1, "Equipaggiamento: ");
	
	//viene elencato l'inventario
	for (int i=0; i<MAX_ITEM; i++){
		mvwprintw(win, 8+i,1, g->getInv(i).getNome().c_str());
	}

	mvwprintw(win, 9+MAX_ITEM,1, "Pozioni: %d", g->getPot());
	wrefresh(win);
}

void Drawer::disegnaPopUp(char msg[20][40], int selected, int nStringhe){
	
	WINDOW* win=win6;
	int centerx=getmaxx(win)/2;

	wclear(win);
	box(win, 0 , 0);
	start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
        
	wmove(win, 2, centerx-4);
	wattron(win, COLOR_PAIR(1));
	wprintw(win, "%s", msg[0]); //titolo
	wattroff(win, COLOR_PAIR(1));
	wmove(win, 3, 2); 
	wprintw(win, "%s", msg[1]); //consegna
	for (int i=2; i<=nStringhe; i++){
		wmove(win, 3+i, 2);
		//se è selezionato è giallo
		if (i==selected){
			wattron(win, COLOR_PAIR(2));
			wprintw(win, "%s", msg[i]);
			wattroff(win, COLOR_PAIR(2));
		}
		else{
			wprintw(win, "%s", msg[i]);
		}
	}
	
	wrefresh(win);
}

void Drawer::disegna(Giocatore* g, Livello* l, Stanza* s){


	struct winsize w;
    int centerx, centery; //coordinate centro terminale
    curs_set(0); //cursore invisibile
    
    //viene rilevato il centro del terminale
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	centery=w.ws_row/2-1;
	centerx=w.ws_col/2-1;
	
	//creazione finestre
	this->win1 = creaWin(7+MAXDIM, 24, centery-(MAXDIM/2+5), centerx-(MAXDIM+24));
	this->win2 = creaWin(5, 2*MAXDIM+2 , centery-(MAXDIM/2+5), centerx-MAXDIM);
	this->win3 = creaWin(MAXDIM+2, MAXDIM*2+2 , centery-MAXDIM/2, centerx-MAXDIM);
	this->win4 = creaWin(6, 2*MAXDIM+50, centery+MAXDIM/2+2, centerx-(MAXDIM+24));
	this->win5 = creaWin(7+MAXDIM, 24, centery-(MAXDIM/2+5), centerx+MAXDIM+2);
	this->win6 = creaWin(16, 32, centery-8, centerx-16);

	
	//disegno finestre
	l->visitStanza(s->getId());
	disegnaStanza(s);
	disegnaStat(g);
	disegnaEquip(g);
	disegnaLiv(l, 1);
	g->setPosX(s->getLibero());
	g->setPosY(s->getDimensione()-2);
	posizionaGiocatore(s, g);
	char msg[100];
	sprintf (msg, "Iniziamo il gioco, clicca un pulsante (no x) ");
    disegnaMess(msg);

}

void Drawer::posizionaMostro(Stanza* s, Mostro* m)
{
	WINDOW* win=win3;
	int posx, posy;
	double inizio=(MAXDIM-s->getDimensione())/2.0;
	
	//conversione coordinate giocatore con quelle grafiche
	posy=(int)inizio+1+m->getPosY();
	posx=(int)(2*(inizio+m->getPosX()))+1;
	
 	init_pair(2, COLOR_CYAN, COLOR_BLACK);
        wattron(win, COLOR_PAIR(2));
    	mvwprintw(win, posy, posx,"M "); //deve occupare 2 px
	wattroff(win, COLOR_PAIR(2));
	wrefresh(win);
}