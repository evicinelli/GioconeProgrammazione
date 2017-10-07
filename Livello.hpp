#include "Stanza.hpp"
#include "Collegamento.hpp"
#include <stdlib.h> //per malloc
#include <iostream>
using namespace std;

#ifndef LIVELLO_HPP_INCLUDED
#define LIVELLO_HPP_INCLUDED
class Livello
{
protected:
    /** numero di stanze del livello*/
    int nStanze;

    /** vettore contenente puntatori alle stanze del livello */
    Stanza* vettStanze;


    /**array dei collegamenti tra le stanze del livello*/
    Collegamento* vettColl;

public:
    /**
    Costruttore del livello:
        1- inizializza il numero di stanze del livello

        2-alloca il vettore delle stanze cha avrà dimensione pari
        al numero delle stanze+2 perchè nell'indice nStanze ci sarà l'ultima
        stanza del livello precedente e nell'indice nStanze+1 ci sarà il
        puntatore alla prima stanza del livello successivo

        3-alloca il vettore dei collegamenti tra le stanze che avrà dimensione
        pari al numero di stanze

        4-inizializza id delle prime nStanze del vettore delle stanze
    */
    Livello (int n);

    /**
    Metodo che si occupa di richiamare il metodo della stanza per la creazione pseudocasuale della mappa della stanza
    passando come parametro a tale metodo i collegamenti della stanza che tengono conto del cambio
    di livello che in fase di generazione del livello non vengono calcolati, così da mettere le porte della stanza nel
    modo giusto.
    */
    void setMatriceStanza(int id);

    /**
     Metodo che restituisce il puntatore alla stanza in base all'intero passato come parametro
    */
    Stanza getStanza(int id);

    /** Metodo che dato un id ed un puntatore ad una stanza il metodo setta la matrice della stanza all'indice id del vettore
     delle stanze del livello con la matrice della stanza passata come parametro al metodo.
    */
    void setStanza(int id, Stanza* s);

    /**Metodo che dato un id e un puntatore a collegamento il metodo setta per prima cosa l'id del collegamento che si trova all'indice
    id del vettore dei collegamenti del livello in base all'id del collegamento passato come parametro, poi inizializza le
    direzioni di tale collegamento tutte a -1 (assenza di collegamento)
    */
    void setCollegamento(int id, Collegamento* c);

    /**
    Metodo che restituisce nell'array adiacenze passato come parametro l'array delle adiacenze del collegamento avente id pari a quello
    passato come parametro
    */
    void getAdiacenze(int id, int adiacenze [4]);


    /**
    Metodo che restituisce la stanza a nord della stanza corrente salvata nell'intero passato come parametro in id
    */
    Stanza vaiNord(int id);

    /**
    Metodo che restituisce la stanza a sud della stanza corrente salvata nell'intero passato come parametro in id
    */
    Stanza vaiSud(int id);

    /**
    Metodo che restituisce la stanza a ovest della stanza corrente salvata nell'intero passato come parametro in id
    */
    Stanza vaiOvest(int id);

    /**
    Metodo che restituisce la stanza a est della stanza corrente salvata nell'intero passato come parametro in id
    */
    Stanza vaiEst(int id);

    /**
    Ritorna il numero delle stanze del livello
    */
    int getNStanze();

    /**
    Metodo che si occupa di modificare il collegamento della stanza di partenza (sPartenza) nell'array delle direzioni
    in base alla direzione passata come paramentro attribuendo a tale elemento l'id della stanza di arrivo (sArrivo)
    */
    void collegaStanza(int sPartenza, int sArrivo, int direz);

    /**
    Metodo che dato l'id della stanza modifica il campo visit della stanza che si trova all'indice id del vettore delle
    stanze del livello
    */
    void visitStanza(int id);

    /**
     Metodo che fa la stessa cosa di getStanza(int id) ma invece di restituire un oggetto restituisce un puntatore all'oggetto
     stanza questo perchè i metodi per collegare le stanze richiedono un puntatore.
    */
    Stanza* getPointerToStanza(int id);

    /**
    Metodo che restituisce il vettore dei collegamenti utilizzato solo a fini di debug
    */
    Collegamento* getVettColl();


};


#endif // LIVELLO_HPP_INCLUDED
