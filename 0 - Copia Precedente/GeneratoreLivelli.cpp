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
   		/**
   			- Preparo il vettore delle stanze disponibili per il giro (bool:v[i] -> è disponibile la stanza i?)
   			- Ciclo sul vettore indice fino a maxlink
   				- Randomizzo una stanza di arrivo per il collegamento. Fino a che non ho successo:
   					- Controllo nel vettore indice se quella stanza può essere collegata questo giro
   					- Se può essere collegata, la collego
   						- Randomizzo una direzione di partenza e di arrivo fino a che non ho successo
   						- In stanza partenza, direzione scelta, scrivo id stanza arrivo
						- In stanza arrivo, direzione scelta, scrivo id stanza partenza
   					- Se non può essere collegata, trovo un'altra stanza
   					- Successo: true
   				- maxLink--


   				NOTA: CASI IN CUI STANZE SONO 0, 1, 2 VANNO TRATTATI APPOSTA! eccVirgolaMobile, ci, ci!!
   		*/

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
   		int stanze = l -> getNStanze() - 1;

   		// direzione di arrivo da -> a
   		int dA = rand() % 4;

   		// direzione di partenza a -> da
   		int dP = rand() % 4;


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

   		/** controlliamo che le direzioni siano libere (cioè a -1)*/



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



