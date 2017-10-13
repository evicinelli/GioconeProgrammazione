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
	int x = this->getPosX();
	int y = this->getPosY();
	int direzione = 0;	/* Direzione in cui devo muovermi */
	int oldDirezione = 0;	/* Ultima direzione in cui mi sono mosso */
	int incX, incY;		/* Incrementi di posizione */
	int counter = 0;	/* Massimo numero di tentativi per trovare una posizione casuale accettabile; evita che il mostro blocchi il gioco nel caso in cui sia circondato da altri mostri */

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
	spot* mSpot = new spot;
	mSpot->c = this->getPosX(); mSpot->r = this->getPosY(); mSpot->val = dmap[mSpot->r][mSpot->c];

	spot* up = new spot; 	up->c = this->getPosX(); 	up->r = this->getPosY() - 1; 	up->val = dmap[up->r][up->c];
	spot* down = new spot; 	down->c = this->getPosX(); 	down->r = this->getPosY() + 1; 	down->val = dmap[down->r][down->c];
	spot* left = new spot; 	left->c = this->getPosX() - 1; 	left->r = this->getPosY(); 	left->val = dmap[left->r][left->c];
	spot* right = new spot; right->c = this->getPosX() + 1; right->r = this->getPosY(); 	right->val = dmap[right->r][right->c];


	spot* move_to = _min(min(up, down, left, right), mSpot);

	this->setPosY(move_to->r);
	this->setPosX(move_to->c);
}

void Mostro::morte(Giocatore *g)
{
	double prob=100*((double)rand()/RAND_MAX);
	int gold=lev*15+(int)(g->getLuck()*3.5);
	double drop=equip.getDropRate()+(0.2*g->getLuck());
	int expGain=20+lev*60+g->getLuck()*8+(con+dex+str)*2;
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
	this->buildDMap(g->getPosX(), g->getPosY(), m, dimensione);

	if (this->needToAttack(g) && (act - 4) >= 0) {
		chasing = false; 				//lo coloriamo anche quando attacca
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

void Mostro::buildDMap(int tx, int ty, int m[24][24], int dim)
{

	/* FILE *f = fopen("log.log", "a"); */
	std::queue<int> myq;

	for (int i = 0; i < 24 * 24; ++i) {
		d[i] = IFTY;
	}

	myq.push(hash(ty, tx, dim));
	d[hash(ty, tx, dim)] = 0;
	int popped_r;
	int popped_c;


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

	for (int i = 0; i < dim; ++i){
		for (int j = 0; j < dim; ++j) {
			dmap[i][j] = d[hash(i, j, dim)];
			/* fprintf(f, "%d   ", dmap[i][j]); */
		}
		/* fprintf(f, "\n"); */
	}
}

int Mostro::hash(int r, int c, int dim)
{
	return (r * dim) + c;
}

int Mostro::getR(int a, int dim)
{
	return a / dim;
}

int Mostro::getC(int a, int dim)
{
	return a % dim;
}

bool Mostro::isAlreadyEnqueued(int r, int c, int dim){
	return d[hash(r, c, dim)] != IFTY;
}

spot* Mostro::_min(spot* a, spot* b)
{
	spot* out;
	if (a->val < b->val && a->val != 0) out = a;
	else if (b != 0 ) out = b;
	else out = a;

	return out;
}

spot* Mostro::min(spot* a, spot* b, spot* c, spot* d)
{
	return _min(_min(a, b), _min(c, d));
}
