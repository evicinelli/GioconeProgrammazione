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
bool Personaggio::actMuovi()
{
    if (act>=1)
    {
        act-=1;
        return true;
    }
    return false;
}
bool Personaggio::actUsa()
{
    if (act>=3)
    {
        act-=3;
        return true;
    }
    return false;
}
bool Personaggio::actApri()
{
    if (act>=2)
    {
        act-=2;
        return true;
    }
    return false;
}
bool Personaggio::actVend()
{
    if (act>=1)
    {
        act-=1;
        return true;
    }
    return false;
}
bool Personaggio::actAttacca()
{
    if (act>=4)
    {
        act-=4;
        return true;
    }
    return false;

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
int Personaggio::attacca(Personaggio *p)
{
    srand(time(0));
	int dannoTot=-1;
    if(actAttacca())
    {
        int dannoArma=(int) (equip.getMin()+																	//danno minimo inflitto
							(equip.getMax()-equip.getMin())														//danno massimo aggiuntivo inflitto (max-min)
							*((double)rand()/RAND_MAX));														//fattore casuale di danno inflitto
        dannoTot=dannoArma+(int)(equip.getStrMult()*str)+(int)(equip.getDexMult()*dex)+(int)(luck*0.4);			//applicazione dei moltiplicatori di forza e destrezza, insieme alla fortuna
        int currHp=p->getHp();
        p->setHp(currHp-dannoTot);
    }
    return dannoTot;
}
