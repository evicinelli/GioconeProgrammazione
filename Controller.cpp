#include "Controller.hpp"
Controller::Controller(GestoreLivelli gl, Giocatore* player){
	this->gestore = gl;
	this->p = player;
	this->d = new Drawer();
	this->stanza = gestore.getInizio()->getPointerToStanza(0);
	//posizione iniziale giocatore
	p->setPosX(stanza->getLibero());
	p->setPosY(stanza->getDimensione()-2);
	ended=false;
}

void Controller::endGame(){
	ended = true;
	d->quit();
}

void Controller::vaiSu(){
	d->liberaPosizione(stanza, p->getPosY(), p->getPosX());
	p->setPosY(p->getPosY()-1);
	d->posizionaGiocatore(stanza, p);
	d->disegnaStat(p);
}
void Controller::vaiGiu(){
	d->liberaPosizione(stanza, p->getPosY(), p->getPosX());
	p->setPosY(p->getPosY()+1);
	d->posizionaGiocatore(stanza, p);
	d->disegnaStat(p);

}
void Controller::vaiDx(){
	d->liberaPosizione(stanza, p->getPosY(), p->getPosX());
	p->setPosX(p->getPosX()+1);
	d->posizionaGiocatore(stanza, p);
	d->disegnaStat(p);

}
void Controller::vaiSx(){
	d->liberaPosizione(stanza, p->getPosY(), p->getPosX());
	p->setPosX(p->getPosX()-1);
	d->posizionaGiocatore(stanza, p);
	d->disegnaStat(p);
}

int Controller::selPopUp(char msg[20][40], int sel, int nStringhe){

	char c;
	d->disegnaPopUp(msg, sel, nStringhe);

	do{
		c=tolower(getch());
		//vado in su, a meno che non ci siano più elementi sopra
		if (c==(char)KEY_UP && sel>2){
			sel--;
			d->disegnaPopUp(msg, sel, nStringhe);
		}
		//vado in giù a meno che non ci siano più elementi sotto
		else if (c==(char)KEY_DOWN && sel<nStringhe){
			sel++;
			d->disegnaPopUp(msg, sel, nStringhe);
		}
	}while(c!=(char)10); //char 10 = invio

	return sel;
}

void Controller::cambiaStanza(int direzione){

	Livello* l=gestore.getLevelById(gestore.getLivello());
	int coll[4];
	int oldColl[4], inizio=0;
	int oldId=stanza->getId();

	for (int i=0; i<4; i++){
		coll[i]=stanza->getColl(i);
		oldColl[i]=coll[i];
	}

	if (coll[direzione]==-2){
		//CASO CAMBIO LIVELLO
		oldId=-2;
		//LIVELLO SUCCESSIVO
		if ((stanza->getId()+1)==gestore.getLivello()){
			gestore.creaLivello(gestore.getLivello() + 1);
			l=gestore.getLevelById(gestore.getLivello());
			stanza=l->getPointerToStanza(0);

			//comunicazione passaggio di livello
			printMsg("Passato al livello successivo");
		}
		//LIVELLO PRECEDENTE
		else{
			gestore.passaLivPrec();
			l=gestore.getLevelById(gestore.getLivello());
			stanza=l->getPointerToStanza(l->getNStanze()-1);

			//comunicazione passaggio di livello
			printMsg("Passato al livello precedente");
		}
	}
	else{
		//CASO STESSO LIVELLO
		if (direzione==0) stanza=l->vaiNord(stanza->getId());
		else if (direzione==1) stanza=l->vaiSud(stanza->getId());
		else if (direzione==2) stanza=l->vaiOvest(stanza->getId());
		else stanza=l->vaiEst(stanza->getId());

		//comunicazione passaggio di livello
		printMsg("Stanza cambiata");
	}
	//cont mi dice in quale delle porte con l'id della mia vecchia stanza devo riapparire (alla cont-esima)
	int cont=0;
	for (int i=0; i<direzione; i++){
		if(oldColl[i]==stanza->getId())
			cont++;
	}
	//STABILISCE LA MIA NUOVA POSIZIONE NELLA STANZA
	for (int i=0; i<4; i++){
		coll[i]=stanza->getColl(i);
		if (coll[i]==oldId){
			if (cont==0)
				inizio=i;
			cont--;
		}
	}
	//A seconda della direzione in cui riappaio cambiano le coordinate
	if (inizio==0){
		p->setPosX(stanza->getPorta(inizio));
		p->setPosY(1);
	}
	else if (inizio==1) {
		p->setPosX(stanza->getPorta(inizio));
		p->setPosY(stanza->getDimensione()-2);
	}
	else if (inizio==2) {
		p->setPosX(1);
		p->setPosY(stanza->getPorta(inizio));
	}
	else {
		p->setPosX(stanza->getDimensione()-2);
		p->setPosY(stanza->getPorta(inizio));
	}

	//DISEGNO
	d->disegnaStanza(stanza);
	l->visitStanza(stanza->getId());
	d->disegnaLiv(l, gestore.getLivello());
	d->posizionaGiocatore(stanza, p);
}

