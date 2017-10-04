#include "Mostro.hpp"

Mostro::Mostro(int level, std::string race)
{
    act=AZIONE;
    lev=level;
    srand(time(0));
    double n;               //fattore casuale nelle statistiche del mostro
    if (race=="bandito")
    {
        id='B';
        n=1.5*((double)rand()/RAND_MAX)+1;
        str=(int)(2*lev+n*lev);
        n=1.5*((double)rand()/RAND_MAX)+1;
        dex=(int)(2*lev+n*lev);
        n=1.5*((double)rand()/RAND_MAX)+1;
        con=(int)(2*lev+n*lev);
    }
    else if (race=="orco")
    {
        id='O';
        n=((double)rand()/RAND_MAX)+1;
        str=(int)(3*lev+n*lev);
        n=((double)rand()/RAND_MAX)+1;
        dex=(int)(lev+n*lev);
        n=2*((double)rand()/RAND_MAX)+1;
        con=(int)(4*lev+n*lev);

    }
    else if (race=="troll")
    {
        id='T';
        n=2*((double)rand()/RAND_MAX)+1;
        str=(int)(5*lev+n*lev);
        n=0.3*((double)rand()/RAND_MAX)+1;
        dex=(int)(0.5*lev+n*lev);
        n=5*((double)rand()/RAND_MAX)+1;
        con=(int)(5*lev+n*lev);

    }
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

void Mostro::scanPlayer(Giocatore *g)
{

}

void Mostro::muovi()
{
    //aggiorna punti azione
}

void Mostro::insegui(Giocatore *g)
{
    //aggiorna punti azione
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
}
