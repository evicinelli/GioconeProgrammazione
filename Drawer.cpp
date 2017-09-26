#include "Drawer.hpp"

Drawer::Drawer(Stanza* s){
	disegna(s);
}


WINDOW* creaWin(int height, int width, int starty, int startx){
	WINDOW* win = newwin(height, width, starty, startx);
	box(win, 0 , 0);	
	wrefresh(win);
	return win;
}

void Drawer::disegnaStanza(Stanza* s, WINDOW* win){
	int dim=s->getDimensione();
	int m[MAXDIM][MAXDIM], in;
	double inizio;
	s->getMatrice(m);
	inizio=(MAXDIM-dim)/2.0;
    for(int i=(int)inizio; i<dim+(int)inizio; i++){
        for (int j=(int)(2.0*inizio); j<(int)(2.0*(dim+inizio)); j+=2){
			in=(int)inizio;
			if(m[i-in][(j-2*in)/2]==-3) mvwaddch(win, i+1, j+1, '.');
			else if(m[i-in][(j-2*in)/2]==-2) mvwaddch(win, i+1, j+1, 'X');
			else if(m[i-in][(j-2*in)/2]==-1) mvwaddch(win, i+1, j+1, '.');
			else if (m[i-in][(j-2*in)/2]==0) mvwaddch(win, i+1, j+1, '#');
			else if (m[i-in][(j-2*in)/2]==1) mvwaddch(win, i+1, j+1, 'M');
			else if (m[i-in][(j-2*in)/2]==2) mvwaddch(win, i+1, j+1, 'V');
			else if (m[i-in][(j-2*in)/2]==3) mvwaddch(win, i+1, j+1, 'B');
			else if (m[i-in][(j-2*in)/2]==4) mvwaddch(win, i+1, j+1, '@');
			
			//mvwaddch(win, i+1, j+2, ' ');
        }
    }
    wrefresh(win);
	
}

void Drawer::disegna(Stanza* s){
	
	WINDOW *win1, *win2, *win3, *win4, *win5;
	
	initscr();
	raw();
	noecho();
	refresh();
	
	win1 = creaWin(12+MAXDIM, 20, 0, 0);
	win2 = creaWin(5, 22+MAXDIM , 0, 20);
	win3 = creaWin(MAXDIM+2, MAXDIM*2+2 , 5, 20);
	win4 = creaWin(5, 22+MAXDIM , 27, 20);
	win5 = creaWin(12+MAXDIM, 20, 0, 62);
	
	disegnaStanza(s, win3);
	
	char c=getch();
	endwin();
	
}


