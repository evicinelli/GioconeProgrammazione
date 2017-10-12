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

void Controller::endGame(int v){
	ended=true;
	int c=' ';
	if (v==0)
	{
		d->quitDefeat();
	}
	if (v==1)
	{
		d->quitVictory();
	}

	while(c!=(char)'x' && c!=27)
	{
		c=tolower(getch());
	}
	endwin();

}

int Controller::selClasse()
{
	char c;
	int sel=2;
	d->disegnaInizio(sel);

	do{
		c=tolower(getch());
		if (c==(char)KEY_UP && sel>2){
			sel--;
			d->disegnaInizio(sel);
		}
		else if (c==(char)KEY_DOWN && sel<MAX_CLASSES+1){
			sel++;
			d->disegnaInizio(sel);
		}
	}while(c!=(char)10);

	flushinp();
	return sel-2;
}

void Controller::animaAttacchi(Mostro* m, bool isPlayer){
		if (isPlayer){
			d->posizionaMostro(stanza, m, false, true);
			usleep(250000);
			d->posizionaMostro(stanza, m, false, false);
		}
		else{
			d->posizionaGiocatore(stanza, p, true);
			usleep(250000);
			d->posizionaGiocatore(stanza, p, false);
		}
}

void Controller::vaiSu(){
	d->liberaPosizione(stanza, p->getPosY(), p->getPosX());
	p->setPosY(p->getPosY()-1);
	d->posizionaGiocatore(stanza, p, false);
	d->disegnaStat(p);
}
void Controller::vaiGiu(){
	d->liberaPosizione(stanza, p->getPosY(), p->getPosX());
	p->setPosY(p->getPosY()+1);
	d->posizionaGiocatore(stanza, p, false);
	d->disegnaStat(p);

}
void Controller::vaiDx(){
	d->liberaPosizione(stanza, p->getPosY(), p->getPosX());
	p->setPosX(p->getPosX()+1);
	d->posizionaGiocatore(stanza, p, false);
	d->disegnaStat(p);

}
void Controller::vaiSx(){
	d->liberaPosizione(stanza, p->getPosY(), p->getPosX());
	p->setPosX(p->getPosX()-1);
	d->posizionaGiocatore(stanza, p, false);
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
	d->disegnaLiv(l);
	d->posizionaGiocatore(stanza, p, false);
}

