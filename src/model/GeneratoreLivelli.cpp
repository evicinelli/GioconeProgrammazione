#include "GeneratoreLivelli.hpp"
GeneratoreLivelli::GeneratoreLivelli(){
    srand(time(0));
}

void GeneratoreLivelli:: inizializzaVettColl(Livello* l){
    // variabile per scorrere collegamenti
    int i;
    //collegamento appoggio
    Collegamento* c;
    //scorriamo collegamenti
    for(i=0; i<l->getNStanze(); i++){
        //inizializziamo a -1 tutto
        c= new Collegamento(i);
        //settiamo id del collegamento
        l->setCollegamento(i,c);

    }
}

void GeneratoreLivelli::riempiVettStanze(Livello* l){
    //scorro le stanze del livello creando le mappe
    for(int i=0; i<l->getNStanze(); i++){
        l->setMatriceStanza(i);
    }
}

void GeneratoreLivelli::controllaAvail(bool avail[4],Livello* l){
    int a[4];
    int neg;
    //scorro i
    for(int i=0; i<l->getNStanze(); i++){
        neg=0;
        l->getAdiacenze(i,a);
        //conto quante direzioni sono occupate
        for(int j=0; j<4; j++){
            if(a[j]!=-1){
                neg++;
            }
        }

        //se le direzioni occupate sono 4 => setto a false
        if(neg==4){
            avail[i]=false;
        }
        //se le direzioni occupate sono 3 e si tratta o della prima o dell'ultima stanza => setto a false
        else if(neg==3&&(i==0||i==l->getNStanze()-1)){
            avail[i]=false;
        }
        //altrimenti setto a true;
        else{
            avail[i]=true;
        }
    }
}

void GeneratoreLivelli::controllaAvail2(bool avail[4],Livello* l){
    int a[4];
    int neg;

    //scorro le stanze
    for(int i=0; i<l->getNStanze(); i++){
        //se la stanza non è già settata a false faccio il controllo
        if(avail[i]!=false){
            neg=0;
            l->getAdiacenze(i,a);

            //conto quante direzioni sono occupate
            for(int j=0; j<4; j++){
                if(a[j]!=-1){
                    neg++;
                }
            }

            //se le direzioni occupate sono 4 => setto a false
            if(neg==4){
                avail[i]=false;
            }
            //se le direzioni occupate sono 3 e si tratta o della prima o dell'ultima stanza => setto a false
            else if(neg==3&&(i==0||i==l->getNStanze()-1)){
                avail[i]=false;
            }
        }
    }
}

void GeneratoreLivelli::riempiVettCollegamenti(Livello* l, int maxLink){

    int p = 0;
    int a = 0;
    int stanze = l->getNStanze();
    bool avail[stanze];

    /**PRIMA PARTE*/
    // Preparo vettore delle disponibilità
    for (int i = 0; i < stanze; ++i){
        avail[i] = true;
    }
    avail[p] = false;

    // Primo giro dei collegamenti
    for (int i = 0; i < stanze - 1; ++i){
        // Scelgo la stanza
        do{
            a = rand() % stanze;
        }
        while (avail[a] == false);

        // Collego le stanze
        link(p, a, l);
        avail[a] = false;
        p = a;
    }


    /**SECONDA PARTE*/
    //controlla adiacenze delle stanze e toglie le stanze piene per evitare di collegarle
    controllaAvail(avail,l);

    // Si collegano un'altra volta le stanze per garantire
    // dei doppi collegamenti
    for (int i = 0; i < maxLink - stanze + 1; ++i){
        p = rand() % stanze; //inizializziamo p
        a = rand() % stanze; //inizializziamo a

        // Scelgo la stanza a cui arrivare in modo che sia accessibile
        while (avail[a] == false){
            a = rand() % stanze;
        }

        // Scelgo la stanza da cui partire in modo che sia accessibile
        while (avail[p] == false){
            p = rand() % stanze;
        }

        // se le due stanze sono uguali cambio la stanza di partenza
        while (p==a){
            p = rand() % stanze;
        }

        // Collego le stanze
        link(p, a, l);

        //setto a false la stanza da cui sono arrivata per toglierla dalle stanze accessibili
        avail[a]=false;

        //controlla adiacenze delle stanze e toglie le stanze piene per evitare di collegarle
        controllaAvail2(avail,l);
    }
}


