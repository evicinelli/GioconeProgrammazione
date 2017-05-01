#include "GeneratoreLivelli.hpp"

   void GeneratoreLivelli::riempiVettStanze(Livello* l){
        int i;
        Stanza* s;
        for(i=0; i<l->getNStanze()+2; i++){

             if(i==l->getNStanze()||i==l->getNStanze()+1){
                /** NOTA: PER COMODITA' I COLLEGAMENTI AI LIVELLI
                PRECEDENTI E SUCCESSIVI SONO STATI MESSI A -1 CIOE'
                LE STANZE DEI LIVELLI PREC E SUCC HANNO COME NUMERO INTERNO -1
                */
                s= new Stanza(-1);
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
   		/*
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
   				- maxlink--
   		*/
   		
   }

   void GeneratoreLivelli::popolaLivello (Livello* l){

   	 	printf("Livello su indirizzo: %p\n", l);

        int stanze = l->getNStanze();
        float hard = .3;
        int maxLink = stanze + (int)(hard * stanze);

        printf("\t mLink: %d\n", maxLink );

        riempiVettStanze(l);
        riempiVettCollegamenti(l, maxLink);

   }