void Controller::apriBaule(int dir){
	int y, x; //coordinate baule
	x=p->getPosX();
	y=p->getPosY();

	Forziere* b =  new Forziere(gestore.getLivello());
	//viene messo nell'inventario l'oggetto
	p->setInv(p->libInventario(), b->getInterno());
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
	d->posizionaGiocatore(stanza, p, false);

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
	d->posizionaGiocatore(stanza, p, false);
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
	d->posizionaGiocatore(stanza, p, false);

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
	sprintf (msg[nStringhe+1], "esci");
	nStringhe++;
	sel=selPopUp(msg, sel, nStringhe);

	//ESCI è selezionato se sel=MAX_ITEM+2
	//imposta sel in modo che sia esattamente l'elemento in inventario
	for (int i=0; i<sel-1 && i<MAX_ITEM; i++){
		if (!p->getInv(i).isAvailable())
			sel++;
	}
	//a seconda di opt cambio o scarto l'arma
	if (sel >= 2 && sel < 2+MAX_ITEM){
		if (opt)
		{
			int res=p->cambioArma(sel-2);
			char mes[100],buf[20];
			switch (res)
			{
				case 0:
					printMsg ("Arma cambiata");
				break;
				case 1:
					strcpy(mes,"Forza insufficiente, richiesta ");
					sprintf(buf,"%d",p->getInv(sel-2).getStrMin());
					strcat(mes,buf);
					d->disegnaMess(mes);
				break;
				case 2:
					strcpy(mes,"Destrezza insufficiente, richiesta ");
					sprintf(buf,"%d",p->getInv(sel-2).getDexMin());
					strcat(mes,buf);
					d->disegnaMess(mes);
				break;
			}

		}
		else p->scartaArma(sel-2);
	}
	//disegno sopra la pop-up
	d->disegnaStanza(stanza);
	d->posizionaGiocatore(stanza, p, false);
	d->disegnaEquip(p);
}
void Controller::vendiVenditore(Venditore* v){
	char msg[20][40], costo[15];
	int sel=2, nStringhe=1;
	bool havePot;
	sprintf (msg[0], "VENDITORE");
	sprintf (msg[1], "Cosa vuoi vendere? (Invio)");
	//conta quante stringhe ci sono
	for (int i=0; i<MAX_ITEM; i++){
		if ( p->getInv(i).isAvailable()){
			sprintf (msg[nStringhe+1], p->getInv(i).getNome().c_str());
			sprintf (costo, "\t\t%d oro",  p->getInv(i).getPrezzo());
			strcat (msg[nStringhe+1], costo);
			nStringhe++;
		}
	}
	havePot=(p->getPot()>0);
	if (havePot){
		sprintf (msg[nStringhe+1], "pozione");
		sprintf (costo, "\t\t%d oro", v->getCostoPot());
		strcat (msg[nStringhe+1], costo);
		nStringhe++;
	}
	sprintf (msg[nStringhe+1], "compra"); nStringhe++;
	sprintf (msg[nStringhe+1], "esci"); nStringhe++;
	sel=selPopUp(msg, sel, nStringhe);
	//imposta sel in modo che sia esattamente l'elemento in inventario
	for (int i=0; i<sel-1 && i<MAX_ITEM; i++){
		if (!p->getInv(i).isAvailable())
			sel++;
	}
	sel-=2;

	//se puoi vendi oggetto
	if (sel >= 0 && sel<=MAX_ITEM){
		if (sel!=MAX_ITEM){
			p->vendiArma(sel);
			printMsg("Arma venduta");
		}
		else if (havePot){
			p->vendiPot(v->getCostoPot());
			printMsg("Pozione venduta");
		}
	}
	d->disegnaStat(p);
	d->disegnaEquip(p);
	if (sel==(MAX_ITEM+2-!havePot)){ //esci
		//disegno sopra la pop-up
		d->disegnaStanza(stanza);
		d->posizionaGiocatore(stanza, p, false);
	}
	else compraDaVend(v);
	
}
void Controller::compraDaVend(Venditore* v){
	char msg[20][40], costo[15];
	int sel=2, nStringhe=1;
	sprintf (msg[0], "VENDITORE");
	sprintf (msg[1], "Cosa vuoi comprare? (Invio)");
	//conta quante stringhe ci sono
	for (int i=0; i<MAX_ITEM; i++){
		if (v->getVendita(i).isAvailable()){
			sprintf (msg[nStringhe+1], v->getVendita(i).getNome().c_str());
			sprintf (costo, "\t\t%d oro", v->getVendita(i).getPrezzo());
			strcat (msg[nStringhe+1], costo);
			nStringhe++;
		}
	}
	if (v->getPozioni()){
		sprintf (msg[nStringhe+1], "pozione");
		sprintf (costo, "\t\t%d oro", v->getCostoPot());
		strcat (msg[nStringhe+1], costo);
		nStringhe++;
	}
	sprintf (msg[nStringhe+1], "vendi"); nStringhe++;
	sprintf (msg[nStringhe+1], "esci"); nStringhe++;
	sel=selPopUp(msg, sel, nStringhe);
	//imposta sel in modo che sia esattamente l'elemento in inventario
	for (int i=0; i<sel-1 && i<3; i++){
		if (!v->getVendita(i).isAvailable())
			sel++;
	}
	sel-=2;

	//se puoi compra oggetto
	if (sel >= 0 && sel<=3){
		if (sel!=3){
				if (p->getOro() >= v->getVendita(sel).getPrezzo()){
					int pos=v->vendi(p, sel);
					if (pos==-1)
						printMsg("Hai l'inventario pieno");
				}
				else
					printMsg("Non hai abbastanza oro");

		}
		else if (v->getPozioni()){
			if(p->getOro() >= v->getCostoPot())
				v->vendi(p, sel);
			else
				printMsg("Non hai abbastanza oro");
		}
	}
	if (sel == (3+v->getPozioni())){
		vendiVenditore(v);
	}
	//se non ha più niente sparisce
	bool isVuoto=true;
	for (int i=0; i<3; i++){
		if (v->getVendita(i).isAvailable())
			isVuoto=false;
	}
	isVuoto=(isVuoto && !v->getPozioni());
	if (isVuoto)
		stanza->setSpot(v->getPosY(), v->getPosX(), -1);
	//disegno sopra la pop-up
	d->disegnaStanza(stanza);
	d->disegnaStat(p);
	d->posizionaGiocatore(stanza, p, false);
	d->disegnaEquip(p);

}
void Controller::aumentaLivello(){
	char msg[20][40];
	int sel=2;
	sprintf (msg[0], "LIVELLO %d:", p->getLev()+1);
	sprintf (msg[1], "Cosa vuoi migliorare? (Invio)");
	sprintf (msg[2], "Forza");
	sprintf (msg[3], "Destrezza");
	sprintf (msg[4], "Costituzione");
	sprintf (msg[5], "Fortuna");
	sel=selPopUp(msg, sel, 5);

	p->levelup(sel-1);
	//disegno sopra la pop-up
	d->disegnaStanza(stanza);
	d->posizionaGiocatore(stanza, p, false);
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
	d->posizionaGiocatore(stanza, p, false);
	return (sel==2);

}

