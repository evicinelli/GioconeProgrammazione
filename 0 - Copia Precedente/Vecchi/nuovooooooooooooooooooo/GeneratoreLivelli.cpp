#include "GeneratoreLivelli.hpp"

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
                /** NOTA: PER COMODITA' I COLLEGAMENTI AI LIVELLI
                PRECEDENTI E SUCCESSIVI SONO STATI MESSI A -1 CIOE'
                LE STANZE DEI LIVELLI PREC E SUCC HANNO COME NUMERO INTERNO -1
                */
                s= new Stanza(-2);
                l->setStanza(i,s);
                cout<< i << ":"<<(l->getStanza(i)).getS()<<endl;
             }
             else{
                s= new Stanza(i);
                l->setStanza(i,s);
                cout<<i<<":"<<(l->getStanza(i)).getS()<<endl;
             }
        }
   }

   void GeneratoreLivelli::riempiVettCollegamenti(Livello* l, int maxLink){
  	srand(time(NULL));

   	int p = 0;
   	int a = 0;
   	int stanze = l->getNStanze();
   	bool avail[stanze];
   	//int disp = stanze - 1;

   	for (int i = 0; i < stanze; ++i){ avail[i] = true; }
   	avail[p] = false;
   	int avanzate = 0;

   	for (int i = 0; i < stanze - 1; ++i)
   	{
   		do {
   			a = rand() % stanze;
   		} while (avail[a] == false);

   		// collego le stanze
   		link(p, a, l);
   		avail[a] = false;
   		printf("%d -> %d\n",p, a);
   		p = a;
   	}

   	for (int i = 0; i < stanze; ++i){ avail[i] = true; }
   	avail[p] = false;
   printf("---\n");

   	for (int i = 0; i < maxLink - stanze + 1; ++i)
   	{
   		do {
   			a = rand() % stanze;
   		} while (avail[a] == false);
   		printf("%d -> %d\n",p, a);


   		// collego le stanze
   		link(p, a, l);

   		avail[a] = false;
   		p = a;
   	}


  	for (int i = 0; i < stanze; ++i)
  	{
  		if (avail[i]) avanzate++;
  		printf("[%d]: %d\n",i, avail[i] );
  	}

   	printf("%d su %d\n", avanzate, (maxLink % stanze));
   }

   void GeneratoreLivelli::link(int da, int a, Livello* l){

       /**
            NOTA: IL CONTROLLO SU STANZA DI PARTENZA E STANZA FINALE VA BENE BISOGNA AGGIUNGERE IL FATTO CHE SE
            COLLEGAMENTO NELLA DIREZIONE SCELTA E' PARI A -1 POSSO COLLEGARE ALTRIMENTI DEVO SCEGLIERE SCEGLIERE
            UN'ALTRA DIREZIONE CON IL RANDOM
       */
   		srand(time(NULL));
   		int stanze = l -> getNStanze() - 1;

   		// direzione di arrivo da -> a
   		int dA = (rand() % 4);

   		//srand(time(NULL));
   		// direzione di partenza a -> da
   		int dP = (rand() % 4);

   		// controlliamo nessuna direzione proibita nel collegamento da/a la prima e l'ultima stanza
   		if (da == stanze && dP == 0 ) {
   			do {
   				dP = rand() % 4;
   			} while (dP == 0);
   		}

   		if (da == 0 && dP == 1) {
   			do {
   				dP = rand() % 4;
   			} while (dP == 1);
   		}

   		if (a == 0 && dA == 1)
   		{
   			do {
   				dA = rand() % 4;
   			} while (dA == 1);
   		}

   		if (a == stanze && dA == 0)
   		{
   			do {
   				dA = rand() % 4;
   			} while (dA == 0);
   		}
   		cout<<"s1: "<<da<<" s2: "<<a<<endl;
        cout<<"dA "<<dA<<endl;
        cout<<"dP "<<dP<<endl;
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
                cout<<a[j]<<" ";
            }
            cout<<endl;
       }

   }

   void GeneratoreLivelli::popolaLivello (Livello* l){

        inizializzaVettColl(l);

        int stanze = l->getNStanze();
        float hard = .3;
        int maxLink = stanze + (int)(hard * stanze);

        printf("mLink: %d \t stanze: %d \n", maxLink, stanze );

        riempiVettStanze(l);
        riempiVettCollegamenti(l, maxLink);

   }



