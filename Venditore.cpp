#include "Venditore.hpp"
#include <iostream>
Venditore::Venditore()
{
}
Venditore::Venditore(int level, int y, int x)
{
	posx=x;
	posy=y;
    costopot=50+(int)(0.5*level);
    //srand(time(0));
    riempi(0,level);
    riempi(1,level);
    riempi(2,level);
    if ((int)rand()%2==1)
        pozioni=true;
    else
        pozioni=false;
}

void Venditore::riempi(int a, int lev)
{
    int r=(int)rand()%3;
    switch (r)
    {
    case 0:
        vendita[a]=Arma(lev,"spada");
        break;
    case 1:
        vendita[a]=Arma(lev,"mazza");
        break;
    case 2:
        vendita[a]=Arma(lev,"pugnale");
        break;
    }
}

Arma Venditore::getVendita(int n)
{
    return vendita[n];
}

int Venditore::vendi(Giocatore* g, int n)
{
    int gold=g->getOro();
    int pos=g->libInventario();
    if (n>=0 && n<=2)
    {
        if (gold>=vendita[n].getPrezzo() && vendita[n].isAvailable())
        {

			if (pos!=-1)
			{
                g->setInv(pos,vendita[n]);
                g->setOro(gold-vendita[n].getPrezzo());
                vendita[n].scarta();
			}

        }
    }
    else if (n==3)
    {
        if (gold>=costopot)
        {
            g->addPot();
            g->setOro(gold-costopot);
            pozioni=false;
        }
    }
    return pos;
}

bool Venditore::getPozioni()
{
	return pozioni;
}

int Venditore::getCostoPot()
{
	return costopot;
}

int Venditore::getPosX()
{
	return posx;
}

int Venditore::getPosY()
{
	return posy;
}
