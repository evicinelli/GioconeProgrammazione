#include "Giocatore.hpp"

Giocatore::Giocatore()
{
    str=8;
    dex=8;
    con=10;
    luck=5;
    hpmax=con*20;
    hp=hpmax;
    act=AZIONE;
    oro=0;
    exp=0;
    nextLevExp=80;
    lev=1;
    pot=2;
    equip=Arma(1,"spada");
}

int Giocatore::getOro()
{
    return oro;
}
int Giocatore::getNextExp()
{
	return nextLevExp;
}

int Giocatore::getPot()
{
    return pot;
}
void Giocatore::addPot()
{
    pot++;
}
Arma Giocatore::getInv(int n)
{
    return inventario[n];
}
void Giocatore::setInv(int n, Arma a)
{
    inventario[n]=a;
}
void Giocatore::setOro(int o)
{
    oro=o;
}
void Giocatore::addOro(int o)
{
    oro+=o;
}
void Giocatore::addExp(int e)
{
    exp+=e;
}

void Giocatore::levelup(int stat)
{
    switch(stat)
    {
    case 1:
        str++;
        break;
    case 2:
        dex++;
        break;
    case 3:
        con++;
        hpmax+=20;
        break;
    case 4:
        luck++;
        break;
    }
    hp=hpmax;
    lev++;
    exp=exp-nextLevExp;
    nextLevExp=nextLevExp*lev;
}

void Giocatore::cambioArma(int pos)
{
    if (inventario[pos].isAvailable())
    {
        Arma temp=equip;
        equip=inventario[pos];
        inventario[pos]=temp;
    }
}

void Giocatore::scartaArma(int pos)
{
    inventario[pos].scarta();
}


int Giocatore::libInventario(){
	int pos=-1;
	int i=0;
	while ((pos==-1) && (i<MAX_ITEM)){
		if (!getInv(i).isAvailable())
			pos=i;
		i++;
	}
	return pos;
}


int Giocatore::usaPozione()
{
    int recuperato=-1;
    if (pot>0)
    {
        pot--;
        act--;
        recuperato=(20+5*lev);
        hp+=recuperato;
        if (hp>hpmax)
		{
			recuperato=hpmax-(hp-recuperato);
			hp=hpmax;
		}
    }
    return recuperato;
}

void morte()
{

}
