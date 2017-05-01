#include "GeneratoreLivelli.hpp"

	void GeneratoreLivelli:: inizializzaVettColl(Livello* l){
            l->inizializzaColl();

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
   		//link(p, a, l);
   		avail[a] = false;
   		printf("%d -> %d\n",p, a);
   		p = a;
   	}

   	for (int i = 0; i < stanze; ++i){ avail[i] = true; }
   	avail[p] = false;
	printf("---\n");

   	for (int i = 0; i < maxLink - stanze + 1; ++i)	{
   		do {
   			a = rand() % stanze;
   		} while (avail[a] == false);

   		// collego le stanze
   		//link(p, a, l);
   		printf("%d -> %d\n",p, a);
   		avail[a] = false;
   		p = a;
   	}
   }

   void GeneratoreLivelli::link(int da, int a, Livello* l){
   		srand(time(NULL));
   		int stanze = l -> getNStanze() - 1;

   		// direzione di arrivo da -> a
   		int dA = rand() % 4;

   		// direzione di partenza a -> da
   		int dP = rand() % 4;

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
        cout<<"dA (direzione arrivo)   "<<dA<<endl;
        cout<<"dP (direzione partenza) "<<dP<<endl;
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

	printf("Livello su indirizzo: %p\n", l);
        inizializzaVettColl(l);

        int stanze = l->getNStanze();
        float hard = .3;
        int maxLink = stanze + (int)(hard * stanze);

        printf("mLink: %d \t stanze: %d \n", maxLink, stanze );

        riempiVettStanze(l);
        riempiVettCollegamenti(l, maxLink);

   }



