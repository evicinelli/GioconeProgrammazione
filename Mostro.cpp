# include "Mostro.hpp"

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
		n=1.5*((double)rand()/RAND_MAX)+1;
		con=(int)(1.1*lev+n*lev);
	}
	else if (race=="orco")
	{
		id='O';
		n=((double)rand()/RAND_MAX)+1;
		str=(int)(1.2*lev+n*lev);
		n=((double)rand()/RAND_MAX)+1;
		dex=(int)(lev+n*lev);
		n=2*((double)rand()/RAND_MAX)+1;
		con=(int)(1.5*lev+n*lev);

	}
	else if (race=="troll")
	{
		id='T';
		n=2*((double)rand()/RAND_MAX)+1;
		str=(int)(1.5*lev+n*lev);
		n=0.3*((double)rand()/RAND_MAX)+1;
		dex=(int)(0.5*lev+n*lev);
		n=5*((double)rand()/RAND_MAX)+1;
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
	int direzione = 0;		/* Direzione in cui devo muovermi */
	int oldDirezione = 0;	/* Ultima direzione in cui mi sono mosso */
	int incX, incY;		/* Incrementi di posizione */
//	int iter = 0;		/* Contatore delle iterazioni */

	do {
		incX = 0;
		incY = 0;
		//do {
			direzione = rand() % 4;
		//} while ((abs(direzione - oldDirezione) == 1) /* && iter < 200 */);

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
//		++iter;
	} while(m[y + incY][x + incX] != -1 || ((x + incX) == tx && (y + incY) == ty) || ((x + incX) > dimensione) || ((y + incY) > dimensione));
	this->setPosX(x + incX);
	this->setPosY(y + incY);
}

void Mostro::insegui(int targetX, int targetY, int matrix[24][24], int dimensione)
{

}

void Mostro::morte(Giocatore *g)
{
	double prob=100*((double)rand()/RAND_MAX);
	int gold=lev*15+(int)(g->getLuck()*3.5);
	double drop=equip.getDropRate()+(0.2*g->getLuck());
	int expGain=lev*30+g->getLuck()*5;
	g->addOro(gold);
	g->addExp(expGain);
	if (prob<=drop)                         //da controllare il funzionamento nel gioco reale
	{
		int i=0;
		while (g->getInv(i).isAvailable())
		{
			i++;
		}
		if (i<MAX_ITEM)
		{
			g->setInv(i,equip);
		}
	}

	alive = false;
}

int Mostro::takeAction(Giocatore* g, int m[24][24], int dimensione)
{
	int targetX = g->getPosX();
	int targetY = g->getPosY();
	int result=0;
	if (this->needToAttack(g) && (act - 4) >= 0) {
		result=attacca(g);			//in caso di attacco restituisce il danno inflitto come valore di ritorno
		//act -= 4;
		// printf("Grrr!!!!\n");
	} else {
		if (this->needToChase(g)) {
			chasing = true;
			insegui(targetX, targetY, m, dimensione);
			result=1;
			// printf("Trovato!\n");
		} else {
			muovi(targetX, targetY, m, dimensione);
			// printf("Dove sei?\n");
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
		   (abs(g->getPosY() - this->getPosY()) <=1);
}

/* Se il giocatore si trova in un quadrato AGGRO x AGGRO intorno al mostro,
 * allora il mostro insegue il giocatore */
bool Mostro::needToChase(Giocatore* g)
{
	 return (abs(g->getPosX() - this->getPosX()) < AGGRO) &&
			(abs(g->getPosY() - this->getPosY()) < AGGRO);
}

bool Mostro::isChasing()
{
	return chasing;
}
