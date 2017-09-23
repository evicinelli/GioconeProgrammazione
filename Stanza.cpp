#include "Stanza.hpp"
#include "NoiseGenerator.hpp"
# define WALL_TRESHOLD 1.2

Stanza::Stanza (){
    srand(time(0));
    this->dimensione=18;
    inizializzaMatrice(this->matrice);
    this->nMaxMostri=6;
    this->nMaxBauli=2;
    this->nMaxVenditori=2;
    this->nMaxMuri=0;
    this->nPorte=0;
}

int buildWall(double p)
{
	if (p > WALL_TRESHOLD) return 0; else return -2;
}

void Stanza:: inizializzaMatrice(int m[18][18]){

    for(int i=0; i<dimensione; i++){
        for (int j=0; j<dimensione; j++){
            m[i][j]=-2;
        }

    }
}

void Stanza:: stampaMatrice(int m[18][18]){
    for(int i=0; i<dimensione; i++){
        for (int j=0; j<dimensione; j++){
			
			if (m[i][j]==4) cout<<"@ ";
			
			else if (m[i][j]==3) cout<<"B ";
			
			else if (m[i][j]==2) cout<<"V ";
			
			else if (m[i][j]==1) cout<<"M ";
			
			else if(m[i][j]==-3) cout<<". ";
			
            else if(m[i][j]==-2) cout<<"# ";
            
            else if(m[i][j]==-1) cout<<". ";
            
			else if (m[i][j]==0) cout<<"# ";
            
            else cout<<m[i][j]<<"   ";

        }
        cout<<endl;
    }

}



void Stanza::getMatrice(int m[18][18]){
    for(int i=0; i<dimensione; i++){
        for (int j=0; j<dimensione; j++){
            m[i][j]=matrice[i][j];
        }

    }
}


void Stanza::setMatrice(int m[18][18]){
    for(int i=0; i<dimensione; i++){
        for (int j=0; j<dimensione; j++){
            matrice[i][j]=m[i][j];
        }

    }
}

void Stanza::mettiMuriContorno(){
	for (int i=0; i<dimensione; i++){
		matrice[i][0]=0;
		matrice[i][dimensione-1]=0;
		matrice[0][i]=0;
		matrice[dimensione-1][i]=0;
	}
}

void Stanza::mettiPorte(int coll[4]){
	// Ci penserà la Giulia, momentaneamente sono random
	nPorte=rand()%4+1;
	
	for (int i=0; i<nPorte; i++)
		porte[i]=rand()%(dimensione-2)+1;
		
	matrice[porte[0]][0]=4;
	if (nPorte>1) matrice[0][porte[1]]=4;
	if (nPorte>2) matrice[porte[2]][dimensione-1]=4;
	if (nPorte>3) matrice[dimensione-1][porte[3]]=4;
	
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
	if (!type){
		posx=1;
		posy=partenza;
		arrivox=dimensione-2;
		arrivoy=arrivo;
	}else{
		posx=partenza;
		posy=1;
		arrivox=arrivo;
		arrivoy=dimensione-2;
	}
	matrice[posy][posx]=-3;
	while (((posx != dimensione-2) && !type) || ((posy != dimensione-2) && type)){
		do{
			direzione=rand()%4+1;
		}while((prec-direzione)==2 || (prec-direzione)==-2  || (direzione-type)==3);
		if (direzione==1 && posx<dimensione-2){
			prec=direzione;
			posx++;
		}else if (direzione==2 && posy<dimensione-2){
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
		matrice[i][dimensione-2]=-3;

	for (int i=posx;i<arrivox;i++)
		matrice[dimensione-2][i]=-3;
		
}
//Sono necessarie 4 porte e porta 0 deve essere opposta a porta 2 (quindi anche per 1 e 3)
void Stanza::inserisciVia(){
	int partenza[2], arrivo[2];
	for (int i=0; i<2; i++){
		if (existPorta(i)) partenza[i]=getPorta(i);
		else partenza[i]=rand()%(dimensione-2)+1;
		
		if (existPorta(i+2)) arrivo[i]=getPorta(i+2);
		else arrivo[i]=rand()%(dimensione-2)+1;
		link(partenza[i], arrivo[i], i);
	}
}

void Stanza::mettiMuri(){
	//lo farà Vicci, momentaneamente random
	int seed = rand() % 100000;
	for (int i=1; i<(dimensione-1); i++){
		for (int j=1; j<(dimensione-1); j++){
			if (matrice[i][j]==-2){
				int r = buildWall(descreteNoise(i, j, (dimensione - 1), 0));
				if (r==0) matrice[i][j]=0;
			}
		}
	}
}

void Stanza::riempiMuri(int x, int y){
		if (matrice[y][x]==-2 || matrice[y][x]==-3){
			matrice[y][x]=-1;
			riempiMuri(x+1,y);
			riempiMuri(x-1,y);
			riempiMuri(x,y+1);
			riempiMuri(x,y-1);	
		}
}

int log(int n){
	if (n==1) return 0;
	return 1+log(n/2);
}

void Stanza::mettiMostri(int livello){
	
	for(int i=0; i<(dimensione-1); i++){
		for(int j=0; j<(dimensione-1) && nMaxMostri>0; j++){
			if (matrice[i][j]==-1){
				int den=1000/(log(livello)+14);
				int r=rand()%den;
				if (r==0){
					matrice[i][j]=1;
					nMaxMostri--;
				}
			}
		}
	}
}
int Stanza::nVicini(int x, int y){
	int somma=0;
	somma+=(matrice[x+1][y]==0 || matrice[x+1][y]==1);
	somma+=(matrice[x-1][y]==0 || matrice[x-1][y]==1);
	somma+=(matrice[x][y+1]==0 || matrice[x][y+1]==1);
	somma+=(matrice[x][y-1]==0 || matrice[x][y-1]==1);
	return somma;
}

void Stanza::mettiBauli(int livello){
	
	for(int i=0; i<(dimensione-1); i++){
		for(int j=0; j<(dimensione-1) && nMaxBauli>0; j++){
			if (matrice[i][j]==-1){
				int den=2000/((livello/30.0)+1);
				if (nVicini(i,j)!=0) den=den/nVicini(i,j);
				int r=rand()%den;
				if (r==0){
					matrice[i][j]=3;
					nMaxBauli--;
				}
			}
		}
	}
	
}

void Stanza::mettiVenditori(int livello){
	
	for(int i=0; i<(dimensione-1); i++){
		for(int j=0; j<(dimensione-1) && nMaxVenditori>0; j++){
			if (matrice[i][j]==-1){
				int den=3000/((livello/20.0)+2);
				int r=rand()%den;
				if (r==0){
					matrice[i][j]=2;
					nMaxVenditori--;
				}
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
	riempiMuri(1,getPorta(0));
	mettiMostri(nLiv);
	mettiBauli(nLiv);
	mettiVenditori(nLiv);

}

