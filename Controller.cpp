#include "Controller.hpp"

Controller::Controller(GestoreLivelli gl, Giocatore* player){
	this->gestore = gl;
	this->p = player;
	this->d = new Drawer();
	this->stanza = gestore.getInizio()->getStanza(0);
	p->setPosX(stanza.getLibero());
	p->setPosY(stanza.getDimensione()-2);
}

void Controller::vaiSu(){
	d->liberaPosizione(&stanza, p->getPosY(), p->getPosX());
	p->setPosY(p->getPosY()-1);
	d->posizionaGiocatore(&stanza, p->getPosY(), p->getPosX());
}
void Controller::vaiGiu(){
	d->liberaPosizione(&stanza, p->getPosY(), p->getPosX());
	p->setPosY(p->getPosY()+1);
	d->posizionaGiocatore(&stanza, p->getPosY(), p->getPosX());
}
void Controller::vaiDx(){
	d->liberaPosizione(&stanza, p->getPosY(), p->getPosX());
	p->setPosY(p->getPosX()+1);
	d->posizionaGiocatore(&stanza, p->getPosY(), p->getPosX());
}
void Controller::vaiSx(){
	d->liberaPosizione(&stanza, p->getPosY(), p->getPosX());
	p->setPosY(p->getPosX()-1);
	d->posizionaGiocatore(&stanza, p->getPosY(), p->getPosX());
}
//Giulia's metodo
void Controller::gestisciInput(char c){

}
void Controller::gioca(){
	char c=' ';
	initscr();
	raw();
	noecho();
	refresh();
	d->disegna(p, gestore.getInizio(), &stanza);
	while (p->getLev()<100 && p->getHp()>0 && c!='x'){
		c=getch();
		gestisciInput(c);
	}
	endwin();
}
