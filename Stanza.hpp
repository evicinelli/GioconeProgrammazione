#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include "Mostro.hpp"
#include "Forziere.hpp"
#define MAXDIM 24	
#define MINDIM 20
using namespace std;

#ifndef STANZA_HPP_INCLUDED
#define STANZA_HPP_INCLUDED

class Stanza
{

protected:
    int matrice [MAXDIM][MAXDIM];
    int dimensione;
    int nMaxMostri;
    int nRealMostri;
    int nMaxBauli;
    int nMaxVenditori;
    int nMaxMuri;
    int porte[4];
    int collegamento[4];
    bool visited;
    int id;
    int libero; //mi indica un punto libero nella prima colonna, nel quale sicuramente non ci sono muri 
    Mostro* monsters[6]; /* Riferimenti ai mostri della stanza */
public:

    //crea la stanza
    Stanza();

	//restituisce la dimensione effettiva della stanza
    int getDimensione();

	//segna come visitata la stanza
    void visit();
    
    //la stanza è già stata visitata?
    bool isVisited();
    
    //setta la matrice della stanza con tutti -2
    void inizializzaMatrice(int m[MAXDIM][MAXDIM]);
	
	//stampa la matrice della stanza a caratteri
    void stampaMatrice (int m[MAXDIM][MAXDIM]);

	//riempie il parametro con la matrice della stanza
    void getMatrice(int m[MAXDIM][MAXDIM]);

	//cambia la matrice della stanza con il parametro 
    void setMatrice(int m[MAXDIM][MAXDIM]);

	//data la direzione, ritorna la coordinata variabile della porta in quella direzione, se non c'è la porta ritorna -1
    int getPorta(int n);
    
    //data la direzione ritorna l'id della a cui è collegata 
    int getColl(int n);
    
    //imposta l'id della stanza
    void setId(int n);
    
	//ritona l'id della stanza
    int getId();
    
    //ritorna la coordinata x nell'ultima colonna, dove sicuramente la matrice è -1
    int getLibero();
    
	//riempie la matrice della stanza
    void riempiMatrice(int nLiv, int coll [4]);

	//ritorna l'i-esimo mostro
    Mostro* getMonster(int i);

	//ritorna quanti mostri ci sono nella stanza
    int getHowManyMonsters();

	//ritorna il valore della matrice[i][j]
    int getSpot(int i, int j);
	
	//imposta il valore della matrice[i][j]
    void setSpot(int i, int j, int value);

private:

	//mette i muri come contorno della stanza
    void mettiMuriContorno();
	
	//dati i collegamenti mette le porte nella stanza (random) 
    void mettiPorte(int coll[4]);

	//true se esiste la porta nella direzione n, false altrimenti
    bool existPorta(int n);

	//collega con una strada casuale porta 0-1 se type=1, 2-3 se type=0 
    void link(int partenza, int arrivo, bool type);

	//inserisce una via tra i 4 lati della stanza
    void inserisciVia();

	//mette i muri dentro la stanza
    void mettiMuri();

	//segna come posti liberi (-1) tutti  quelli raggiungibili
    void riempiMuri(int x, int y);

	//trasforma i -2 (punti interni) in 0 (muri)
    void trasformaInterni();

	//ritorna quanti muri o mostri ci sono vicini alla posizione
    int nVicini(int y, int x);

	//mette i mostri nella stanza
    void mettiMostri(int livello);

	//mette i bauli nella stanza
    void mettiBauli(int livello);

	//mette i venditori nella stanza
    void mettiVenditori(int livello);

	//libera il posto vicino alle porte (e il punto di partenza del giocatore)
	void liberaPorte();

    //Trasforma tutti i -3 (strada dovuta a liberaPorte) a -1 (vuoto)
    void normalizza();
};




#endif // STANZA_HPP_INCLUDED

 /**
        -3 -> strada
        -2 -> interno
        -1 -> esterno
        0 -> muro : i muri non possono essere messi sulle porte e non possono essere lunghi quanto un lato della stanza perchè deve essere
                    possibile passare da una parte all'altra della stanza
        1 -> mostro : in base al numero max di mostri della stanza
        2 -> venditore : raro
        3 -> baule : raro
        4 -> porta : le posizioni delle porte (numero di porte è in base al numero di collegamenti) vengono scelte in base al lato dove sono
                     presenti i collegamenti, in qualsiasi riquadro del lato corrispondente
    */
