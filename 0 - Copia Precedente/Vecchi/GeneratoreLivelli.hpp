#include "Stanza.hpp"
#include "Livello.hpp"
#include <iostream>
#include <stdio.h>
using namespace std;

#ifndef GENERATORELIVELLI_HPP_INCLUDED
#define GENERATORELIVELLI_HPP_INCLUDED
class GeneratoreLivelli{
private:
     /**
    -crea vettore delle stanze
    -crea collegamenti
    */

    void riempiVettStanze(Livello* l);
    void riempiVettCollegamenti(Livello* l, int maxLink);

public:

	/*
	Costruisce il livello, inizializzando in manera coerente 
	le strutture dati del livello
	*/
   void popolaLivello (Livello* l);

};


#endif // GENERATORELIVELLI_HPP_INCLUDED
