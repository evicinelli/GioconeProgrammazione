# include "Mostro.hpp"
# include <queue>
# define IFTY 580

Mostro::Mostro(int level, std::string race)
{
	alive = true;
	act=AZIONE;
	lev=level;
	double n;               //fattore casuale nelle statistiche del mostro
	if (race=="bandito")
	{
		id='R';
		n=0.75*((double)rand()/RAND_MAX)+1;
		str=(int)(lev+n*lev);
		n=1.5*((double)rand()/RAND_MAX)+1;
		dex=(int)(lev+n*lev);
		n=0.5*((double)rand()/RAND_MAX)+1;
		con=(int)(1.1*lev+n*lev);
	}
	else if (race=="orco")
	{
		id='O';
		n=((double)rand()/RAND_MAX)+1;
		str=(int)(1.2*lev+n*lev);
		n=((double)rand()/RAND_MAX)+1;
		dex=(int)(lev+n*lev);
		n=1.1*((double)rand()/RAND_MAX)+1;
		con=(int)(1.5*lev+n*lev);

	}
	else if (race=="troll")
	{
		id='T';
		n=2*((double)rand()/RAND_MAX)+1;
		str=(int)(1.5*lev+n*lev);
		n=0.3*((double)rand()/RAND_MAX)+1;
		dex=(int)(0.5*lev+n*lev);
		n=1.5*((double)rand()/RAND_MAX)+1;
		con=(int)(2*lev+n*lev);

	}
	razza=race;
	luck=0;
	exp=0;
	hpmax=20*con;
	hp=hpmax;
	int r=(int)rand()%3;
	switch (r)
	{
	case 0:
		equip=Arma(lev,"spada");
		break;
	case 1:
		equip=Arma(lev,"mazza");
		break;
	case 2:
		equip=Arma(lev,"pugnale");
		break;
	}
}

char Mostro::getId()
{
	return id;
}

std::string Mostro::getRazza()
{
	return razza;
}

void Mostro::muovi(int tx, int ty, int m[24][24], int dimensione)
{
	int x = this->getPosX();/* Posizione <x,y> del mostro */
	int y = this->getPosY();
	int direzione = 0;	/* Direzione in cui devo muovermi */
	int oldDirezione = 0;	/* Ultima direzione in cui mi sono mosso */
	int incX, incY;		/* Incrementi di posizione */
	int counter = 0;	/* Massimo numero di tentativi per trovare una posizione casuale accettabile; evita che il mostro blocchi il gioco nel caso in cui sia circondato da altri mostri */
	
	/* Scelgo una direzione, calcolo l'incremento lungo quella direzione e poi setto la
	 * posizione. Ripeto tutto fino a che:
	 * 1) Capito su una posizione che non sia strada
	 * 2) Capito sul giocatore
	 * 3) Capito fuori dalla matrice 
	 * 4) Il numero delle iterazioni < 500 (evita ciclo infinito se il mostro si trova bloccato in
	 * tutte e 4 le direzioni)*/
	do {
		incX = 0;
		incY = 0;
		direzione = rand() % 4;
		switch( direzione ) {
			case 0:	/* BASSO */
				++incY;
				break;
			case 1: /* ALTO */
				--incY;
				break;
			case 2:	/* DESTRA */
				++incX;
				break;
			case 3: /* SINISTRA */
				--incX;
				break;
		}
		oldDirezione = direzione;
		counter++;
	} while((m[y + incY][x + incX] != -1 || ((x + incX) == tx && (y + incY) == ty) || ((x + incX) > dimensione) || ((y + incY) > dimensione)) && counter<500);
	if (counter<500) {
		this->setPosX(x + incX);
		this->setPosY(y + incY);
	}
}

