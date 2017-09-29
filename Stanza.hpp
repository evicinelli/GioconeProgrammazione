#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
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
    int nMaxBauli;
    int nMaxVenditori;
    int nMaxMuri;
    int porte[4];
    int collegamento[4];
    bool visited;
    int id;
    int libero; //mi indica un punto libero nella prima colonna, nel quale sicuramente non ci sono muri 
public:

	/*
	Crea la stanza di id n
	*/
	Stanza();

	int getDimensione();

	void visit();
	
	bool isVisited();
	
    void inizializzaMatrice(int m[MAXDIM][MAXDIM]);

    void stampaMatriceInizializzata (int m[MAXDIM][MAXDIM]);

    void stampaMatrice (int m[MAXDIM][MAXDIM]);

    void getMatrice(int m[MAXDIM][MAXDIM]);

    void setMatrice(int m[MAXDIM][MAXDIM]);

    int getColl(int n);
    
    void setId(int n);
    
    int getId();
    
    int getLibero();
    
    void riempiMatrice(int nLiv, int coll [4]);


private:

    void mettiMuriContorno();

    void mettiPorte(int coll[4]);

    bool existPorta(int n);

    int getPorta(int n);

    void link(int partenza, int arrivo, bool type);

    void inserisciVia();

    void mettiMuri();

    void riempiMuri(int x, int y);

    void trasformaInterni();

    int nVicini(int y, int x);

    void mettiMostri(int livello);

    void mettiBauli(int livello);

    void mettiVenditori(int livello);

};




#endif // STANZA_HPP_INCLUDED
