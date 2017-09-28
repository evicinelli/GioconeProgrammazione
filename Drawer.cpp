#include "Drawer.hpp"
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>

Drawer::Drawer(){
}


WINDOW* creaWin(int height, int width, int starty, int startx){
	WINDOW* win = newwin(height, width, starty, startx);
	box(win, 0 , 0);	
	wrefresh(win);
	return win;
}

void Drawer::disegnaStanza(int idStanza, Livello* l, WINDOW* win){
	
	Stanza* s=l->getPointerToStanza(idStanza);
    int posy;
    int posx;
	int dim=s->getDimensione();
	int m[MAXDIM][MAXDIM];
	double inizio;
	
	l->visitStanza(idStanza);
	wprintw(win, "STANZA %d", idStanza);
	s->getMatrice(m);
	inizio=(MAXDIM-dim)/2.0;
	posy=(int)inizio+1;
	posx=(int)(2*inizio)+1;
    for (int i=0; i<dim; i++){
		for (int j=0; j<dim; j++){
			wmove(win, posy, posx);
			switch(m[i][j])
			{
				case(-3):
					waddch(win, ' ');
					break;
				case(-2):
					waddch(win, 'X');
					break;
				case(-1):
					waddch(win, ' ');
					break;
				case(0):
					//waddch(win, '#');
					waddch(win, (char)198);
					waddch(win, (char)198);
					break;
				case(1):
					waddch(win, 'M');
					break;
				case(2):
					waddch(win, 'V');
					break;
				case(3):
					waddch(win, 'B');
					break;
				case(4):
					int p; //in quale porta sono?
					//p=0;
					if (i==0) p=0;
					else if (i==(s->getDimensione()-1)) p=1;
					else if (j==0) p=2;
					else p=3;
					if (s->getColl(p)!=-2)
						waddch(win, (char)(s->getColl(p)+48));
					else
						waddch(win, 'L');
					break;
				default:
					break;
				}
				posx+=2;
		}
		posx=(int)(2*inizio)+1;
		posy++;
	}
    wrefresh(win);
	
}
void Drawer::disegnaStat(Giocatore* g, WINDOW* win){
	int posy=2;
	wprintw(win, "PERSONAGGIO");
	wmove(win,posy,2);
	wprintw(win, "LIVELLO %d", g->getLev()); wmove(win,posy+=3,2);
	wprintw(win, "HP %d/%d", g->getHp(), g->getHpmax()); wmove(win,posy+=2,2);
	wprintw(win, "GOLD %d", g->getOro()); wmove(win,posy+=2,2);
	wprintw(win, "STR %d", g->getStr()); wmove(win,posy+=2,2);
	wprintw(win, "DEX %d", g->getDex()); wmove(win,posy+=2,2);
	wprintw(win, "CON %d", g->getCon()); wmove(win,posy+=2,2);
	wprintw(win, "LUCK %d", g->getLuck()); wmove(win,posy+=2,2);
	wprintw(win, "EXP %d/%d", g->getExp(), g->getNextExp()); wmove(win,posy+=2,2);
	wprintw(win, "ACT %d/%d", g->getAct(), AZIONE); wmove(win,posy+=2,2);
	wrefresh(win);
}
void Drawer::disegnaEquip(Giocatore* g, WINDOW* win){	
	
	wprintw(win, "ZAINO");
	wmove(win,2,2);
	wprintw(win, "EQUIPAGGIAMENTO");
	for (int i=0; i<MAX_ITEM; i++){
		wmove(win,2*i+5,2);
		wprintw(win, g->getInv(i).getNome().c_str());
	}
	wmove(win,2*MAX_ITEM+5,2);
	wprintw(win, "POZIONI %d", g->getPot());
	wrefresh(win);
}
void Drawer::disegnaLiv(Livello* l, WINDOW* win, int nLiv){
	wprintw(win, "LIVELLO %d", nLiv);
	wmove(win,1,2);
	wprintw(win, "STANZE: ");
	for (int i=0; i<l->getNStanze(); i++){
		if ((l->getStanza(i)).isVisited())
			wprintw(win, "X ");
		else
			wprintw(win, "%d ",i);
	}
	wrefresh(win);
	
}
void Drawer::disegna(int idStanza, Giocatore* g, Livello* l){
	
    struct winsize w;
    int centerx, centery;
	WINDOW *win1, *win2, *win3, *win4, *win5;
	
	initscr();
	raw();
	noecho();
	refresh();
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    
	centery=w.ws_row/2-1;
	centerx=w.ws_col/2-1	;
	win1 = creaWin(7+MAXDIM, 20, centery-(MAXDIM/2+5), centerx-(MAXDIM+20));
	win2 = creaWin(5, 2*MAXDIM+2 , centery-(MAXDIM/2+5), centerx-MAXDIM);
	win3 = creaWin(MAXDIM+2, MAXDIM*2+2 , centery-MAXDIM/2, centerx-MAXDIM);
	win4 = creaWin(6, 2*MAXDIM+42, centery+MAXDIM/2+2, centerx-(MAXDIM+20));
	win5 = creaWin(7+MAXDIM, 20, centery-(MAXDIM/2+5), centerx+MAXDIM+2);
	
	l->getStanza(idStanza).visit();
	disegnaStanza(idStanza, l, win3);
	disegnaStat(g, win1);
	disegnaEquip(g, win5);
	disegnaLiv(l, win4, 2);
	getch();
	endwin();
}


