#include <iostream>
#include "GeneratoreLivelli.hpp"
#include "GestoreLivelli.hpp"

using namespace std;

int main()
{
/*
   Livello* l= new Livello(25);
   GeneratoreLivelli g=GeneratoreLivelli();
    cout<<"____________________"<<endl;
g.stampaCollegamenti(l);
    g.popolaLivello(l);

     g.stampaCollegamenti(l);*/

	GestoreLivelli gestore = GestoreLivelli();
	gestore.dumpLevelList();
	gestore.creaLivello(gestore.getLevN() + 1);

   return 0;
}