void Controller::apriBaule(int dir){
	int y, x; //coordinate baule
	x=p->getPosX();
	y=p->getPosY();

	Forziere* b =  new Forziere(gestore.getLivello());
	//viene messo nell'inventario l'oggetto
	p->setInv(libInventario(), b->getInterno());
	//impostate le coordinate del baule
	if (dir==0) y--;
	else if (dir==1) y++;
	else if (dir==2) x--;
	else if (dir==3) x++;
	stanza->setSpot(y, x, -1);
	//disegnato tutto
	d->liberaPosizione(stanza, y, x);
	d->disegnaEquip(p);
	d->disegnaStanza(stanza);
	d->posizionaGiocatore(stanza, p);

}

void Controller::scriviIstruzioni(){
	char ins[20][40], c;
	//Messaggio
	sprintf (ins[0], "ISTRUZIONI:");
	sprintf (ins[1], "h per riprendere");
	sprintf (ins[2], "X: Esci dal gioco");
	sprintf (ins[3], "A: Apri porta ");
	sprintf (ins[4], "Tasti direzionali: Movimento (1 pa)");
	sprintf (ins[5], "L: Cambia arma ");
	sprintf (ins[6], "S: Scarta arma ");
	sprintf (ins[7], "B: Compra da venditore ");
	sprintf (ins[8], "K: Attacca mostro (4 pa)");
	sprintf (ins[9], "O: Apri baule (2 pa)");
	sprintf (ins[10], "P: Usa pozione (1 pa)");
	sprintf (ins[11], "I: Informazioni sul mostro");
	sprintf (ins[12], "Z: Passa il turno ");
	d->disegnaPopUp(ins, -1, 12);
	//si chiude quando si preme h
	do{
		c=tolower(getch());
	}while(c!='h');
	//disegno sopra la finestra pop up
	d->disegnaStanza(stanza);
	d->posizionaGiocatore(stanza, p);
}

void Controller::scriviInfoMostro(Mostro* m)
{
	char info[100];
	char buf[20];
    strcpy(info,"RAZZA: ");
    strcat(info,m->getRazza().c_str());
    strcat(info,"; HP: ");
    sprintf(buf,"%d",m->getHp());
    strcat(info,buf);
    strcat(info,"/");
    sprintf(buf,"%d",m->getHpmax());
    strcat(info,buf);
    d->disegnaMess(info);
}

void Controller::scriviInfoMostroAvanzate(Mostro* m)
{
    char ins[20][40], c, buf[20];
	sprintf (ins[0], "INFO MOSTRO: ");
	sprintf (ins[1], "i per riprendere");
	sprintf (ins[2], "RAZZA: ");
	strcat	(ins[2], m->getRazza().c_str());

	sprintf (ins[3], "LIVELLO: ");
	sprintf (buf,"%d",m->getLev());
	strcat	(ins[3], buf);

	sprintf (ins[4],"HP: ");
    sprintf (buf,"%d",m->getHp());
    strcat	(ins[4],buf);
    strcat	(ins[4],"/");
    sprintf (buf,"%d",m->getHpmax());
    strcat	(ins[4],buf);

	sprintf (ins[5], "ARMA: ");
	strcat	(ins[5], m->getEquip().getNome().c_str());

	sprintf (ins[6], "STR: ");
	sprintf (buf,"%d",m->getStr());
	strcat	(ins[6],buf);

	sprintf (ins[7], "DEX: ");
	sprintf (buf,"%d",m->getDex());
	strcat	(ins[7],buf);

	d->disegnaPopUp(ins, -1, 7);
	//si chiude quando si preme h
	do{
		c=tolower(getch());
	}while(c!='i');
	//disegno sopra la finestra pop up
	d->disegnaStanza(stanza);
	d->posizionaGiocatore(stanza, p);

}

