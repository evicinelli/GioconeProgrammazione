#include <iostream>
#include "GeneratoreLivelli.hpp"
#include "GestoreLivelli.hpp"
using namespace std;

int main()
{
    //Creazione di un solo livello 3
/**
    Livello* l= new Livello(3);
    GeneratoreLivelli g=GeneratoreLivelli();
    cout<<"____________________"<<endl;
    g.stampaCollegamenti(l);
    g.popolaLivello(l);
    g.stampaCollegamenti(l);
*/

    //Creazione e collegamento fino al terzo livello

    GestoreLivelli gestore = GestoreLivelli();

	gestore.creaLivello(gestore.getLevN() + 1);

	gestore.creaLivello(gestore.getLevN() + 1);

	gestore.creaLivello(gestore.getLevN() + 1);

	gestore.creaLivello(gestore.getLevN() + 1);

    gestore.stampaCollegamentiLivelli();
    //cout<<gestore.getLevN();

   return 0;
}
