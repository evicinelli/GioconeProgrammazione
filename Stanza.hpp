#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#define MAXDIM 20
#define MINDIM 14
using namespace std;

#ifndef STANZA_HPP_INCLUDED

#define STANZA_HPP_INCLUDED

class Stanza{

protected:
    int matrice [20][20];
    int dimensione;
    int nMaxMostri;
    int nMaxBauli;
    int nMaxVenditori;
    int nMaxMuri;
    int nPorte; 
    int porte[4]; //Giulia se per te è scomodo gestire le porte così (lo è anche per me), lo tolgo e lo metto come dici tu
    int libero; //mi indica un punto libero nella prima colonna, nel quale sicuramente non ci sono muri 
public:

	/**
	Crea la stanza di id n
	*/
	Stanza();


    void inizializzaMatrice(int m[MAXDIM][MAXDIM]);

    void stampaMatriceInizializzata (int m[MAXDIM][MAXDIM]);

    void stampaMatrice (int m[MAXDIM][MAXDIM]);

    void getMatrice(int m[MAXDIM][MAXDIM]);

    void setMatrice(int m[MAXDIM][MAXDIM]);
	
    void riempiMatrice(int nLiv, int coll [4]);
    

private:

	void mettiMuriContorno();
	
	void mettiPorte(int coll[4]);
	
	bool existPorta(int n);
	
	int getPorta(int n);
	
	void link(int partenza, int arrivo, int type);
	
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
