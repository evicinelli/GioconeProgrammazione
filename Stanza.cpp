#include "Stanza.hpp"

Stanza::Stanza (){
    srand(time(0));
    inizializzaMatrice(this->matrice);
    this->nMaxMostri=0;
    this->nMaxBauli=0;
    this->nMaxVenditori=0;
    this->nMaxMuri=0;
    stampaMatriceInizializzata(matrice);
}


void Stanza:: inizializzaMatrice(int m[18][18]){

    for(int i=0; i<18; i++){
        for (int j=0; j<18; j++){
            m[i][j]=-1;
        }

    }
}

void Stanza:: stampaMatriceInizializzata(int m[18][18]){

     cout<<"    ";
    for(int i=0; i<18; i++){

        if(i<11){
            cout<<i<<"   ";
        }
        else{
            cout<<i<<"  ";
        }
    }
    cout<<endl;

    for(int i=0; i<18; i++){

        for (int j=0; j<18; j++){
            if(j==0){
                if(i<10){
                    cout<<i<<"   ";
                }
                else{
                    cout<<i<<"  ";
                }
            }
            cout<<m[i][j]<<"  ";
        }
        cout<<endl;

    }

}

void Stanza:: stampaMatrice(int m[18][18]){
    for(int i=0; i<18; i++){
        for (int j=0; j<18; j++){
            if(m[i][j]==-1){
                cout<<m[i][j]<<"  ";
            }
            else{
                cout<<m[i][j]<<"   ";
            }

        }
        cout<<endl;
    }

}



void Stanza::getMatrice(int m[18][18]){
    for(int i=0; i<18; i++){
        for (int j=0; j<18; j++){
            m[i][j]=matrice[i][j];
        }

    }
}


void Stanza::setMatrice(int m[18][18]){
    for(int i=0; i<18; i++){
        for (int j=0; j<18; j++){
            matrice[i][j]=m[i][j];
        }

    }
}

