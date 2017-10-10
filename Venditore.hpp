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
public:
    Venditore();
    Venditore(int level);
    void riempi(int a, int lev);
    Arma getVendita(int n);
    int vendi(Giocatore* g, int n);				//metodo di vendita che usa libInventario(); analogamente a quest'ultimo metodo, ritorna -1 se l'inventario è pieno

};

#endif // VENDITORE_HPP_INCLUDED
