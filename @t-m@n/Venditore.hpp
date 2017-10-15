#ifndef VENDITORE_HPP_INCLUDED
#define VENDITORE_HPP_INCLUDED
#include "Arma.hpp"
#include "Giocatore.hpp"

class Venditore
{
protected:
    bool pozioni;
    int costopot;
    Arma vendita[3];
    int posx;
    int posy;
public:
    Venditore();
    Venditore(int level, int y, int x);
    void riempi(int a, int lev);
    Arma getVendita(int n);
    int vendi(Giocatore* g, int n);				//metodo di vendita che usa libInventario(); analogamente a quest'ultimo metodo, ritorna -1 se l'inventario è pieno
    bool getPozioni();
    int getCostoPot();
    int getPosX();
    int getPosY();
    

};

#endif // VENDITORE_HPP_INCLUDED
