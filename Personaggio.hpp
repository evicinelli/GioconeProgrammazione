#ifndef PERSONAGGIO_HPP_INCLUDED
#define PERSONAGGIO_HPP_INCLUDED
#define AZIONE 5
#include <string>
#include "Arma.hpp"
#include <stdlib.h>
#include <time.h>
class Personaggio
{
<<<<<<< HEAD
    protected:
        int str, dex, con, luck, hp, hpmax;    //forza, destrezza, costituzione, fortuna, punti vita, punti vita massimi
        int lev, act, exp;                               //livello, punti azione per turno, punti esperienza attuali
        Arma equip;                     //arma equipaggiata
    public:
        Personaggio();
        void setEquip(Arma e);
        void setStr(int x);
        void setDex(int x);
        void setCon(int x);
        void setLuck(int x);
        void setHp(int x);
        void setAct(int x);
        int getStr();
        int getDex();
        int getCon();
        int getLuck();
        int getHp();
        int getHpmax();
        int getAct();
        int getLev();
        int getExp();
        Arma getEquip();
        void attacca(Personaggio p);
=======
protected:
    int str, dex, con, luck, hp, hpmax;    //forza, destrezza, costituzione, fortuna, punti vita, punti vita massimi
    int lev, act, exp;                               //livello, punti azione per turno, punti esperienza attuali
    Arma equip;                     //arma equipaggiata
public:
    Personaggio();
    void setEquip(Arma e);
    void setStr(int x);
    void setDex(int x);
    void setCon(int x);
    void setLuck(int x);
    void setHp(int x);
    void setAct(int x);
    int getStr();
    int getDex();
    int getCon();
    int getLuck();
    int getHp();
    int getHpmax();
    int getAct();
    Arma getEquip();
    void attacca(Personaggio p);
>>>>>>> 01f99fac64ad8df4127b3bae0d3102f06b7680c3

};

#endif // PERSONAGGIO_HPP_INCLUDED
