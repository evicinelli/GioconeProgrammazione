#include "GeneratoreLivelli.hpp"
GeneratoreLivelli::GeneratoreLivelli(){
	srand(time(0));
}



void GeneratoreLivelli:: inizializzaVettColl(Livello* l){
	int i;
	Collegamento* c;
	for(i=0; i<l->getNStanze(); i++){
		c= new Collegamento(i);
		l->setCollegamento(i,c);
	}

}


void GeneratoreLivelli::riempiVettStanze(Livello* l){
	int i;
	Stanza* s;
	for(i=0; i<l->getNStanze()+2; i++){

		if(i==l->getNStanze()||i==l->getNStanze()+1){
			/** NOTA: PER COMODITA' I COLLEGAMENTI AI LIVELLI PRECEDENTI E SUCCESSIVI SONO STATI MESSI A -1 CIOE' LE STANZE DEI LIVELLI PREC E SUCC HANNO COME NUMERO INTERNO -1
			*/
			s= new Stanza(-2);
			l->setStanza(i,s);
				//cout<< i << ":"<<(l->getStanza(i)).getS()<<endl;
		}
		else{
			s= new Stanza(i);
			l->setStanza(i,s);
				//cout<<i<<":"<<(l->getStanza(i)).getS()<<endl;
		}
	}
}

void GeneratoreLivelli::riempiVettCollegamenti(Livello* l, int maxLink){

	srand(time(NULL));
	int p = 0;
	int a = 0;
	int stanze = l->getNStanze();
	bool avail[stanze];

	// Preparo vettore delle disponibilit
	for (int i = 0; i < stanze; ++i){ avail[i] = true; }
		avail[p] = false;

	// Primo giro dei collegamenti
	for (int i = 0; i < stanze - 1; ++i) {
		// Scelgo la stanza 
		do {
			a = rand() % stanze;
		} while (avail[a] == false);

		// Collego le stanze
		link(p, a, l);
		avail[a] = false;
		p = a;
	}

	// Abbiamo collegato tra loro tutte le stanze. Si 
	// rigenera il vettore delle disponibilità e poi...
	for (int i = 0; i < stanze; ++i){ avail[i] = true; }
		avail[p] = false;
	printf("\t---\n");

	// Si collegano un'altra volta le stanze per garantire
	// dei doppi collegamenti
	for (int i = 0; i < maxLink - stanze + 1; ++i) {
		// Scelgo la stanza a cui arrivare
		do {
			a = rand() % stanze;
		} while (avail[a] == false);

		// Collego le stanze
		link(p, a, l);
		avail[a] = false;
		p = a;
	}
}


void GeneratoreLivelli::link(int da, int a, Livello* l){

	   /**
			NOTA: IL CONTROLLO SU STANZA DI PARTENZA E STANZA FINALE VA BENE BISOGNA AGGIUNGERE IL FATTO CHE SE
			COLLEGAMENTO NELLA DIREZIONE SCELTA E' PARI A -1 POSSO COLLEGARE ALTRIMENTI DEVO SCEGLIERE SCEGLIERE
			UN'ALTRA DIREZIONE CON IL RANDOM
	   */
	int stanze = l -> getNStanze() - 1;
	int tmpDirDa[4];
	int tmpDirA[4];
	int dA = rand() % 4;
	int dP = rand() % 4;

	// Mi prendo le adiacenze della stanza da e a per i controlli
	l->getAdiacenze(da, tmpDirDa);
	l->getAdiacenze(a, tmpDirA);

	// Ci si può collegare solamente se non ci si è già collegati a quella stanza nella stessa direzione. Se questo succede, bisogna ricalcolare la direzione alla quale attaccarsi
	if(tmpDirDa[dP] != -1 || tmpDirA[dA] != -1){
		while(tmpDirDa[dP] != -1 || tmpDirA[dA] != -1){
			dA = rand() % 4;
			dP = rand() % 4;
		}
	}

	/** controlliamo nessuna direzione proibita nel collegamento da/a la prima e l'ultima stanza*/
	// se in da c'è l'ultima stanza e in dA c'è la direzione NORD (0) allora viene ricalcolato il random
	if(da == stanze&& dA==0){
		while(dA==0){
			dA = rand() % 4;
		}
	}
	
	//se in a c'è l'ultima stanza e in dP c'è la direzione NORD (0) allora viene ricalcolato il random
	if(a == stanze&& dP==0){
		while(dP==0){
			dP = rand() % 4;
		}
	}
	
	//se in da c'è la prima stanza e in dA c'è la direzione SUD (1) allora viene ricalcolato il random
	if(da == 0&& dA==1){
		while(dA==1){
			dA = rand() % 4;
		}
	}

	//se in a c'è la prima stanza e in dP c'è la direzione SUD (1)allora viene ricalcolato il random
	if(a == 0&& dP==1){
		while(dP==1){
			dP = rand() % 4;
		}
	}
	printf("\t%d:%d -> %d:%d\n",da, dP, a, dA );
	l->collegaStanza(da,a,dA);
	l->collegaStanza(a,da,dP);

}

void GeneratoreLivelli::stampaCollegamenti(Livello* l){
	int a[4]={0,0,0,0};
	cout<<endl;
	for (int i=0; i<l->getNStanze();i++){
		l->getAdiacenze(i,a);
		cout<<i<<":";
		for (int j=0; j<4; j++){
			cout<<"\t"<<a[j]<<" ";
		}
		cout<<endl;
	}

}

void GeneratoreLivelli::popolaLivello (Livello* l){

	int maxLink = 0;
	inizializzaVettColl(l);

	int stanze = l->getNStanze();
	if (stanze != 1) {
		float hard = .3;
		maxLink = stanze + (int)(hard * stanze);
	}
	printf("\tmLink: %d \t stanze: %d \n", maxLink, stanze );

	riempiVettStanze(l);
	riempiVettCollegamenti(l, maxLink);

}



