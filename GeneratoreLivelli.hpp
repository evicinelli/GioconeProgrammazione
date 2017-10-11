#include "Stanza.hpp"
#include "Livello.hpp"
#include "Collegamento.hpp"
#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

#ifndef GENERATORELIVELLI_HPP_INCLUDED
#define GENERATORELIVELLI_HPP_INCLUDED
class GeneratoreLivelli
{
private:
    /**
    Metodo richiama il metodo setMatriceStanza(int id) di Livello per ogni stanza del vettore delle stanze tranne le ultime due le quali corrispondono alle
    stanze del livello precedente e successivo.
    */
    void riempiVettStanze(Livello* l);

    /**
    Metodo che si occupa di creare randomicamente i collegamenti tra le stanze di un livello, è diviso in due parti.
    Nella prima parte il metodo si occupa di collegare una volta tutte le stanze così da creare almeno un percorso per visitare tutte le stanze.
    Nella seconda parte il metodo si occupa di collegare un'altra volta le stanze in modo da garantire il doppio collegamento.
    */
    void riempiVettCollegamenti(Livello* l, int maxLink);

    /**
    Metodo che controlla le direzioni nel caso esse non siano ammissibili e infine ne restituisce una ammissibile, essa esiste sempre perchè
    le stanze passate come input al metodo sono due stanze settate a true nel vettore avail e quindi disponibili.
    */
    int controlloLink(int s,int direzione,int dir[4], int stanze);

    /**
    Metodo che si occupa di scegliere le direzioni dei collegamenti delle stanze e di collegarle con il metodo
    collegaStanza(int sPartenza, int sArrivo, int direz)
    */
    void link(int da, int a, Livello* l);

    /**
    Metodo che controlla nella prima parte del riempiVettCollegamenti(Livello* l, int maxLink) la disponibilità delle stanze
    */
    void controllaAvail(bool avail[4],Livello* l);

    /**
    Metodo che controlla nella seconda parte del riempiVettCollegamenti(Livello* l, int maxLink) la disponibilità delle stanze
    */
    void controllaAvail2 (bool avail[4],Livello* l);

    /**
    Metodo cheinizializza i collegamenti del livello settando tutte le adiacenze a -1 e settando il campo id.
    */
    void inizializzaVettColl(Livello* l);


public:
    /**
    Costruttore che inizializza il random che useremo in seguito.
    */
    GeneratoreLivelli();

    /**
    Metodo per prima cosa inizializza il vettore collegamenti mettendo poi vengono creati i collegamenti e riempite le stanze.
    */
    void popolaLivello (Livello* l);

    /**
    Metodo utilizzato solo a fini di debug
    */
    void stampaCollegamenti(Livello* l);



    /**
    Metodo che si occupa di collegare i vari livelli del gioco, il livello corrente dopo esser stato popolato viene
    collegato con il livello precedente
    */
    void collegaLivelloPrec(Livello* l1, Livello* l2);

};


#endif // GENERATORELIVELLI_HPP_INCLUDED
