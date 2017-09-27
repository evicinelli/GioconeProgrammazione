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
    void vendi(Giocatore g, int n);

};

#endif // VENDITORE_HPP_INCLUDED
