#include "GeneratoreLivelli.hpp"
#include "Livello.hpp"

#ifndef GESTORELIVELLI_HPP_INCLUDED
#define GESTORELIVELLI_HPP_INCLUDED

class GestoreLivelli
{
protected:

    struct lista
    {
        Livello* l;
        lista* next;
    };
    typedef lista* ptr_listaLiv;

    ptr_listaLiv head;
    int livCorrente;
    int maxLiv;
    GeneratoreLivelli generatore;

public:
    GestoreLivelli();

    /** incrementa di uno il livello corrente*/
    void passaLivSucc();

    /** decrementa di uno il livello corrente*/
    void passaLivPrec();

    /** Aggiungi livello in coda alla lista dei livelli */
    void aggiungiLivello(Livello *l);

    /**
    	-chiama il costruttore di livello
    	-chiama metodo popolaLivello di GeneratoreLivelli passando il puntatore al livello
    	-aggiungi il livello in coda alla lista dei livelli di GestoreLivelli
    	-cambia il livello corrente
    */
    Livello* creaLivello(int n);

    // Stampa la lista dei livelli
  //  void dumpLevelList();

    // Ritorna il massimo numero di livelli
    int getLevN();

	int getLivello();

	Livello* getInizio();
    /**
    Ritorna livello a partire da id
    */
    Livello* getLevelById(int id);

    void stampaCollegamentiLivelli();

};


#endif // GESTORELIVELLI_HPP_INCLUDED
