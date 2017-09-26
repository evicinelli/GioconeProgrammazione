#include "Drawer.hpp"
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>

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
	
    struct winsize w;
    int centerx, centery;
	WINDOW *win1, *win2, *win3, *win4, *win5;
	
	initscr();
	raw();
	noecho();
	refresh();
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    
	centery=w.ws_row/2-1;
	centerx=w.ws_col/2-1;
	win1 = creaWin(12+MAXDIM, 20, centery-(MAXDIM/2+5), centerx-(MAXDIM+20));
	win2 = creaWin(5, 2*MAXDIM+2 , centery-(MAXDIM/2+5), centerx-MAXDIM);
	win3 = creaWin(MAXDIM+2, MAXDIM*2+2 , centery-MAXDIM/2, centerx-MAXDIM);
	win4 = creaWin(5, 2*MAXDIM+2, centery+MAXDIM/2+2, centerx-MAXDIM);
	win5 = creaWin(12+MAXDIM, 20, centery-(MAXDIM/2+5), centerx+MAXDIM+2);
	
	disegnaStanza(s, win3);
	
	char c=getch();
	endwin();

    printf ("lines %d\n", w.ws_row);
    printf ("columns %d\n", w.ws_col);
}