void GeneratoreLivelli::link(int da, int a, Livello* l){
    //prendo il numero di stanze da 0 a nStanze-1
    int stanze = l -> getNStanze() - 1;

    // direzione di arrivo da -> a
    int dA = rand() % 4;

    // direzione di partenza a -> da
    int dP = rand() % 4;

    //array di appoggio per le direzioni
    int dirDa[4];
    int dirA[4];

    // Mi prendo le adiacenze della stanza da e a per i controlli
    l->getAdiacenze(da, dirDa);
    l->getAdiacenze(a, dirA);

    /** Controlliamo nessuna direzione proibita nel collegamento da/a la prima e l'ultima stanza*/

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

    /** Controlliamo che la direzione scelta per le due stanze sia libera (cioè settata a -1) */

    //se la direzione è occupata dA => faccio controllo che ne restituisce una giusta
    if(dirDa[dA]!=-1){
        dA=controlloLink(da,dA,dirDa,stanze);
    }

    //se la direzione è occupata dP => faccio controllo che ne restituisce una giusta
    if(dirA[dP]!=-1){
        dP=controlloLink(a,dP,dirA,stanze);
    }

    //adesso che sono sicura che le direzioni siano libere collego le due stanze
    l->collegaStanza(da,a,dA);
    l->collegaStanza(a,da,dP);

}


int GeneratoreLivelli::controlloLink(int s,int direzione,int dir[4], int stanze){
    do{
        //cambio la direzione
        direzione = rand() % 4;

        //caso particolare dell'ultima stanza
        if(s == stanze&& direzione==0){
            while(direzione==0){
                direzione = rand() % 4;
            }
        }

        //caso particolare della prima stanza
        else if(s == 0&& direzione==1){
            while(direzione==1){
                direzione = rand() % 4;
            }
        }

    }
    while(dir[direzione]!=-1); //fino a quando la direzione non è libera

    return direzione;

}


void GeneratoreLivelli::stampaCollegamenti(Livello* l){
    int a[4]= {0,0,0,0};
    cout<<endl;
    Collegamento* vColl=new Collegamento[l->getNStanze()];
    vColl=l->getVettColl();
    for (int i=0; i<l->getNStanze(); i++){
        int id=vColl[i].getId();
        l->getAdiacenze(i,a);
        cout<<id<<":";
        for (int j=0; j<4; j++){
            cout<<"\t"<<a[j]<<" ";
        }
        cout<<endl;
    }

}

void GeneratoreLivelli::popolaLivello (Livello* l){

    int maxLink = 0;
    //inizializza i collegamenti
    inizializzaVettColl(l);

    //scelta del massimo dei collegamenti possibili
    int stanze = l->getNStanze();
    if (stanze != 1){
        float hard = .3;
        maxLink = stanze + (int)(hard * stanze);
    }

    //scelta dei collegamenti
    riempiVettCollegamenti(l, maxLink);
    //riempimento delle stanze
    riempiVettStanze(l);

}



void GeneratoreLivelli::collegaLivelloPrec(Livello* corrente, Livello* precedente){

    //all'indice nStanze del vettore delle stanze del livello corrente viene messa l'ultima stanza (quella all'indice nStanze-1) del livello precedente
    corrente->setStanza(corrente->getNStanze(),precedente->getPointerToStanza(precedente->getNStanze()-1));

    //all'indice nStanze+1 del vettore delle stanze del livello precedente viene messa la prima stanza (quella all'indice zero) del livello corrente
    precedente->setStanza(precedente->getNStanze()+1,corrente->getPointerToStanza(0));

    //la prima stanza del livello corrente viene collegata in direzione sud al livello precedente quindi: stanza partenza è la stanza zero e la stanza di
    //arrivo è quella all'indice nStanze (che è l'ultima stanza del livello precedente) e la direzione è 1
    corrente->collegaStanza(0,corrente->getNStanze(),1);

    //l'ultima stanza del livello successivo viene collegata al livello corrente in direzione nord quindi: stanza di partenza è l'ultima del livello precedente
    //e la stanza di arrivo è la prima del livello successivo (nel nostro caso si chiama corrente) la direzione è 0
    precedente->collegaStanza(precedente->getNStanze()-1, precedente->getNStanze()+1,0);

}



