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
void Personaggio::setAct(int x)
{
    act=x;
}
void Personaggio::setPosX(int x)
{
	posx=x;
}
void Personaggio::setPosY(int y)
{
	posy=y;
}
int Personaggio::getPosX()
{
	return posx;
}
int Personaggio::getPosY()
{
	return posy;
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
int Personaggio::getHpmax()
{
    return hpmax;
}
Arma Personaggio::getEquip()
{
    return equip;
}
int Personaggio::getLev()
{
    return lev;
}
int Personaggio::getExp()
{
	return exp;
}
int Personaggio::getAct()
{
    return act;
}
void Personaggio::attacca(Personaggio p)
{
    srand(time(0));
    int dannoArma=(int)((equip.getMin()+equip.getMax())/(1+(double)rand()/RAND_MAX));
    int dannoTot=dannoArma+(equip.getStrMult()*str)+(equip.getDexMult()*dex);
    int currHp=p.getHp();
    p.setHp(currHp-dannoTot);
}
