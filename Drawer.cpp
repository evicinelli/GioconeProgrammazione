#include "Drawer.hpp"
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>

Drawer::Drawer(){

}

WINDOW* Drawer::creaWin(int height, int width, int starty, int startx){
	WINDOW* win = newwin(height, width, starty, startx);
	box(win, 0 , 0);
	wrefresh(win);
	return win;
}
void Drawer::liberaPosizione(Stanza* s, int y, int x){
	WINDOW* win=win3;
	int posx, posy;
	double inizio=(MAXDIM-s->getDimensione())/2.0;
	posy=(int)inizio+1+y;
	posx=(int)(2*(inizio+x))+1;
	mvwaddch(win, posy, posx, ' ');
	wrefresh(win);
}
void Drawer::posizionaGiocatore(Stanza* s, Giocatore* g){
	WINDOW* win=win3;
	int posx, posy;
	double inizio=(MAXDIM-s->getDimensione())/2.0;
	posy=(int)inizio+1+g->getPosY();
	posx=(int)(2*(inizio+g->getPosX()))+1;
	init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    wattron(win, COLOR_PAIR(6));
	mvwaddch(win, posy, posx, '@');
	wattroff(win, COLOR_PAIR(6));
	wrefresh(win);
}
void Drawer::disegnaStanza(Stanza* s){
    WINDOW* win=win3;
	//Stanza* s=l->getPointerToStanza(idStanza);
    int posy;
    int posx;
	int dim=s->getDimensione();
	int m[MAXDIM][MAXDIM];
	double inizio;


	wclear(win);
	box(win, 0 , 0);
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	wattron(win, COLOR_PAIR(1));
	mvwprintw(win, 0, 19, " STANZA %d ", s->getId());
	wattroff(win, COLOR_PAIR(1));
	s->getMatrice(m);
	inizio=(MAXDIM-dim)/2.0;
	posy=(int)inizio+1;
	posx=(int)(2*inizio)+1;
    for (int i=0; i<dim; i++){
		for (int j=0; j<dim; j++){
			wmove(win, posy, posx);
			switch(m[i][j])
			{
				case(0):
					//waddch(win, '#');
					waddch(win, (char)198);
					waddch(win, (char)198);
					break;
				case(1):
                    init_pair(2, COLOR_CYAN, COLOR_BLACK);
                    wattron(win, COLOR_PAIR(2));
					waddch(win, 'M');
					wattroff(win, COLOR_PAIR(2));
					break;
				case(2):
                    init_pair(3, COLOR_GREEN, COLOR_BLACK);
                    wattron(win, COLOR_PAIR(3));
					waddch(win, 'V');
					wattroff(win, COLOR_PAIR(3));
					break;
				case(3):
					init_pair(4, COLOR_YELLOW, COLOR_BLACK);
                    wattron(win, COLOR_PAIR(4));
					waddch(win, 'B');
					wattroff(win, COLOR_PAIR(4));
					break;
				case(4):
					int p; //in quale porta sono?
					//p=0;
					init_pair(5, COLOR_WHITE, COLOR_BLUE);
                    wattron(win, COLOR_PAIR(5));
					if (i==0) p=0;
					else if (i==(s->getDimensione()-1)) p=1;
					else if (j==0) p=2;
					else p=3;
					if (s->getColl(p)!=-2)
						//waddch(win, (char)(s->getColl(p)+48));
						wprintw(win, "%d", s->getColl(p));
					else
                        waddch(win, 'L');
					if (s->getColl(p)<10 ) waddch(win, ' ');
                    wattroff(win, COLOR_PAIR(5));
					break;
				default:
					waddch(win, ' ');
					break;
				}
				if (m[i][j]!=0 && m[i][j]!=4) waddch(win, ' ');
				posx+=2;
		}
		posx=(int)(2*inizio)+1;
		posy++;
	}
    wrefresh(win);

}
void Drawer::disegnaStat(Giocatore* p){

        WINDOW* win=win1;
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
        //print_in_middle(stdscr, LINES / 2, 0, 0, "Viola !!! In color ...");

        mvwprintw(win, 3, 3, "%s", "STATISTICHE:");
        wattroff(win, COLOR_PAIR(1));

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
        start_color();			/* Start color 			*/
        init_pair(1, COLOR_RED, COLOR_BLACK);

        wattron(win, COLOR_PAIR(1));
        //print_in_middle(stdscr, LINES / 2, 0, 0, "Viola !!! In color ...");

        mvwprintw(win, 1, 20, "%s", "MESSAGGI:");
        wattroff(win, COLOR_PAIR(1));

        mvwprintw(win, 2, 1, "%s", msg);

         wrefresh(win);

}

void Drawer::disegnaLiv(Livello* l, int nLiv){

	WINDOW* win=win4;

	wclear(win);
	box(win, 0 , 0);
	start_color();	/* Start color 			*/
    init_pair(1, COLOR_RED, COLOR_BLACK);
    wattron(win, COLOR_PAIR(1));
    mvwprintw(win, 1, 35,"LIVELLO %d", nLiv);
    wattroff(win, COLOR_PAIR(1));

    mvwprintw(win, 3, 2,"Stanze:");

	for (int i=0; i<l->getNStanze(); i++){
		if ((l->getStanza(i)).isVisited()){
            mvwprintw(win, 3, 10+2*i, "%d", i);
		}
	}
	wrefresh(win);

}

void Drawer::disegnaEquip(Giocatore* g){


		WINDOW* win=win5;

		wclear(win);
		box(win, 0 , 0);
        start_color();			/* Start color 			*/
        init_pair(1, COLOR_RED, COLOR_BLACK);

        wattron(win, COLOR_PAIR(1));
        //print_in_middle(stdscr, LINES / 2, 0, 0, "Viola !!! In color ...");
        mvwprintw(win,3 ,7, "%s","ZAINO:");
        wattroff(win, COLOR_PAIR(1));

	mvwprintw(win,6,1, "Equipaggiamento: ");
	int j=0;
	for (int i=0; i<MAX_ITEM; i++){
		mvwprintw(win, 10+i,1, g->getInv(i).getNome().c_str());
		j=i;
	}

	mvwprintw(win, 6+j+1,1, "Pozioni: %d", g->getPot());
	wrefresh(win);
}

void Drawer::disegna(Giocatore* g, Livello* l, Stanza* s){


	struct winsize w;
    int centerx, centery;
    curs_set(0);
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	centery=w.ws_row/2-1;
	centerx=w.ws_col/2-1;	;
	this->win1 = creaWin(7+MAXDIM, 20, centery-(MAXDIM/2+5), centerx-(MAXDIM+20));
	this->win2 = creaWin(5, 2*MAXDIM+2 , centery-(MAXDIM/2+5), centerx-MAXDIM);
	this->win3 = creaWin(MAXDIM+2, MAXDIM*2+2 , centery-MAXDIM/2, centerx-MAXDIM);
	this->win4 = creaWin(6, 2*MAXDIM+42, centery+MAXDIM/2+2, centerx-(MAXDIM+20));
	this->win5 = creaWin(7+MAXDIM, 20, centery-(MAXDIM/2+5), centerx+MAXDIM+2);


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
