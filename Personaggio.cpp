#include "Personaggio.hpp"

Personaggio::Personaggio()
{
}
void Personaggio::setEquip(Arma e)
{
    equip=e;
}
void Personaggio::setStr(int x)
{
    str=x;
}
void Personaggio::setDex(int x)
{
    dex=x;
}
void Personaggio::setCon(int x)
{
    con=x;
}
void Personaggio::setLuck(int x)
{
    luck=x;
}
void Personaggio::setHp(int x)
{
    hp=x;
}
int Personaggio::getStr()
{
    return str;
}
int Personaggio::getDex()
{
    return dex;
}
int Personaggio::getCon()
{
    return con;
}
int Personaggio::getLuck()
{
    return luck;
}
int Personaggio::getHp()
{
    return hp;
}
Arma Personaggio::getEquip()
{
    return equip;
}
