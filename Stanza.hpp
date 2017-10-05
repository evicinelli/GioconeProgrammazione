#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include "Mostro.hpp"
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

    int getPorta(int n);
    
    int getColl(int n);
    
    void setId(int n);
    
    int getId();
    
    int getLibero();
    
    void riempiMatrice(int nLiv, int coll [4]);

    Mostro* getMonster(int i);

    int getHowManyMonsters();

    int getSpot(int i, int j);

private:

    void mettiMuriContorno();

    void mettiPorte(int coll[4]);

    bool existPorta(int n);

    void link(int partenza, int arrivo, bool type);

    void inserisciVia();

    void mettiMuri();

    void riempiMuri(int x, int y);

    void trasformaInterni();

    int nVicini(int y, int x);

    void mettiMostri(int livello);

    void mettiBauli(int livello);

    void mettiVenditori(int livello);
    
    void trasformaStrada();

	void liberaPorte();
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
