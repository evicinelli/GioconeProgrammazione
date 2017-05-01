#include "GeneratoreLivelli.hpp"
#include "Livello.hpp"

#ifndef GESTORELIVELLI_HPP_INCLUDED
#define GESTORELIVELLI_HPP_INCLUDED

class GestoreLivelli{
protected:
    struct lista{
        Livello l;
        lista* next;
    };typedef lista* ptr_listaLiv;

    ptr_listaLiv head;

    int livCorrente;

    GeneratoreLivelli generatore;

public:
    GestoreLivelli();
   
    /** incrementa di uno il livello corrente*/
    void passaLivSucc();

    /** decrementa di uno il livello corrente*/
    void passaLivPrec();
   
    /**
    Aggiungi livello in coda alla lista dei livelli
    */
    void aggiungiLivello();

    /**
        -chiama il costruttore di livello
        -chiama metodo popolaLivello di GeneratoreLivelli passando il puntatore al livello
        -cambia il livello corrente
        -aggiungi il livello in coda alla lista dei livelli di GestoreLivelli
    */
    Livello creaLivello(int n);



};



#endif // GESTORELIVELLI_HPP_INCLUDED
