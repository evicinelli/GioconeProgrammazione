# include "Stanza.hpp"
# include "NoiseGenerator.hpp"
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
    //inzialmente non ci sono porte
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
int Stanza::getLibero(){
	return libero;
}
Venditore* Stanza::getVenditoreByPos(int y, int x){
	Venditore* tmp; 
	
	for (int i=0; i<(2-nMaxVenditori); i++){
		if (v[i]->getPosX()==x && v[i]->getPosY()==y){
			tmp=v[i];
		}
	}
	return tmp;
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

void Stanza::setId(int n){
	id=n;
}

int Stanza::getId(){
	return id;
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
    //Porte random
    for (int i=0; i<4; i++)
    {
        if (coll[i]!=-1){
			if (i!=3)
				porte[i]=rand()%(dimensione-3)+2;
			else
				porte[i]=rand()%(dimensione-4)+2;
		}
    }
    //la porta solo se il collegamento nella direzione è != -1
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
	if (collegamento[n] != -1)
		return porte[n];
	else
		return -1;
}

void Stanza::link(int partenza, int arrivo, bool type)  //type=0:2->3, type=1:0->1
{
	/* Il metodo crea una via casuale tra due porte delle 4 porte
	 * Per generare questa via ci sarà un immaginario cursore che si può muovere in tre diverse direzioni:
	 * tutte fuorchè quella opposta a quella appena percorsa (inoltre non si potrà muovere nella direzione
	 * che lo riporterebbe vicino alla porta di partenza). Terminerà quando giungerà allo stesso lato della
	 * porta di arrivo.
	 */

	//posx e posy sono le coordinate del mio immaginario cursore
	//prec mi indica la direzione verso la quale il cursore si è precedentemente spostato
    int prec, posx, posy, arrivox, arrivoy, direzione;
    prec=7;//valore nullo 7-4=3>+-2

    //setto le variabili a seconda del tipo di collegamento
    if (!type)
    {
        posx=1;
        posy=partenza;
        arrivox=dimensione-2;
        arrivoy=arrivo;
    }
    else
    {
        posx=partenza;
        posy=1;
        arrivox=arrivo;
        arrivoy=dimensione-2;
        libero=arrivox;
    }
    matrice[posy][posx]=-3;

    //continua finchè non si arriva al lato opposto
    while (((posx != dimensione-2) && !type) || ((posy != dimensione-2) && type))
    {
		//la direzione deve essere giusta, cioè non deve essere opposta alla precedente,
		//in più non deve essere W se vado verso E e non N se vado verso S
        do
        {
            direzione=rand()%4+1;
        }
        while((prec-direzione)==2 || (prec-direzione)==-2 || (direzione-type)==3);

        //se riesco mi sposto nella direzione
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
    //il punto di arrivo fa parte della strada
    matrice[arrivoy][arrivox]=-3;

    /* Una volta arrivato al lato giusto devo arrivare fino alla porta
     * che si troverà lungo il medesimo lato
     */

    //faccio in modo che la pos sia < dell'arrivo (indipendentemente dal lato)
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

	//dalla posizione del cursore arrivo alla porta
    for (int i=posy; i<arrivoy; i++)
        matrice[i][dimensione-2]=-3;

    for (int i=posx; i<arrivox; i++)
        matrice[dimensione-2][i]=-3;

}
//Sono necessarie 4 porte e porta 0 deve essere opposta a porta 1 (quindi anche per 2 e 3)
void Stanza::inserisciVia()
{
    int partenza[2], arrivo[2];
    //partenza e arrivo contengono la coordinata variabile della porta di partenza e d arrivo
    for (int i=0; i<=2; i+=2)
    {
		//se la porta esiste bene, altrimenti me la invento
        if (existPorta(i)) partenza[i/2]=getPorta(i);
        else partenza[i/2]=rand()%(dimensione-2)+1;

        if (existPorta(i+1)) arrivo[i/2]=getPorta(i+1);
        else arrivo[i/2]=rand()%(dimensione-2)+1;

        link(partenza[i/2], arrivo[i/2], (i==0));
    }
}

void Stanza::mettiMuri()
{
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
	//se posso andarci allora imposto a -1
	if (matrice[y][x]==-2 || matrice[y][x]==-3)
    {
		matrice[y][x]=-1;
        riempiMuri(x+1,y);
        riempiMuri(x-1,y);
        riempiMuri(x,y+1);
        riempiMuri(x,y-1);
    }
}

bool Stanza::isVendBloccato(int y, int x){
	bool cond=false;
	if (matrice[y][x]==2){
		cond= ((matrice[y-1][x]==0 || matrice[y-1][x]==-2) && 
				(matrice[y+1][x]==0 || matrice[y+1][x]==-2) &&
				(matrice[y][x+1]==0 || matrice[y][x+1]==-2) &&
				(matrice[y][x-1]==0 || matrice[y][x-1]==-2));
	}
	return cond;
}

void Stanza::trasformaInterni()
{
    for (int i=1; i<dimensione-1; i++)
    {
        for (int j=1; j<dimensione-1; j++)
        {
            if (matrice[i][j]==-2 || isVendBloccato(i, j))
                matrice[i][j]=0;
        }
    }
}

void Stanza::mettiMostri(int livello){
    int mCounter = 0;
	for(int i=0; i<(dimensione-1); i++){
		for(int j=0; j<(dimensione-1) && nMaxMostri>0; j++){
			if (matrice[i][j]==-1){
				//denominatore dellla funzione di probabilità che appaia un mostro in una casella
				int den=(170-MAXDIM)+dimensione;
				int r=rand()%den;
				if (r==0){
                    int razza=(int)rand()%3;
                    matrice[i][j]=1;
                    switch (razza)
                    {
						case 0:
							monsters[mCounter] = new Mostro(livello, "bandito");
							break;
						case 1:
							monsters[mCounter] = new Mostro(livello, "orco");
							break;
						case 2:
							monsters[mCounter] = new Mostro(livello, "troll");
							break;
                    }
                    monsters[mCounter]->setPosX(j);
                    monsters[mCounter]->setPosY(i);
                    printf("%d - %p\n", mCounter, monsters[mCounter]);
					nMaxMostri--;
                    mCounter++;
				}
			}
		}
	}

    nRealMostri = mCounter;
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
				//denominatore dellla funzione di probabilità che appaia un mostro in una casella
                int den=1700/((livello/30.0)+1);
                //la probabilità è moltiplicata per il numero di muri/mostri che la casella ha vicino
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
	int nVend=0;
	for(int i=0; i<(dimensione-1); i++){
		for(int j=0; j<(dimensione-1) && nMaxVenditori>0; j++){
			if (matrice[i][j]==-2 && matrice[i-1][j-1]!=2 && matrice[i-1][j+1]!=2 && 
				matrice[i][j-2]!=2 && matrice[i][j-1]!=2 && matrice[i-1][j]!=2 && matrice[i-2][j]!=2){
				//denominatore dellla funzione di probabilità che appaia un mostro in una casella
				int den=20;//1500/((livello/20.0)+2);
				int r=rand()%den;
				if (r==0){
					matrice[i][j]=2;
					v[nVend]=new Venditore(livello, i, j);
					nVend++;
					nMaxVenditori--;
				}
			}
		}
	}

}

int Stanza::getColl(int n){
	return collegamento[n];
}

void Stanza::liberaPorte(){
	matrice[dimensione-2][libero]=-3;
	if (collegamento[0]!=-1) matrice[1][porte[0]]=-3;
	if (collegamento[1]!=-1) matrice[dimensione-2][porte[1]]=-3;
	if (collegamento[2]!=-1) matrice[porte[2]][1]=-3;
	if (collegamento[3]!=-1) matrice[porte[3]][dimensione-2]=-3;
}

void Stanza::normalizza()
{
    for (int i=1; i<dimensione-1; i++)
        {
            for (int j=1; j<dimensione-1; j++)
            {
                if (matrice[i][j]==-3)
                    matrice[i][j]=-1;
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

	
    this->dimensione=rand()%(MAXDIM-MINDIM+1)+MINDIM;
    inizializzaMatrice(this->matrice);

	mettiMuriContorno();
	mettiPorte(coll);
	inserisciVia();
	mettiMuri();
    mettiVenditori(nLiv); //i venditori non possono stare sulla via
    riempiMuri(libero, dimensione-2);
    trasformaInterni();
	liberaPorte();
    mettiMostri(nLiv);
    mettiBauli(nLiv);
    normalizza();
}
Mostro* Stanza::getMonsterByCoord(int x, int y)
{
		int i;
		bool flag=false;
		for (i=0;i<getHowManyMonsters() && !flag;i++)
		{
			if (getMonster(i)->getPosX()==x && getMonster(i)->getPosY()==y)
			{
				flag=true;
			}
		}
		if (flag==true)
			return getMonster(i-1);
		else
			return NULL;
}

Mostro* Stanza::getMonster(int i)
{
    return monsters[i];
}

int Stanza::getHowManyMonsters()
{
    return nRealMostri;
}

int Stanza::getSpot(int i, int j)
{
    return matrice[i][j];
}

void Stanza::setSpot(int i, int j, int value)
{
    matrice[i][j] = value;
}
