#include "Stanza.hpp"
#include <stdlib.h> //per malloc

#ifndef LIVELLO_HPP_INCLUDED
#define LIVELLO_HPP_INCLUDED
class Livello{
protected:
        /** numero di stanze del livello*/
        int nStanze;

        /** vettore contenente puntatori alle stanze del livello */
        Stanza* vettStanze;

        /**
        -l'id è l'indice del puntatore alla stanza contenuto in vettStanze
        -nell'array direzioni:
                direzioni[0]-> N
                direzioni[1]-> S
                direzioni[2]-> O
                direzioni[3]-> E
        */
        struct collegamenti{
            int id;
            int direzioni[4];
        }; typedef collegamenti* prt_coll;

        /**array dei collegamenti tra le stanze del livello*/
        prt_coll vettColl;
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
        Metodo che restituisceil puntatore alla stanza in base all'intero passato
        come parametro
        */
        Stanza getStanza(int id);

        void setStanza(int id, Stanza* s);

        /**
        Metodo che restituisce nell'array adiacenze passato come parametro
        l'array delle adiacenze in base all'intero passato come parametro in id
        */
        void getAdiacenze(int id, int adiacenze [4]);

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
};


#endif // LIVELLO_HPP_INCLUDED
