#ifndef GIOCATORE_HPP_INCLUDED
#define GIOCATORE_HPP_INCLUDED
#define MAX_ITEM 3
#define MAX_POTION 10
#include "Personaggio.hpp"

class Giocatore : public Personaggio
{
    protected:
        int lev, exp;               //livello, esperienza
        int pot;                    //numero di pozioni trasportate
        Arma inventario[MAX_ITEM];  //armi trasportate ma non equipaggiate
    public:
        Giocatore();
        void setStats();            //dà i valori iniziali alle statistiche
        void levelup();             //metodo da chiamare quando passa di livello il giocatore

};

#endif // GIOCATORE_HPP_INCLUDED
