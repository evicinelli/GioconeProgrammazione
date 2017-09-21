#ifndef PERSONAGGIO_HPP_INCLUDED
#define PERSONAGGIO_HPP_INCLUDED
#include <string>
#include "Arma.hpp"
#include <stdlib.h>
class Personaggio
{
    protected:
        int str, dex, con, luck, hp;    //forza, destrezza, costituzione, fortuna, punti vita
        Arma equip;                     //arma equipaggiata
    public:
        Personaggio();
        void setEquip(Arma e);
        void setStr(int x);
        void setDex(int x);
        void setCon(int x);
        void setLuck(int x);
        void setHp(int x);
        int getStr();
        int getDex();
        int getCon();
        int getLuck();
        int getHp();
        Arma getEquip();

};

#endif // PERSONAGGIO_HPP_INCLUDED
