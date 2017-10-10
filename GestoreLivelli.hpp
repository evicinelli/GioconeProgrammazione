#include "GeneratoreLivelli.hpp"
#include "Livello.hpp"

#ifndef GESTORELIVELLI_HPP_INCLUDED
#define GESTORELIVELLI_HPP_INCLUDED

class GestoreLivelli
{
protected:
    /**
    Struttura che contiene la lista dei livelli del gioco.
    */
    struct lista
    {
        Livello* l;
        lista* next;
    };
    typedef lista* ptr_listaLiv;

    /**Testa della lista */
    ptr_listaLiv head;
    /**Livello corrente cioè quello in cui il giocatore si trova*/
    int livCorrente;
    /**Massimo livello in cui il giocatore si è trovato */
    int maxLiv;
    /**Oggetto di generatore livelli */
    GeneratoreLivelli generatore;

public:

    public:

    /**
    Costruttore della classe crea un oggetto di classe GeneratoreLivelli, inizializza il
    puntatore alla testa della lista a null, crea il primo livello, inizializza livello corrente e livello
    massimo a uno.

    */
    GestoreLivelli();

    /** Metodo che incrementa di uno il livello corrente*/
    void passaLivSucc();

    /** Metodo che decrementa di uno il livello corrente*/
    void passaLivPrec();

    /** Metodo che aggiunge livello in coda alla lista dei livelli */
    void aggiungiLivello(Livello *l);

    /**
    Metodo che per prima cosa crea un livello avente il numero di stanze pari al numero passato come parametro al metodo,
    in seguito utilizzando il generatore di livelli viene popolato il livello,
    viene aggiunto tale livello alla lista di gestoreLivelli, viene richiamato passaLivSucc che aggiorna la variabile livCorrente,
    infine se il livello appena creato non è il primo viene collegato il livello corrente a quello precedente attraverso il metodo di GeneratoreLivelli.
    */
    Livello* creaLivello(int n);

    /**
    Metodo privato che ricerca nella lista un livello con un determinato id e lo restituisce.
    */
    Livello* getLevelById(int id);

    /**
    Metodo getter che ritorna maxLiv
    */
    int getLevN();

    /**
    Metodo getter che ritorna livello corrente
    */
	int getLivello();

	/**
	Metodo che restituisce il primo livello cioè il livello contenuto nel primo elemento della lista, quindi quello puntato da head
	*/
	Livello* getInizio();

	/**
	Metodo di stampa utilizzato solo a fini di debug.
	*/
    void stampaCollegamentiLivelli();


};


#endif // GESTORELIVELLI_HPP_INCLUDED