void Mostro::insegui(int matrix[24][24], int dimensione)
{
	spot* mSpot = new spot; /* Casella della dmap dove si trova il mostro */
	mSpot->c = this->getPosX(); mSpot->r = this->getPosY(); mSpot->val = dmap[mSpot->r][mSpot->c];

	/* Spot è una struttura che tiene le coordinate e il valore di una casella sulla dmap del
	 * mostro. Facilita il confronto. */
	spot* up = new spot; 	up->c = this->getPosX(); 	up->r = this->getPosY() - 1; 	up->val = dmap[up->r][up->c];
	spot* down = new spot; 	down->c = this->getPosX(); 	down->r = this->getPosY() + 1; 	down->val = dmap[down->r][down->c];
	spot* left = new spot; 	left->c = this->getPosX() - 1; 	left->r = this->getPosY(); 	left->val = dmap[left->r][left->c];
	spot* right = new spot; right->c = this->getPosX() + 1; right->r = this->getPosY(); 	right->val = dmap[right->r][right->c];

	/* Decido lo spot minimoi (con valore minimo, ovvero il più conveniente) tra quelli che circondano il mostro e quello su cui si trova il
	 * mostro stesso */
	spot* move_to = _min(min(up, down, left, right), mSpot);
	
	/* Mi sposto in quello spot */
	this->setPosY(move_to->r);
	this->setPosX(move_to->c);
}

void Mostro::morte(Giocatore *g)
{
	double prob=100*((double)rand()/RAND_MAX);
	int gold=lev*15+(int)(g->getLuck()*3.5);
	double drop=equip.getDropRate()+(0.2*g->getLuck());
	int expGain=(20+lev*60+(con+dex+str)*2)*(int)(1+g->getLuck()*0.15);
	g->addOro(gold);
	g->addExp(expGain);
	if (prob<=drop)
	{
		if (g->libInventario()!=-1)
			g->setInv(g->libInventario(),equip);
	}

	alive = false;
}

int Mostro::takeAction(Giocatore* g, int m[24][24], int dimensione)
{
	int targetX = g->getPosX();
	int targetY = g->getPosY();
	int result=0;

	/* Costruisco la Dijkstra Map della stanza a partire dal giocatore */
	this->buildDMap(g->getPosX(), g->getPosY(), m, dimensione);

	/* Devo attaccare, inseguire o muovermi a caso? */
	if (this->needToAttack(g) && (act - 4) >= 0) {
		chasing = false; 			//lo coloriamo anche quando attacca
		result=attacca(g);			//in caso di attacco restituisce il danno inflitto come valore di ritorno
	} else {
		if (this->needToChase(g)) {
			chasing = true;
			insegui(m, dimensione);
			result=1;
		} else {
			chasing = false;
			muovi(targetX, targetY, m, dimensione);
		}
		act -= 1;
	}
	return result;
}

bool Mostro::isAlive()
{
	return alive;
}

/* Se il giocatore si trova vicino al mostro, allora il mostro attacca */
bool Mostro::needToAttack(Giocatore* g)
{
	return (abs(g->getPosX() - this->getPosX()) <=1) &&
		   (abs(g->getPosY() - this->getPosY()) <=1) &&
		   !(abs(g->getPosY() - this->getPosY()) ==1 && abs(g->getPosX() - this->getPosX()) ==1);
}

/* Se il giocatore si trova in un quadrato AGGRO x AGGRO intorno al mostro,
 * allora il mostro insegue il giocatore */
bool Mostro::needToChase(Giocatore* g)
{
	 return (abs(g->getPosX() - this->getPosX()) <= AGGRO) &&
		(abs(g->getPosY() - this->getPosY()) <= AGGRO);
}

bool Mostro::isChasing()
{
	return chasing;
}


