#include "Venditore.hpp"
#include <iostream>
Venditore::Venditore()
{
}
Venditore::Venditore(int level)
{
    costopot=50+(int)(0.5*level);
    srand(time(0));
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

void Venditore::vendi(Giocatore g, int n)
{
    int gold=g.getOro();
    if (n>=0 && n<=2)
    {
        if (gold>vendita[n].getPrezzo() && vendita[n].isAvailable())
        {
            int i=0;
            while (g.getInv(i).isAvailable())     //controllo che ci sia uno slot libero nell'inventario (se l'arma è disponibile lo slot è occupato)
            {
                i++;
            }
            if (i<MAX_ITEM)
            {
                g.setInv(i,vendita[n]);
                g.setOro(gold-vendita[n].getPrezzo());
                vendita[n].scarta();
            }

        }
    }
    else if (n==3)
    {
        if (gold>costopot)
        {
            g.addPot();
            g.setOro(gold-costopot);
        }
    }
}
