#include "Giocatore.hpp"

Giocatore::Giocatore()
{
    str=5;
    dex=5;
    con=8;
    luck=3;
    hpmax=con*20;
    hp=hpmax;
    act=AZIONE;
    oro=0;
    exp=0;
    nextLevExp=200;
    lev=1;
    equip=Arma(0,"spada");
}

int Giocatore::getOro()
{
    return oro;
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
    if (exp>=nextLevExp)
        levelup(5);                     //da collegare con la schermata di levelup per l'input, non completo
}
//da implementare la gestione dell'inventario e il metodo di equipaggiamento arma

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

void Giocatore::cambioArma(int pos)                         //da debuggare, devo provarla bene
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

void Giocatore::usaPozione()
{
    if (pot>0)
    {
        pot--;
        hp+=(20+5*lev);
    }
}

void morte()
{

}
