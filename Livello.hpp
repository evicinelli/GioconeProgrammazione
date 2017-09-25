#include "Stanza.hpp"
#include "Collegamento.hpp"
#include <stdlib.h> //per malloc
#include <iostream>
using namespace std;

#ifndef LIVELLO_HPP_INCLUDED
#define LIVELLO_HPP_INCLUDED
class Livello{
protected:
		/** numero di stanze del livello*/
	int nStanze;

		/** vettore contenente puntatori alle stanze del livello */
	Stanza* vettStanze;


		/**array dei collegamenti tra le stanze del livello*/
	Collegamento* vettColl;
public:
	/** Costruttore del livello:
			-inizializza il numero di stanze del livello
			-alloca il vettore delle stanze cha avrà dimensione pari
			al numero delle stanze+2 perchè nell'indice nStanze ci sarà l'ultima
			stanza del livello precedente e nell'indice nStanze+1 ci sarà il
			puntatore alla prima stanza del livello successivo (inizialmente
			inizializzata a null)
			-alloca il vettore dei collegamenti tra le stanze che avrà dimensione
			pari al numero di stanze
		*/
	Livello (int n);

		/**
		Metodo che restituisce il puntatore alla stanza in base all'intero passato
		come parametro
		*/
        
        void setMatriceStanza(int id);
        
	Stanza getStanza(int id);

	void setStanza(int id, Stanza* s);


	void setCollegamento(int id, Collegamento* c);

		/**
		Metodo che restituisce nell'array adiacenze passato come parametro
		l'array delle adiacenze in base all'intero passato come parametro in id
		*/
	void getAdiacenze(int id, int adiacenze [4]);

		/**
		Imposta il vettore delle adiacenze della stanza in base all'id
		*/
	void setAdiacenze(int id, int a [4]);

		/**
		Metodo che restituisce la stanza a nord della stanza corrente salvata
		nell'intero passato come parametro in id
		*/
	Stanza vaiNord(int id);

		/**
		Metodo che restituisce la stanza a sud della stanza corrente salvata
		nell'intero passato come parametro in id
		*/
	Stanza vaiSud(int id);

		/**
		Metodo che restituisce la stanza a ovest della stanza corrente salvata
		nell'intero passato come parametro in id
		*/
	Stanza vaiOvest(int id);

		/**
		Metodo che restituisce la stanza a est della stanza corrente salvata
		nell'intero passato come parametro in id
		*/
	Stanza vaiEst(int id);

		/**
		Ritorna il numero delle stanze del livello
		*/
	int getNStanze();
    void dumpRoomList();
	void collegaStanza(int sPartenza, int sArrivo, int direz);
    Stanza* getPointerToStanza(int id);

    Collegamento* getVettColl();

};


#endif // LIVELLO_HPP_INCLUDED
