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

    PRECONDIZIONE NON CONTROLLATA: PUNTATORE A LIVELLO NON NULLO
    -crea vettore delle stanze
    -crea collegamenti
    */

    void riempiVettStanze(Livello* l);
    void riempiVettCollegamenti(Livello* l, int maxLink);
    int controlloLink(int s,int direzione,int dir[4], int stanze);
    //void inizializzaVettColl(Livello* l);
    void link(int da, int a, Livello* l);
    void controllaAvail(bool avail[4],Livello* l);
    void controllaAvail2 (bool avail[4],Livello* l);


public:
    GeneratoreLivelli();
    /**
    Costruisce il livello, inizializzando in maniera coerente
    le strutture dati del livello
    */

    void popolaLivello (Livello* l);
    void stampaCollegamenti(Livello* l);
    void inizializzaVettColl(Livello* l);
// Logica del collegamento al livello precedente
    void collegaLivelloPrec(Livello* l1, Livello* l2);

};


#endif // GENERATORELIVELLI_HPP_INCLUDED