/* Costruisce la mappa di Dijkstra a partire dal giocatore. Vedere 
http://www.roguebasin.com/index.php?title=Dijkstra_Maps_Visualized  per dettagli sulle mappe.
L'idea è quella di costruire una coda e un array delle distanze. Si inizializza l'array a INFINITY,
e si mette in coda la casella di partenza (quella dove si trova il giocatore). La sua distanza
nell'array sarà 0. Si accodano le caselle adiacenti, se non sono già in coda, e la loro distanza
sarà 1 + la distanza della casella da cui sono arrivato. Si passa dalla coppia <r, c> all'indice
nell'array e viceversa usando hash(r, c) e getR(hash) o getC(hash). Per ultimo, si riempe la matrice
interna con gli opportuni valori prelevati dall'array delle distanze appena calcolate. */
void Mostro::buildDMap(int tx, int ty, int m[24][24], int dim)
{

	std::queue<int> myq;
	
	/* Inizializzo a IFTY il vettore. IFTY > MAXDIM*MAXDIM, perchè siamo sicuri che nessuna
	 * casella sarà distante più di MAXDIM^2 dalla casella origine */
	for (int i = 0; i < 24 * 24; ++i) {
		d[i] = IFTY;
	}

	/* Accodo la casella di partenza */
	myq.push(hash(ty, tx, dim));
	d[hash(ty, tx, dim)] = 0;
	int popped_r;
	int popped_c;

	/* Fino a che la coda è piena, analizzo il primo elemento e accodo i suoi vicini. Calcolo le
	 * distanze per ogni elemento che prelevo dalla coda */
	while(!myq.empty()) {
		popped_r = getR(myq.front(), dim);
		popped_c = getC(myq.front(), dim);
		myq.pop();

		if(!isAlreadyEnqueued(popped_r - 1, popped_c, dim) && popped_r > 0 && m[popped_r - 1][popped_c] == -1) {
			myq.push(hash(popped_r - 1, popped_c, dim));
			d[hash(popped_r - 1, popped_c, dim)] = 1 + d[hash(popped_r, popped_c, dim)];
		}

		if(!isAlreadyEnqueued(popped_r + 1, popped_c, dim) && popped_r < dim && m[popped_r + 1][popped_c] == -1) {
			myq.push(hash(popped_r + 1, popped_c, dim));
			d[hash(popped_r + 1, popped_c, dim)] = 1 + d[hash(popped_r, popped_c, dim)];
		}

		if(!isAlreadyEnqueued(popped_r, popped_c - 1, dim) && popped_c > 0 && m[popped_r][popped_c - 1] == -1) {
			myq.push(hash(popped_r, popped_c - 1, dim));
			d[hash(popped_r, popped_c - 1, dim)] = 1 + d[hash(popped_r, popped_c, dim)];
		}
		if(!isAlreadyEnqueued(popped_r, popped_c + 1, dim) && popped_c < dim && m[popped_r][ popped_c + 1] == -1) {
			myq.push(hash(popped_r, popped_c + 1, dim));
			d[hash(popped_r, popped_c + 1, dim)] = 1 + d[hash(popped_r, popped_c, dim)];
		}
	}

	/* Copio opportunamente l'array delle distanze nella matrice */
	for (int i = 0; i < dim; ++i){
		for (int j = 0; j < dim; ++j) {
			dmap[i][j] = d[hash(i, j, dim)];
		}
	}
}

/* Hash della coppia <r, c> per ottenere un indice compatibile nell'array delle distanze */
int Mostro::hash(int r, int c, int dim)
{
	return (r * dim) + c;
}

/* Dall'hash mi da la riga usata per generarlo */
int Mostro::getR(int a, int dim)
{
	return a / dim;
}

/* Dato l'hash mi restituisce la colonna usata per generarlo */
int Mostro::getC(int a, int dim)
{
	return a % dim;
}

bool Mostro::isAlreadyEnqueued(int r, int c, int dim){
	return d[hash(r, c, dim)] != IFTY;
}

/* Calcola lo spot con il valore minimo tra due spot dati, preoccupandosi di non ritornare _mai_ uno
 * spot con valore = 0 (sarebbe lo spot dove si trova il giocatore nella mappa) */
spot* Mostro::_min(spot* a, spot* b)
{
	spot* out;
	if (a->val < b->val && a->val != 0) out = a;
	else if (b != 0 ) out = b;
	else out = a;

	return out;
}

/* Minimo tra 4 spot. Vedi _min per maggiori dettagli */
spot* Mostro::min(spot* a, spot* b, spot* c, spot* d)
{
	return _min(_min(a, b), _min(c, d));
}
