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

}
void Controller::vaiGiu(){
	d->liberaPosizione(&stanza, p->getPosY(), p->getPosX());
	p->setPosY(p->getPosY()+1);
}
void Controller::vaiDx(){
	d->liberaPosizione(&stanza, p->getPosY(), p->getPosX());
	p->setPosX(p->getPosX()+1);
}
void Controller::vaiSx(){
	d->liberaPosizione(&stanza, p->getPosY(), p->getPosX());
	p->setPosX(p->getPosX()-1);
}
//Giulia's metodo
void Controller::gestisciInput(char c){
    keypad(stdscr, true);
    switch(c){

        //MOVIMENTO IN ALTO
        case ((char)KEY_UP):
        if(controllaMovimento(p->getPosX(), p->getPosY()-1)==true){
            this->vaiSu();
            d->disegnaStanza(&stanza);
            d->posizionaGiocatore(&stanza, p->getPosY(), p->getPosX());
        }
        break;

        //MOVIMENTO IN BASSO
        case ((char)KEY_DOWN):
        if(controllaMovimento(p->getPosX(), p->getPosY()+1)==true){
            this->vaiGiu();
            d->disegnaStanza(&stanza);
            d->posizionaGiocatore(&stanza, p->getPosY(), p->getPosX());
        }
        break;

        //MOVIMENTO A DESTRA
        case ((char)KEY_RIGHT):
        if(controllaMovimento(p->getPosX()+1, p->getPosY())==true){
            this->vaiDx();
            d->disegnaStanza(&stanza);
            d->posizionaGiocatore(&stanza, p->getPosY(), p->getPosX());
        }
        break;

        //MOVIMENTO A SINISTRA
        case ((char)KEY_LEFT):
        if(controllaMovimento(p->getPosX()-1, p->getPosY())==true){
            this->vaiSx();
            d->disegnaStanza(&stanza);
            d->posizionaGiocatore(&stanza, p->getPosY(), p->getPosX());
        }
        break;
        //COMPRARE DA VENDIORE

        //ATTACCARE MOSTRO

        //APRIRE BAULE

        //RACCOGLIERE OGGETTI LASCIATI DAL MOSTRO

        //USA POZIONE

        //CAMBIA ARMA

        //SCARTA ARMA

        default:
        char msg[100];
        sprintf (msg, "Clicca un pulsante riconosciuto              ");
        d->disegnaMess(msg);
    }

}

bool Controller::controllaMovimento(int posX, int posY){
    bool valido=false;
    int m [24][24];
    stanza.getMatrice(m);

    if(m[posY][posX]==-3|| m[posY][posX]==-2|| m[posY][posX]==-1|| m[posY][posX]==4 ) {
        if(m[posY][posX]==4){
            //CAMBIO STANZA


            //PASSAGGIO LIVELLO
        }
        else{
            char msg[100];
            sprintf (msg, "Spostamento effettuato                   ");
            d->disegnaMess(msg);
            valido=true;
        }


    }
    else{
        char msg[100];
        sprintf (msg, "Spostamento negato                          ");
        d->disegnaMess(msg);
    }
    return valido;
}

void Controller::gioca(){
	char c=' ';
	initscr();
	raw();
	noecho();
	refresh();
	d->disegna(p, gestore.getInizio(), &stanza);
	while (p->getLev()<100 && p->getHp()>0&&c!='x'){
		c=getch();
		gestisciInput(c);
	}
	endwin();
}
