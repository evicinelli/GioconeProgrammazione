#ifndef GIOCATORE_HPP_INCLUDED
#define GIOCATORE_HPP_INCLUDED
#define MAX_ITEM 3
#define MAX_CLASSES 3
#include "Personaggio.hpp"
#include "Giocatore.hpp"

class Giocatore : public Personaggio
{
    protected:
        int nextLevExp;						//esperienza per il livello successivo
        int pot;							//numero di pozioni trasportate
        int oro;							//oro trasportato
        Arma inventario[MAX_ITEM];			//armi trasportate ma non equipaggiate
    public:
        Giocatore();
        void classChosen(int sel);			//in base alla classe selezionata determina le statistiche del giocatore
        int getOro();
        int getNextExp();
        int getPot();
        void addPot();
        Arma getInv(int n);
        void setOro(int o);
        void setInv(int n, Arma a);
        void addOro(int o);
        void addExp(int e);
        void levelup(int stat);				//metodo da chiamare quando passa di livello il giocatore; "stat" viene passato da tastiera quando compare la schermata di passaggio di livello
        int cambioArma(int pos);			//scambia l'arma equipaggiata con una nell'inventario
        void scartaArma(int pos);			//scarta una delle armi nell'inventario
		void vendiArma(int pos);			//vende una delle armi a un venditore
        int libInventario();				//restituisce la prima posizione libera di inventario, -1 se è piena
        int usaPozione();					//usa una pozione e ritorna il numero di hp recuperati
        void vendiPot(int prezzo);			//vendi la pozione al venditore

};

#endif // GIOCATORE_HPP_INCLUDED
