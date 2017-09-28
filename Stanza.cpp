#include "Stanza.hpp"
#include "NoiseGenerator.hpp"
# define WALL_TRESHOLD 1.2

Stanza::Stanza ()
{
    srand(time(0));
    this->dimensione=0;
    this->nMaxMostri=6;
    this->nMaxBauli=2;
    this->nMaxVenditori=2;
    this->nMaxMuri=0;
    this->visited=false;
    for (int i=0; i<4; i++) 
		this->porte[i]=-1;
}

int Stanza::getDimensione(){
	return this->dimensione;
}
void Stanza::visit(){
	visited=true;
}
bool Stanza::isVisited(){
	return visited;
}
int buildWall(double p)
{
    if (p > WALL_TRESHOLD) return 0;
    else return -2;
}

void Stanza:: inizializzaMatrice(int m[MAXDIM][MAXDIM])
{

    for(int i=0; i<dimensione; i++)
    {
        for (int j=0; j<dimensione; j++)
        {
            m[i][j]=-2;
        }

    }
}

void Stanza:: stampaMatrice(int m[MAXDIM][MAXDIM])
{
    for(int i=0; i<dimensione; i++)
    {
        for (int j=0; j<dimensione; j++)
        {

            if (m[i][j]==4) cout<<"@ ";

            else if (m[i][j]==3) cout<<"B ";

            else if (m[i][j]==2) cout<<"V ";

            else if (m[i][j]==1) cout<<"M ";

            else if(m[i][j]==-3) cout<<". ";

            else if(m[i][j]==-2) cout<<"X ";

            else if(m[i][j]==-1) cout<<". ";

            else if (m[i][j]==0) cout<<"# ";

            else cout<<m[i][j]<<"   ";

        }
        cout<<endl;
    }

}



void Stanza::getMatrice(int m[MAXDIM][MAXDIM])
{
    for(int i=0; i<dimensione; i++)
    {
        for (int j=0; j<dimensione; j++)
        {
            m[i][j]=matrice[i][j];
        }

    }
}


void Stanza::setMatrice(int m[MAXDIM][MAXDIM])
{
    for(int i=0; i<dimensione; i++)
    {
        for (int j=0; j<dimensione; j++)
        {
            matrice[i][j]=m[i][j];
        }

    }
}

void Stanza::mettiMuriContorno()
{
    for (int i=0; i<dimensione; i++)
    {
        matrice[i][0]=0;
        matrice[i][dimensione-1]=0;
        matrice[0][i]=0;
        matrice[dimensione-1][i]=0;
    }
}

void Stanza::mettiPorte(int coll[4])
{
    // Ci penserà la Giulia, momentaneamente sono random
    for (int i=0; i<4; i++)
    {
        if (coll[i]!=-1)
            porte[i]=rand()%(dimensione-2)+1;
    }
    if (coll[0]!=-1) matrice[0][porte[0]]=4;
    if (coll[1]!=-1) matrice[dimensione-1][porte[1]]=4;
    if (coll[2]!=-1) matrice[porte[2]][0]=4;
    if (coll[3]!=-1) matrice[porte[3]][dimensione-1]=4;

	//riempie collegamento
	for (int i=0; i<4; i++)
		collegamento[i]=coll[i];
}

bool Stanza::existPorta(int n)
{
    return porte[n]!=-1;
}

int Stanza::getPorta(int n)
{
    return porte[n];
}

