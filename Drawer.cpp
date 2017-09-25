#include "Drawer.hpp"

Drawer::Drawer(){
	
}


WINDOW* creaWin(int height, int width, int starty, int startx){
	WINDOW* win = newwin(height, width, starty, startx);
	box(win, 0 , 0);	
	wrefresh(win);
	return win;
}

void Drawer::disegna(){
	
	WINDOW* win1;
	WINDOW* win2;
	WINDOW* win3;
	WINDOW* win4;
	WINDOW* win5;
	initscr();
	raw();
	noecho();
	refresh();
	win1 = creaWin(30, 20, 10, 35);
	win2 = creaWin(5, 40 , 10, 55);
	win3 = creaWin(20, 40 , 15, 55);
	win4 = creaWin(5, 40 , 35, 55);
	win5 = creaWin(30, 20, 10, 95);
	
	char c=getch();
	endwin();
	
}


