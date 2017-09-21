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

private:

    bool contrCorrettezzaMuri (int r, int c);

};




#endif // STANZA_HPP_INCLUDED
