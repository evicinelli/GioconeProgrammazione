#ifndef GIOCATORE_HPP_INCLUDED
#define GIOCATORE_HPP_INCLUDED
#define MAX_ITEM 3
#define MAX_POTION 10
#include "Personaggio.hpp"

class Giocatore : public Personaggio
{
    protected:
        int nextLevExp;               //esperienza per il livello successivo
        int pot;                    //numero di pozioni trasportate
        int oro;                    //oro trasportato
        Arma inventario[MAX_ITEM];  //armi trasportate ma non equipaggiate
    public:
        Giocatore();
        void levelup(int stat);             //metodo da chiamare quando passa di livello il giocatore; "stat" viene passato da tastiera quando compare la schermata di passaggio di livello
        void morte();                       //metodo forse non necessario; dovrebbe chiamare la schermata di sconfitta
};

#endif // GIOCATORE_HPP_INCLUDED