void Controller::scriviInfoAttacco(Mostro* m, int danno, bool ricevuto)
{
	char info[100];
	char buf[20];
	if (ricevuto==true)
	{
        strcpy(info,"Hai inflitto ");
        sprintf(buf,"%d",danno);
        strcat(info,buf);
        strcat(info," danni. HP: ");
		sprintf(buf,"%d",m->getHp());
		strcat(info,buf);
		strcat(info,"/");
		sprintf(buf,"%d",m->getHpmax());
		strcat(info,buf);
	}
	else
	{
		strcpy(info,"Hai ricevuto ");
        sprintf(buf,"%d",danno);
        strcat(info,buf);
        strcat(info," danni da ");
		strcat(info,m->getRazza().c_str());
	}
	d->disegnaMess(info);
}

void Controller::scriviMorteMostro(Mostro* m, int danno)
{
	char info[100];
	char buf[20];
	strcpy(info,"Hai inflitto ");
    sprintf(buf,"%d",danno);
    strcat(info,buf);
    strcat(info," danni e hai ucciso ");
    strcat(info, m->getRazza().c_str());
    d->disegnaMess(info);
}

void Controller::scegliArma(bool opt){ //opt=1 cambio arma, opt=0 scarta arma
	char msg[20][40];
	int sel=2, nStringhe=1; //inizia da 2 perchè msg[0] e msg[1] non devono essere selezionati
	sprintf (msg[0], "ARMA:");
	if (opt) sprintf (msg[1], "Scegli l'arma da cambiare");
	else sprintf (msg[1], "Scegli l'arma da scartare");

	//conta quante stringhe ci sono
	for (int i=0; i<MAX_ITEM; i++){
		if (p->getInv(i).isAvailable()){
			sprintf (msg[nStringhe+1], p->getInv(i).getNome().c_str());
			nStringhe++;
		}
	}
	sel=selPopUp(msg, sel, nStringhe);

	//imposta sel in modo che sia esattamente l'elemento in inventario
	for (int i=0; i<sel-1; i++){
		if (!p->getInv(i).isAvailable())
			sel++;
	}
	//a seconda di opt cambio o scarto l'arma
	if (sel >= 2){
		if (opt) p->cambioArma(sel-2);
		else p->scartaArma(sel-2);
	}
	//disegno sopra la pop-up
	d->disegnaStanza(stanza);
	d->posizionaGiocatore(stanza, p);
	d->disegnaEquip(p);
}

void Controller::aumentaLivello(){
	char msg[20][40];
	int sel=2;
	sprintf (msg[0], "LIVELLO %d:", p->getLev()+1);
	sprintf (msg[1], "Cosa vuoi migliorare? (Invio)");
	sprintf (msg[2], "Strength");
	sprintf (msg[3], "Dexterity");
	sprintf (msg[4], "Constitution");
	sprintf (msg[5], "Luck");
	sel=selPopUp(msg, sel, 5);

	p->levelup(sel-1);
	//disegno sopra la pop-up
	d->disegnaStanza(stanza);
	d->posizionaGiocatore(stanza, p);
	d->disegnaStat(p);
	printMsg("Livello giocatore aumentato");
}

bool Controller::chiudiGioco(){
	char msg[20][40];
	int sel=2;
	sprintf (msg[0], "ESCI");
	sprintf (msg[1], "Vuoi uscire dal gioco?");
	sprintf (msg[2], "SI");
	sprintf (msg[3], "NO");
	sel=selPopUp(msg, sel, 3);

	//disegno sopra la pop-up
	d->disegnaStanza(stanza);
	d->posizionaGiocatore(stanza, p);
	return (sel==2);

}

