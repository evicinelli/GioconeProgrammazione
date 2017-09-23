#include <iostream>
#include "GeneratoreLivelli.hpp"
#include "GestoreLivelli.hpp"
using namespace std;

int main()
{
/*
    //Creazione di un solo livello 3


    //Creazione e collegamento fino al terzo livello

    GestoreLivelli gestore = GestoreLivelli();

	gestore.creaLivello(gestore.getLevN() + 1);

	gestore.creaLivello(gestore.getLevN() + 1);

	gestore.creaLivello(gestore.getLevN() + 1);

	gestore.creaLivello(gestore.getLevN() + 1);

	gestore.creaLivello(gestore.getLevN() + 1);

	gestore.creaLivello(gestore.getLevN() + 1);

	gestore.creaLivello(gestore.getLevN() + 1);

	gestore.creaLivello(gestore.getLevN() + 1);

	gestore.creaLivello(gestore.getLevN() + 1);

    gestore.stampaCollegamentiLivelli();

    //cout<<gestore.getLevN();
*/

    Stanza* st= new Stanza();
    int c[4]={-1,2,9,-2};
    st->riempiMatrice(100,c);
    int m [18][18];
    st->getMatrice(m);
    st->stampaMatrice(m);

   return 0;
}