void Stanza::link(int partenza, int arrivo, bool type)  //type=0:2->3, type=1:0->1
{
    int prec, posx, posy, arrivox, arrivoy, direzione; //1 E, 2 S, 3 W, 4N
    prec=7;//valore nullo 7-4=3>+-2
    if (!type)
    {
        posx=1;
        posy=partenza;
        libero=posy;
        arrivox=dimensione-2;
        arrivoy=arrivo;
    }
    else
    {
        posx=partenza;
        posy=1;
        arrivox=arrivo;
        arrivoy=dimensione-2;
    }
    matrice[posy][posx]=-3;
    while (((posx != dimensione-2) && !type) || ((posy != dimensione-2) && type))
    {
        do
        {
            direzione=rand()%4+1;
        }
        while((prec-direzione)==2 || (prec-direzione)==-2  || (direzione-type)==3);
        if (direzione==1 && posx<dimensione-2)
        {
            prec=direzione;
            posx++;
        }
        else if (direzione==2 && posy<dimensione-2)
        {
            prec=direzione;
            posy++;
        }
        else if (direzione==3 && posx>1)
        {
            prec=direzione;
            posx--;
        }
        else if (direzione==4 && posy>1)
        {
            prec=direzione;
            posy--;
        }
        matrice[posy][posx]=-3;
    }
    matrice[arrivoy][arrivox]=-3;
    if (arrivoy<posy)  //type=1 non entra
    {
        int temp=arrivoy;
        arrivoy=posy;
        posy=temp;
    }
    if (arrivox<posx)  //type=0 non entra
    {
        int temp=arrivox;
        arrivox=posx;
        posx=temp;
    }

    for (int i=posy; i<arrivoy; i++)
        matrice[i][dimensione-2]=-3;

    for (int i=posx; i<arrivox; i++)
        matrice[dimensione-2][i]=-3;

}
//Sono necessarie 4 porte e porta 0 deve essere opposta a porta 1 (quindi anche per 2 e 3)
void Stanza::inserisciVia()
{
    int partenza[2], arrivo[2];
    for (int i=0; i<=2; i+=2)
    {
        if (existPorta(i)) partenza[i/2]=getPorta(i);
        else partenza[i/2]=rand()%(dimensione-2)+1;

        if (existPorta(i+1)) arrivo[i/2]=getPorta(i+1);
        else arrivo[i/2]=rand()%(dimensione-2)+1;
        link(partenza[i/2], arrivo[i/2], (i==0));
        //cout << "ciao";
    }
}

void Stanza::mettiMuri()
{
    //lo farà Vicci, momentaneamente random
    //int seed = rand() % 100000;
    for (int i=1; i<(dimensione-1); i++)
    {
        for (int j=1; j<(dimensione-1); j++)
        {
            if (matrice[i][j]==-2)
            {
                int r = buildWall(descreteNoise(i, j, (dimensione - 1), 0));
                if (r==0) matrice[i][j]=0;
            }
        }
    }
}

void Stanza::riempiMuri(int x, int y)
{
    if (matrice[y][x]==-2 || matrice[y][x]==-3)
    {
        matrice[y][x]=-1;
        riempiMuri(x+1,y);
        riempiMuri(x-1,y);
        riempiMuri(x,y+1);
        riempiMuri(x,y-1);
    }
}

void Stanza::trasformaInterni()
{
    for (int i=1; i<dimensione-1; i++)
    {
        for (int j=1; j<dimensione-1; j++)
        {
            if (matrice[i][j]==-2)
                matrice[i][j]=0;
        }
    }
}

int log(int n)
{
    if (n==1) return 0;
    return 1+log(n/2);
}

void Stanza::mettiMostri(int livello){

	for(int i=0; i<(dimensione-1); i++){
		for(int j=0; j<(dimensione-1) && nMaxMostri>0; j++){
			if (matrice[i][j]==-1){
				int den=1500/(log(livello)+14);
				int r=rand()%den;
				if (r==0){
					matrice[i][j]=1;
					nMaxMostri--;
				}
			}
		}
	}
}
int Stanza::nVicini(int x, int y)
{
    int somma=0;
    somma+=(matrice[x+1][y]==0 || matrice[x+1][y]==1);
    somma+=(matrice[x-1][y]==0 || matrice[x-1][y]==1);
    somma+=(matrice[x][y+1]==0 || matrice[x][y+1]==1);
    somma+=(matrice[x][y-1]==0 || matrice[x][y-1]==1);
    return somma;
}

void Stanza::mettiBauli(int livello)
{

    for(int i=0; i<(dimensione-1); i++)
    {
        for(int j=0; j<(dimensione-1) && nMaxBauli>0; j++)
        {
            if (matrice[i][j]==-1)
            {
                int den=2000/((livello/30.0)+1);
                if (nVicini(i,j)!=0) den=den/nVicini(i,j);
                int r=rand()%den;
                if (r==0)
                {
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

int Stanza::getColl(int n){
	return collegamento[n];
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
    this->dimensione=rand()%(MAXDIM-MINDIM+1)+MINDIM;
    inizializzaMatrice(this->matrice);
    
	mettiMuriContorno();
	mettiPorte(coll);
	inserisciVia();
	mettiMuri();
	riempiMuri(1, libero);
	trasformaInterni();
	mettiMostri(nLiv);
	mettiBauli(nLiv);	

	//this->stampaMatrice(this->matrice);
}