void Controller::gestisciInput(char c){

    int dir; //direzione nella quale sono gli oggetti
    keypad(stdscr, true);
    switch(c){

        //MOVIMENTO IN ALTO
        case ((char)KEY_UP):
            if (controllaMovimento(p->getPosX(), p->getPosY()-1)==true && p->actMuovi())
				this->vaiSu();
        break;

        //MOVIMENTO IN BASSO
        case ((char)KEY_DOWN):
            if (controllaMovimento(p->getPosX(), p->getPosY()+1)==true && p->actMuovi())
				this->vaiGiu();
        break;

        //MOVIMENTO A DESTRA
        case ((char)KEY_RIGHT):
            if (controllaMovimento(p->getPosX()+1, p->getPosY())==true && p->actMuovi())
				this->vaiDx();
        break;

        //MOVIMENTO A SINISTRA
        case ((char)KEY_LEFT):
            if (controllaMovimento(p->getPosX()-1, p->getPosY())==true && p->actMuovi())
				this->vaiSx();
        break;
        //APRIRE PORTA (A)
        case ((char)('a')):
            if(isVicino(4, dir))
                this->cambiaStanza(dir);
            else
				printMsg("Non hai una porta vicina");
		break;
		//CHIUDI GIOCO (X)
        case((char)('x')):
			if (chiudiGioco()){
				endwin();
				ended=true;
			}
        break;
        //COMPRARE DA VENDIORE  (B)
        case((char)('b')):

        break;
        //ATTACCARE MOSTRO      (K)
        case((char)('k')):
        	if (selected!=NULL && selected->isAlive())
			{
				/*int distX=abs(selected->getPosX()-p->getPosX());
				int distY=abs(selected->getPosY()-p->getPosY());
				if (distX<=1 && distY<=1 && !(distX==1 && distY==1))
				{*/
				if (isVicino(1, dir)){
					if (p->getAct()>=4)
					{
						int danno=p->attacca(selected);
						if (selected->getHp()>0)
							scriviInfoAttacco(selected,danno,true);
						else
						{
							selected->morte(p);
							scriviMorteMostro(selected,danno);
							d->disegnaEquip(p);
						}
						d->disegnaStat(p);
						d->disegnaStanza(stanza);
						d->posizionaGiocatore(stanza,p);
					}
					else
						printMsg("Non hai abbastanza punti azione (minimo 4)");
				}
			}
        break;
        //APRIRE BAULE          (O)
        case((char)('o')):
			if (isVicino(3, dir) && (libInventario()!=-1)){
				if(p->actApri())
				{
					apriBaule(dir);
					printMsg("Aperto baule");
				}
				else
					printMsg("Non hai abbastanza punti azione (minimo 2)");
			}
			else if (libInventario()==-1)
				printMsg("Hai l'inventario pieno");
			else
				printMsg("Non sei vicino a un baule");
        break;
        //RACCOGLIERE OGGETTI LASCIATI DAL MOSTRO

        //USA POZIONE           (P)
        case((char)('p')):
				if(p->getAct()>0)		//questa condizione non dovrebbe mai essere falsa (con act=0 non si può giocare); tenuta per debug
				{
					int use=p->usaPozione();
					if(use>=0)
					{
						d->disegnaStat(p);
						d->disegnaEquip(p);
						char info[100],buf[20];
						strcpy(info,"Pozione bevuta. HP recuperati: ");
						sprintf(buf,"%d",use);
						strcat(info,buf);
						d->disegnaMess(info);

					}
					else
						printMsg("Non hai pozioni nell'inventario");
				}
				else
					printMsg("Non hai abbastanza punti azione (minimo 1)");
                p->usaPozione();
                d->disegnaStat(p);
                d->disegnaEquip(p);
                printMsg("Usata pozione");
        break;
        //CAMBIA ARMA           (L)
        case((char)('l')):
			if (thereisArma()){
				scegliArma(1);
				printMsg("Arma cambiata");
			}
			else{
				printMsg("Non hai armi nell'inventario");
			}
			break;
        //SCARTA ARMA           (S)
        case((char)('s')):
			if (thereisArma()){
				scegliArma(0);
				printMsg ("Arma scartata");
			}
			else{
				printMsg("Non hai armi nell'inventario");
			}
        break;
        //HELP                  (H)
        case((char)('h')):
			scriviIstruzioni();
        break;
        //INFORMAZIONI AVANZATE SUL MOSTRO (I)
        case((char)('i')):
        	if (selected!=NULL)
			{
				if (selected->isAlive()==true)
				{
					scriviInfoMostroAvanzate(selected);
				}
				else
					printMsg("Il mostro selezionato è morto");
			}
			else
				printMsg("Nessun mostro selezionato");
		break;
		//PASSA IL TURNO		(Z)
		case((char)('z')):
			if (p->getAct()<5)
			{

				p->setAct(0);
				printMsg("Turno passato");
			}
			else
				printMsg("Devi compiere almeno un'azione per poter passare");
		break;
		//se la finestra viene ridimensionata
        case ((char)KEY_RESIZE):
            cout<<"Resized; ";
            //refresh();
            //clear();
            
			resize_term(37, 150);
            d->disegnaLiv(gestore.getLevelById(gestore.getLivello()), gestore.getLivello());
            d->disegnaStanza(stanza);
            d->posizionaGiocatore(stanza, p);
            d->disegnaStat(p);
            d->disegnaEquip(p);
            printMsg("Ripristinate dimensioni del terminale");
            refresh();
        break;

        default:
            printMsg("Clicca un pulsante riconosciuto");
		break;
    }
}