void Stanza::riempiMatrice(int nLiv, int coll [4]){
    /**
        0 -> muro : i muri non possono essere messi sulle porte e non possono essere lunghi quanto un lato della stanza perchè deve essere
                    possibile passare da una parte all'altra della stanza
        1 -> mostro : in base al numero max di mostri della stanza
        2 -> venditore : raro
        3 -> baule : raro
        4 -> porta : le posizioni delle porte (numero di porte è in base al numero di collegamenti) vengono scelte in base al lato dove sono
                     presenti i collegamenti, in qualsiasi riquadro del lato corrispondente
    */

    int p= (18*18)-200; //Sono da riempire 124 buchi al massimo
    int nPorte=0;

    for(int i=0; i<4; i++){
        if(coll[i]!=-1){
            nPorte++;
        }
    }

    p=p-nPorte;

    /**
        Dobbiamo settare la probabilità della presenza di muri, mostri, venditori e bauli.
        Quindi dobbiamo settare:
            nMaxMostri;
            nMaxBauli;
            nMaxVenditori;
            nMaxMuri;

        NOTA: ricordiamo che su ogni riga ci deve essere almeno un quadrato libero e i muri vanno messi come minimo in una riga si e una no
        così da assicurare almeno un percorso

        (matrice [nRiga][nColonna])
    */
    int avanti=false;

    do{
        this->nMaxMostri=rand()%7;

        if(p-nMaxMostri>=0){
            avanti=true;
        }

    }while(!avanti);

    p=p-nMaxMostri;

    if(p>0){
        avanti=false;
        do{
            this->nMaxBauli=(rand()%3);

            if(p-nMaxBauli>=0){
                avanti=true;
            }

        }while(!avanti);

        p=p-nMaxBauli;
    }

    int percVend=rand()%100;
    if(p>0&&percVend<=5){
        nMaxVenditori=1;
        p=p-nMaxVenditori;
    }

    //i muri occuperanno il 90% delle posizioni ancora libere --> 90 : 100 = x : p

    nMaxMuri= (90*p)/100;

    p=p-nMaxMuri;

    cout<<"porte: "<<nPorte<<endl;
    cout<<"mostri: "<<nMaxMostri<<endl;
    cout<<"bauli: "<<nMaxBauli<<endl;
    cout<<"venditori: "<<nMaxVenditori<<endl;
    cout<<"muri: "<<nMaxMuri<<endl;
    cout<<"p: "<<p<<endl;

    //SCELTA DELLE PORTE
    int pos;

    if(coll[0]!=-1){
        //scegli posizione della porta a nord cioè sulla riga 0 e la colonna variabile (non scegliamo gli angoli no colonna 0 e 17)
        do{
            pos= rand()%18;
        }while((pos!=0&&pos!=17)&& matrice [0][pos]==-1);

        matrice [0][pos]=4;

    }

    if(coll[1]!=-1){
        //scegli posizione della porta a sud cioè sulla riga 17 e la colonna variabile (non scegliamo gli angoli no colonna 0 e 17)
        do{
            pos= rand()%18;
        }while((pos!=0&&pos!=17)&& matrice [17][pos]==-1);

        matrice [17][pos]=4;

    }

    if(coll[2]!=-1){
        //scegli posizione della porta a ovest cioè sulla colonna 0 e la riga variabile (non scegliamo gli angoli no riga 0 e 17)
        do{
            pos= rand()%18;
        }while((pos!=0&&pos!=17)&& matrice [pos][0]==-1);

        matrice [pos][0]=4;

    }

    if(coll[3]!=-1){
        //scegli posizione della porta a est cioè sulla colonna 17 e la riga variabile (non scegliamo gli angoli no riga 0 e 17)
        do{
            pos= rand()%18;
        }while((pos!=0&&pos!=17)&& matrice [pos][17]==-1);

        matrice [pos][17]=4;

    }
/**
    //SCELTA DEI MURI

    int riga;
    int colonna;

    for(int i=0; i<nMaxMuri; i++){
        do{
            riga=rand()%18;
            colonna=rand()%18;

        }while(contrCorrettezzaMuri(riga, colonna));

        matrice[riga][colonna]=0;
    }

    //SCELTA MOSTRI

    for(int i=0; i<nMaxMostri; i++){
        do{
            riga=rand()%18;
            colonna=rand()%18;

        }while(matrice[riga][colonna]==-1);
        matrice[riga][colonna]=1;
    }

    //SCELTA BAULE

    for(int i=0; i<nMaxBauli; i++){
        do{
            riga=rand()%18;
            colonna=rand()%18;

        }while(matrice[riga][colonna]==-1);

        matrice[riga][colonna]=3;
    }

    //SCELTA VENDITORE

    for(int i=0; i<nMaxVenditori; i++){
        do{
            riga=rand()%18;
            colonna=rand()%18;

        }while(matrice[riga][colonna]==-1);

        matrice[riga][colonna]=2;
    }

*/

}

bool Stanza::contrCorrettezzaMuri(int r, int c){
    /**
        CONTROLLO MURI:
        -controllare che la posizioni scelta sia a -1 cioè libera
        -controllare che nella riga scelta ci sia almeno un passaggio libero
        -controllare che nelle righe sopra e sotto quella scelta non ci siano muri (perchè i muri vanno fatti una riga si e una no)
        -controllare che nelle posizioni di fianco (sulla stessa riga ma sulle colonne a dx o a sx) non ci siano le porte
    */

    if(matrice[r][c]==-1){
        bool ris=true;

        //controllare che nella riga scelta ci sia almeno un passaggio libero
        int nLib=0;
        for(int i=0; i<18; i++){
            if(matrice[i][c]==-1){
                nLib=nLib+1;
            }
        }
        if(nLib==0){
            ris=false;
        }

        //-controllare che nelle righe di fianco non ci siano muri (perchè i muri vanno fatti una riga si e una no)
        if(r!=0){
            for(int i=0; i<18; i++){
                if(matrice[r-1][i]==0){
                    ris=false;
                }
            }
        }

        if(r!=17){
            for(int i=0; i<18; i++){
                if(matrice[r+1][i]==0){
                    ris=false;
                }
            }
        }

        //controllare che nelle posizioni di fianco (sulla stessa riga ma sulle colonne a dx o a sx) non ci siano le porte
        if(c!=0){
            if(matrice[r][c-1]==4){
                ris=false;
            }
        }

        if(c!=17){
            if(matrice[r][c+1]==4){
                ris=false;
            }
        }

        return ris;

    }
    else{
        return false;
    }

}