void Controller::gestisciInput(char c){

    int dir; //direzione nella quale sono gli oggetti
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
			if (isVicino(2, dir)){
				int x, y;
				x=p->getPosX();
				y=p->getPosY();
				if (dir==0) y--;
				else if (dir==1) y++;
				else if (dir==2) x--;
				else if (dir==3) x++;
				Venditore* v = stanza->getVenditoreByPos(y, x);
				compraDaVend(v);
			}
			else{
				printMsg("Non sei vicino a un venditore");
			}
        break;
        //ATTACCARE MOSTRO      (K)
        case((char)('k')):
        	if (selected!=NULL && selected->isAlive())
			{
				int distX=abs(selected->getPosX()-p->getPosX());
				int distY=abs(selected->getPosY()-p->getPosY());
				if (distX<=1 && distY<=1 && !(distX==1 && distY==1))
				{
					if (p->getAct()>=4)
					{
						int danno=p->attacca(selected);
						if (selected->getHp()>0)
							scriviInfoAttacco(selected,danno,true);
						else
						{
							stanza->setSpot(selected->getPosY(), selected->getPosX(), -1);
							selected->morte(p);
							scriviMorteMostro(selected,danno);
							d->disegnaEquip(p);
						}
						animaAttacchi(selected, true);
						d->disegnaStat(p);
						d->disegnaStanza(stanza);
						d->posizionaGiocatore(stanza,p, false);
					}
					else
						printMsg("Non hai abbastanza punti azione (minimo 4)");
				}
			}
        break;
        //APRIRE BAULE          (O)
        case((char)('o')):
			if (isVicino(3, dir) && (p->libInventario()!=-1)){
				if(p->actApri())
				{
					apriBaule(dir);
					printMsg("Aperto baule");
				}
				else
					printMsg("Non hai abbastanza punti azione (minimo 2)");
			}
			else if (p->libInventario()==-1)
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
                d->disegnaStat(p);
                d->disegnaEquip(p);
        break;
        //CAMBIA ARMA           (L)
        case((char)('l')):
			if (thereisArma()){
				scegliArma(1);
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
			clear();
			refresh();
			d->disegna(p, gestore.getLevelById(gestore.getLivello()), stanza);
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
	d->posizionaMostro(stanza, m, isChasing, false);
}

void Controller::init()
{
   	initscr();
	raw();
	noecho();
	refresh();
	start_color();
	keypad(stdscr, true);
	p->classChosen(selClasse());
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
