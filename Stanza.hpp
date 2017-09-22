#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
using namespace std;

#ifndef STANZA_HPP_INCLUDED

#define STANZA_HPP_INCLUDED

class Stanza{

protected:
    int matrice [18][18];
    int nMaxMostri;
    int nMaxBauli;
    int nMaxVenditori;
    int nMaxMuri;
    int nPorte; 
    int porte[4]; //Giulia se per te è scomodo gestire le porte così (lo è anche per me), lo tolgo e lo metto come dici tu
public:

	/**
	Crea la stanza di id n
	*/
	Stanza();


    void inizializzaMatrice(int m[18][18]);

    void stampaMatriceInizializzata (int m[18][18]);

    void stampaMatrice (int m[18][18]);

    void getMatrice(int m[18][18]);

    void setMatrice(int m[18][18]);
	
    void riempiMatrice(int nLiv, int coll [4]);
    
    void riempiMatrice2(int nLiv, int coll [4]);

private:

	void mettiMuriContorno();
	
	void mettiPorte(int coll[4]);
	
	bool existPorta(int n);
	
	int getPorta(int n);
	
	void link(int partenza, int arrivo, int type);
	
	void inserisciVia();
	
	void mettiMuri();

    bool contrCorrettezzaMuri (int r, int c);

};




#endif // STANZA_HPP_INCLUDED
