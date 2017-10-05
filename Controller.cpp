#include "Controller.hpp"

Controller::Controller(GestoreLivelli gl, Giocatore* player){
	this->gestore = gl;
	this->p = player;
	this->d = new Drawer();
	this->stanza = gestore.getInizio()->getStanza(0);
	p->setPosX(stanza.getLibero());
	p->setPosY(stanza.getDimensione()-2);
	ended=false;
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


void Controller::cambiaStanza(int direzione){
	Livello* l=gestore.getLevelById(gestore.getLivello());
	int coll[4];
	int oldColl[4], inizio=0;
	int oldId=stanza.getId();

	for (int i=0; i<4; i++){
		coll[i]=stanza.getColl(i);
		oldColl[i]=coll[i];
	}

	if (coll[direzione]==-2){
		//CASO CAMBIO LIVELLO
		oldId=-2;
		if ((stanza.getId()+1)==gestore.getLivello()){
			gestore.creaLivello(gestore.getLivello() + 1);
			l=gestore.getLevelById(gestore.getLivello());
			stanza=l->getStanza(0);
		}
		else{
			gestore.passaLivPrec();
			l=gestore.getLevelById(gestore.getLivello());
			stanza=l->getStanza(l->getNStanze()-1);
		}
	}
	else{
		//CASO STESSO LIVELLO
		if (direzione==0) stanza=l->vaiNord(stanza.getId());
		else if (direzione==1) stanza=l->vaiSud(stanza.getId());
		else if (direzione==2) stanza=l->vaiOvest(stanza.getId());
		else stanza=l->vaiEst(stanza.getId());
	}
	int cont=0;
	for (int i=0; i<direzione; i++){
		if(oldColl[i]==stanza.getId())
			cont++;
	}
	//STABILISCE LA MIA NUOVA POSIZIONE NELLA STANZA
	for (int i=0; i<4; i++){
		coll[i]=stanza.getColl(i);
		if (coll[i]==oldId){
			if (cont==0)
				inizio=i;
			cont--;

		}
	}
	if (inizio==0){
		p->setPosX(stanza.getPorta(inizio));
		p->setPosY(1);
	}
	else if (inizio==1) {
		p->setPosX(stanza.getPorta(inizio));
		p->setPosY(stanza.getDimensione()-2);
	}
	else if (inizio==2) {
		p->setPosX(1);
		p->setPosY(stanza.getPorta(inizio));
	}
	else {
		p->setPosX(stanza.getDimensione()-2);
		p->setPosY(stanza.getPorta(inizio));
	}

	//DISEGNO
	d->disegnaStanza(&stanza);
	l->visitStanza(stanza.getId());
	d->disegnaLiv(l, gestore.getLivello());
	d->posizionaGiocatore(&stanza, p);
}

void Controller::scriviIstruzioni(){
	char ins[20][40], c;
	sprintf (ins[0], "ISTRUZIONI:");
	sprintf (ins[1], "h per riprendere");
	sprintf (ins[2], "X: Esci dal gioco");
	sprintf (ins[3], "A: Apri porta ");
	sprintf (ins[4], "Tasti direzionali: Movimento ");
	sprintf (ins[5], "L: Cambia arma ");
	sprintf (ins[6], "S: Scarta arma ");
	sprintf (ins[7], "B: Compra da venditore ");
	sprintf (ins[8], "K: Attacca mostro ");
	sprintf (ins[9], "O: Apri baule ");
	sprintf (ins[10], "P: Usa pozione ");
	d->disegnaPopUp(ins, -1, 10);
	do{
		c=tolower(getch());
	}while(c!='h');
	d->disegnaStanza(&stanza);
	d->posizionaGiocatore(&stanza, p);
}

void Controller::scegliArma(bool opt){ //opt=1 cambio arma, opt=0 scarta arma
	char msg[20][40], c;
	int sel=2, nStringhe=1; //inizia da 2 perchè msg[0] e msg[1] non devono essere selezionati
	sprintf (msg[0], "ARMA:");
	sprintf (msg[1], "Invio per selezionare");

	//conta quante stringhe ci sono
	for (int i=0; i<MAX_ITEM; i++){
		if (p->getInv(i).isAvailable()){
			sprintf (msg[nStringhe+1], p->getInv(i).getNome().c_str());
			nStringhe++;
		}
	}
	d->disegnaPopUp(msg, sel, nStringhe);

	do{
		c=tolower(getch());
		if (c==(char)KEY_UP && sel>2){
			sel--;
			d->disegnaPopUp(msg, sel, nStringhe);
		}
		else if (c==(char)KEY_DOWN && sel<nStringhe){
			sel++;
			d->disegnaPopUp(msg, sel, nStringhe);
		}
	}while(c!=(char)10); //char 10 = invio

	//imposta sel in modo che sia esattamente l'elemento in inventario
	for (int i=0; i<sel-2; i++){
		if (!p->getInv(i).isAvailable())
			sel++;
	}

	if (opt) p->cambioArma(sel-2);
	else p->scartaArma(sel-2);
	d->disegnaStanza(&stanza);
	d->posizionaGiocatore(&stanza, p);
	d->disegnaEquip(p);
}

void Controller::aumentaLivello(){
	char msg[20][40], c;
	int sel=2;
	sprintf (msg[0], "LIVELLO %d:", p->getLev()+1);
	sprintf (msg[1], "Invio per selezionare");
	sprintf (msg[2], "Strength");
	sprintf (msg[3], "Dexterity");
	sprintf (msg[4], "Constitution");
	sprintf (msg[5], "Luck");
	d->disegnaPopUp(msg, sel, 5);
	do{
		c=tolower(getch());
		if (c==(char)KEY_UP && sel>2){
			sel--;
			d->disegnaPopUp(msg, sel, 5);
		}
		else if (c==(char)KEY_DOWN && sel<5){
			sel++;
			d->disegnaPopUp(msg, sel, 5);
		}
	}while(c!=(char)10); //char 10 = invio
	p->levelup(sel-1);
	d->disegnaStanza(&stanza);
	d->posizionaGiocatore(&stanza, p);
	d->disegnaStat(p);
}

void Controller::gestisciInput(char c){
    keypad(stdscr, true);
    switch(c){

        //MOVIMENTO IN ALTO
        case ((char)KEY_UP):
            if (controllaMovimento(p->getPosX(), p->getPosY()-1)==true)
            {
                if(p->actMuovi()){
                    this->vaiSu();
                    d->posizionaGiocatore(&stanza, p);
                    d->disegnaStat(p);
                }
            }
        break;

        //MOVIMENTO IN BASSO
        case ((char)KEY_DOWN):
            if (controllaMovimento(p->getPosX(), p->getPosY()+1)==true)
            {
                if(p->actMuovi()){
                    this->vaiGiu();
                    d->posizionaGiocatore(&stanza, p);
                    d->disegnaStat(p);
                }
            }
        break;

        //MOVIMENTO A DESTRA
        case ((char)KEY_RIGHT):
            if (controllaMovimento(p->getPosX()+1, p->getPosY())==true)
            {
                if(p->actMuovi()){
                    this->vaiDx();
                    d->posizionaGiocatore(&stanza, p);
                    d->disegnaStat(p);
                }
            }
        break;

        //MOVIMENTO A SINISTRA
        case ((char)KEY_LEFT):
            if (controllaMovimento(p->getPosX()-1, p->getPosY())==true)
            {
                if(p->actMuovi()){
                    this->vaiSx();
                    d->posizionaGiocatore(&stanza, p);
                    d->disegnaStat(p);

                }
            }
        break;
        //APRIRE PORTA
        case ((char)('a')):
            int dir;
            if(isVicinoPorta(dir)){
                this->cambiaStanza(dir);
                char msg[100];
                sprintf (msg, "Stanza cambiata");
                d->disegnaMess(msg);
            }
        break;
        case((char)('x')):
            endwin();
            ended=true;
        break;
        //COMPRARE DA VENDIORE  (B)
        case((char)('b')):
        break;
        //ATTACCARE MOSTRO      (K)
        case((char)('k')):
        break;
        //APRIRE BAULE          (O)
        case((char)('o')):
        break;
        //RACCOGLIERE OGGETTI LASCIATI DAL MOSTRO

        //USA POZIONE           (P)
        case((char)('p')):
        break;
        //CAMBIA ARMA           (L)
        case((char)('l')):
        scegliArma(1);
        break;
        //SCARTA ARMA           (S)
        case((char)('s')):
        scegliArma(0);
        break;
		//AUMENTA LIVELLO
		case ((char)('i')):
		aumentaLivello();
		break;
        //HELP                  (H)
        case((char)('h')):
        scriviIstruzioni();
        break;

        default:
            char msg[100];
            sprintf (msg, "Clicca un pulsante riconosciuto");
            d->disegnaMess(msg);
    }
}


bool Controller::isVicinoPorta(int &dir){
		int x=p->getPosX();
		int y=p->getPosY();
		dir=-1;
		if (x==stanza.getPorta(0) && y==1) dir=0;
		if (x==stanza.getPorta(1) && y==stanza.getDimensione()-2) dir=1;
		if (x==1 && y==stanza.getPorta(2)) dir=2;
		if (x==stanza.getDimensione()-2 && y==stanza.getPorta(3)) dir=3;

		return (dir!=-1);

}

bool Controller::controllaMovimento(int posX, int posY){
    bool valido=false;
    int m [MAXDIM][MAXDIM];
    stanza.getMatrice(m);

    if(m[posY][posX]==-1) {
		char msg[100];
		sprintf (msg, "Spostamento effettuato");
		d->disegnaMess(msg);
		valido=true;
    }
    else{
        char msg[100];
        sprintf (msg, "Spostamento negato");
        d->disegnaMess(msg);
    }
    return valido;
}
bool Controller::hasGameEnded()
{
    return ended;
}
void Controller::init()
{
    initscr();
	raw();
	noecho();
	refresh();
	Arma* a1 = new Arma(20, "mazza");
	Arma* a2 = new Arma(20, "pugnale");
	p->setInv(0, *a1);
	p->setInv(1, *a2);
    d->disegna(p, gestore.getInizio(), &stanza);
}
void Controller::gioca(){

        char c=tolower(getch());
        gestisciInput(c);
        usleep(30000);
}


void Controller::printDebugMsg(const char* s)
{
    char msg[100];
    sprintf(msg, s);
    d->disegnaMess(msg);
}


Stanza* Controller::getCurrentRoom()
{
    return &stanza;
}
