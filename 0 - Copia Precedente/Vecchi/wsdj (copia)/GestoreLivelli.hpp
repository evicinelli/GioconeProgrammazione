#include "GeneratoreLivelli.hpp"
#include "Livello.hpp"

#ifndef GESTORELIVELLI_HPP_INCLUDED
#define GESTORELIVELLI_HPP_INCLUDED

class GestoreLivelli{
protected:
    struct lista{
        Livello l;
        lista* next;
    };typedef struct lista* ptr_listaLiv;

    ptr_listaLiv head; // lista dei livelli
    int livCorrente; // id livello corrente
    int livMax; // numero di livelli creati
    GeneratoreLivelli generatore; // oggetto generatore dei livelli
    
    
    /**
    Deve collegare il livello precedente <-> corrente
    */
public:
	void linkLivelli();

//public:
    GestoreLivelli();
   
    /** incrementa di uno il livello corrente*/
    void passaLivSucc();

    /** decrementa di uno il livello corrente*/
    void passaLivPrec();
   
    /**
    Aggiungi livello in coda alla lista dei livelli
    */
    void aggiungiLivello();

	/***/
	Livello* getLivello (int id);
	
    /**
        -chiama il costruttore di livello
        -chiama metodo popolaLivello di GeneratoreLivelli passando il puntatore al livello
        -cambia il livello corrente
        -aggiungi il livello in coda alla lista dei livelli di GestoreLivelli
		- ricordarsi di inizializzare stanza di indice n nel livello precedente (collegarsi al livello precedente) - vedi fogli
    */
    Livello* creaLivello(int n);



};



#endif // GESTORELIVELLI_HPP_INCLUDED
