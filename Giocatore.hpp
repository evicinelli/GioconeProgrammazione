#ifndef GIOCATORE_HPP_INCLUDED
#define GIOCATORE_HPP_INCLUDED
#define MAX_ITEM 3
#define MAX_POTION 10
#include "Personaggio.hpp"
#include "Giocatore.hpp"

class Giocatore : public Personaggio
{
    protected:
        int nextLevExp;               //esperienza per il livello successivo
        int pot;                    //numero di pozioni trasportate
        int oro;                    //oro trasportato
        Arma inventario[MAX_ITEM];  //armi trasportate ma non equipaggiate
    public:
        Giocatore();
        int getOro();
        int getNextExp();
        int getPot();
        void addPot();
        Arma getInv(int n);
        void setOro(int o);
        void setInv(int n, Arma a);
        void addOro(int o);
        void addExp(int e);
        void levelup(int stat);             //metodo da chiamare quando passa di livello il giocatore; "stat" viene passato da tastiera quando compare la schermata di passaggio di livello
        void cambioArma(int pos);           //scambia l'arma equipaggiata con una nell'inventario
        void scartaArma(int pos);           //scarta una delle armi nell'inventario
        void usaPozione();
        void morte();                       //metodo forse non necessario; dovrebbe chiamare la schermata di sconfitta
};

#endif // GIOCATORE_HPP_INCLUDED