bool Controller::thereisArma(){
	bool cond=false;
	for (int i=0; i<MAX_ITEM; i++){
		if (p->getInv(i).isAvailable())
			cond=true;
	}
	return cond;
}

int Controller::libInventario(){
	int pos=-1;
	int i=0;
	while ((pos==-1) && (i<MAX_ITEM)){
		if (!p->getInv(i).isAvailable())
			pos=i;
		i++;
	}
	return pos;
}

bool Controller::isVicino(int value, int &dir){
		int x=p->getPosX();
		int y=p->getPosY();
		dir=-1;
		if (stanza->getSpot(y-1, x)==value) dir=0;
		if (stanza->getSpot(y+1, x)==value) dir=1;
		if (stanza->getSpot(y, x-1)==value) dir=2;
		if (stanza->getSpot(y, x+1)==value) dir=3;

		return (dir!=-1);

}

bool Controller::controllaMovimento(int posX, int posY){
    bool valido=false;
    int m [MAXDIM][MAXDIM];
    stanza->getMatrice(m);

	//puoi spostarti solo se la posizione è libera
    if(m[posY][posX]==-1) {
		printMsg("Spostamento effettuato");
		valido=true;
    }
    else if(m[posY][posX]==1)
	{
		//cerca il mostro a partire dalla posizione nella stanza
		selected=stanza->getMonsterByCoord(posX,posY);
		scriviInfoMostro(selected);
	}
    else{
		printMsg("Spostamento negato");
    }
    return valido;
}

bool Controller::hasGameEnded()
{
    return ended;
}

void Controller::printMsg(const char* s)
{
    char msg[100];
    sprintf(msg, s);
    d->disegnaMess(msg);
}


Stanza* Controller::getCurrentRoom()
{
    return stanza;
}

void Controller::updateMonsterCoordinates(int oldY, int oldX, Mostro* m, bool isChasing)
{
	// Pulisco le vecchie coordinate sulla matrice
	stanza->setSpot(oldY, oldX, -1);
	d->liberaPosizione(stanza, oldY, oldX);
	//printf("fatto pulizia\n");

	// Metto il mostro nella sua nuova posizione
	stanza->setSpot(m->getPosY(), m->getPosX(), 1);
	d->posizionaMostro(stanza, m);
}

void Controller::init()
{
    initscr();
	raw();
	noecho();
	refresh();
	start_color();
	d->disegna(p, gestore.getInizio(), stanza);
}

void Controller::gioca(){

	while (p->getExp()>=p->getNextExp())
		aumentaLivello();
	d->disegnaStat(p);
	char c=tolower(getch());
	gestisciInput(c);
	usleep(30000);
}
