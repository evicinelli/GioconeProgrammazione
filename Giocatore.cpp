#include "Giocatore.hpp"

Giocatore::Giocatore()
{
    str=5;
    dex=5;
    con=8;
    luck=3;
    hpmax=con*20;
    hp=hpmax;
    act=5;
    oro=0;
    exp=0;
    nextLevExp=200;
    lev=1;
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


void morte()
{

}
