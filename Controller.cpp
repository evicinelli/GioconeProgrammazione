#include "Controller.hpp"

Controller::Controller(GestoreLivelli gl, Giocatore* player){
	this->gestore=gl;
	this->p=player;
	this->d = new Drawer();
}

void Controller::gioca(){
	
    Livello* l = gestore.creaLivello(2);
	
	initscr();
	raw();
	noecho();
	refresh();
	d->disegna(0, p, l);
	
}
