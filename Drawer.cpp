#include "Drawer.hpp"
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>

Drawer::Drawer(Stanza* s, Personaggio* p){
	disegna(s, p);
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
			switch(m[i-in][(j-2*in)/2])
			{
				case(-3):
					mvwaddch(win, i+1, j+1, '.');
					break;
				case(-2):
					mvwaddch(win, i+1, j+1, 'X');
					break;
				case(-1):
					mvwaddch(win, i+1, j+1, '.');
					break;
				case(0):
					mvwaddch(win, i+1, j+1, (char)198);
					mvwaddch(win, i+1, j+2, (char)198);
					break;
				case(1):
					mvwaddch(win, i+1, j+1, 'M');
					break;
				case(2):
					mvwaddch(win, i+1, j+1, 'V');
					break;
				case(3):
					mvwaddch(win, i+1, j+1, 'B');
					break;
				case(4):
					int p; //in quale porta sono?
					if (i-in==0) p=0;
					else if (i-in==(s->getDimensione()-1)) p=1;
					else if ((j-2*in)==0) p=2;
					else p=3;
					if (s->getColl(p)!=-2)
						mvwaddch(win, i+1, j+1, (char)(s->getColl(p)+48));
					else
						mvwaddch(win, i+1, j+1, 'L');
					break;
				default:
					break;
			}
        }
    }
    wrefresh(win);
	
}
void Drawer::disegnaStat(Personaggio* p, WINDOW* win){
	
}

void Drawer::disegna(Stanza* s, Personaggio* p){
	
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
	win1 = creaWin(12+MAXDIM, 20, centery-(MAXDIM/2+5), centerx-(MAXDIM+20));
	win2 = creaWin(5, 2*MAXDIM+2 , centery-(MAXDIM/2+5), centerx-MAXDIM);
	win3 = creaWin(MAXDIM+2, MAXDIM*2+2 , centery-MAXDIM/2, centerx-MAXDIM);
	win4 = creaWin(5, 2*MAXDIM+2, centery+MAXDIM/2+2, centerx-MAXDIM);
	win5 = creaWin(12+MAXDIM, 20, centery-(MAXDIM/2+5), centerx+MAXDIM+2);
	
	disegnaStanza(s, win3);
	disegnaStat(p, win1);
	char c=getch();
	endwin();

    printf ("lines %d\n", w.ws_row);
    printf ("columns %d\n", w.ws_col);
}


