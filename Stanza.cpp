#include "Stanza.hpp"

Stanza::Stanza (){
    srand(time(0));
    inizializzaMatrice(this->matrice);
    this->nMaxMostri=0;
    this->nMaxBauli=0;
    this->nMaxVenditori=0;
    this->nMaxMuri=0;
    this->nPorte=0;
    //stampaMatrice(matrice);
}


void Stanza:: inizializzaMatrice(int m[18][18]){

    for(int i=0; i<18; i++){
        for (int j=0; j<18; j++){
            m[i][j]=-2;
        }

    }
}
/*
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

}*/

void Stanza:: stampaMatrice(int m[18][18]){
    for(int i=0; i<18; i++){
        for (int j=0; j<18; j++){
			if (m[i][j]==0) cout<<"# ";
			
			else if (m[i][j]==4) cout<<"@ ";
			
			else if(m[i][j]==-3) cout<<". ";
			
            else if(m[i][j]==-2) cout<<"  ";
            
            else cout<<m[i][j]<<"   ";

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

void Stanza::mettiMuriContorno(){
	for (int i=0; i<18; i++){
		matrice[i][0]=0;
		matrice[i][17]=0;
		matrice[0][i]=0;
		matrice[17][i]=0;
	}
}
void Stanza::mettiPorte(int coll[4]){
	// Ci penserà la Giulia, momentaneamente sono random
	nPorte=rand()%4+1;
	
	for (int i=0; i<nPorte; i++)
		porte[i]=rand()%15+1;
		
	matrice[porte[0]][0]=4;
	if (nPorte>1) matrice[0][porte[1]]=4;
	if (nPorte>2) matrice[porte[2]][17]=4;
	if (nPorte>3) matrice[17][porte[3]]=4;
	
}

bool Stanza::existPorta(int n){
	return n<nPorte;
}

int Stanza::getPorta(int n){
	return porte[n];
}

void Stanza::link(int partenza, int arrivo, int type){
	int prec, posx, posy, arrivox, arrivoy, direzione; //1 E, 2 S, 3 W, 4N 
	prec=7;//valore nullo 7-4=3>+-2
	if (type==0){
		posx=1;
		posy=partenza;
		arrivox=16;
		arrivoy=arrivo;
	}else{
		posx=partenza;
		posy=1;
		arrivox=arrivo;
		arrivoy=16;
	}
	matrice[posy][posx]=-3;
	while ((posx != 16 && type==0) || (posy != 16 && type==1)){
		do{
			direzione=rand()%4+1;
		}while((prec-direzione)==2 || (prec-direzione)==-2  || (direzione-type)==3);
		if (direzione==1 && posx<16){
			prec=direzione;
			posx++;
		}else if (direzione==2 && posy<16){
			prec=direzione;
			posy++;
		}else if (direzione==3 && posx>1){
			prec=direzione; 
			posx--;
		}else if (direzione==4 && posy>1){
			prec=direzione; 
			posy--;
		}
		matrice[posy][posx]=-3;
	}
	matrice[arrivoy][arrivox]=-3;
	if (arrivoy<posy){ //type=1 non entra
		int temp=arrivoy;
		arrivoy=posy;
		posy=temp;
	}
	if (arrivox<posx){ //type=0 non entra
		int temp=arrivox;
		arrivox=posx;
		posx=temp;
	}
	
	for (int i=posy;i<arrivoy;i++)
		matrice[i][16]=-3;

	for (int i=posx;i<arrivox;i++)
		matrice[16][i]=-3;
		
}
//Sono necessarie 4 porte e porta 0 deve essere opposta a porta 2 (quindi anche per 1 e 3)
void Stanza::inserisciVia(){
	int partenza[2], arrivo[2];
	for (int i=0; i<2; i++){
		if (existPorta(i)){partenza[i]=getPorta(i);}
		else{ partenza[i]=rand()%15+1;}
		
		if (existPorta(i+2)){ arrivo[i]=getPorta(i+2);}
		else{ arrivo[i]=rand()%15+1;}
		link(partenza[i], arrivo[i], i);
	}
}

void Stanza::mettiMuri(){
	//lo farà Vicci, momentaneamente random
	for (int i=1; i<17; i++){
		for (int j=1; j<17; j++){
			if (matrice[i][j]==-2){
				int r=rand()%3;
				if (r==0) matrice[i][j]=0;
			}
		}
	}
}

void Stanza::riempiMatrice(int nLiv, int coll [4]){
	 /**
		-3 -> strada
		-2 -> interno
		-1 -> esterno
        0 -> muro : i muri non possono essere messi sulle porte e non possono essere lunghi quanto un lato della stanza perchè deve essere
                    possibile passare da una parte all'altra della stanza
        1 -> mostro : in base al numero max di mostri della stanza
        2 -> venditore : raro
        3 -> baule : raro
        4 -> porta : le posizioni delle porte (numero di porte è in base al numero di collegamenti) vengono scelte in base al lato dove sono
                     presenti i collegamenti, in qualsiasi riquadro del lato corrispondente
    */
	mettiMuriContorno();
	mettiPorte(coll);
	inserisciVia();
	mettiMuri();
	/*riempiMuri();
	mettiMostri();
	mettiBauli();*/

}

void Stanza::riempiMatrice2(int nLiv, int coll [4]){
    /**
		-2 -> vuoto
		-1 -> strada
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
