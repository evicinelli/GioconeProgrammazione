#include <iostream>
#include "GeneratoreLivelli.hpp"
#include "GestoreLivelli.hpp"
using namespace std;

int main() {
	// TODO: il livello va creato tramite gestoreLivelli
	/** Livello* l= new Livello(5);
	
	GeneratoreLivelli g=GeneratoreLivelli();
	g.inizializzaVettColl(l);
	g.stampaCollegamenti(l);
	cout<<" Inizializzazione completata "<<endl;

	// test
	g.link(1,2, l);
	g.link(2,9, l);
	g.link(2,9, l);
	g.link(2,4, l);
	g.link(4,1, l);

	printf("Popolo livello a indirizzo %p\n", l);
	g.popolaLivello(l);


	

	printf("Situazione dei collegamenti per il livello %d\n", l->getNStanze());
	g.stampaCollegamenti(l); */

	GestoreLivelli gest = GestoreLivelli();
	printf("\n\n\n");
	gest.creaLivello(2);

	printf("\n\n\n");
	gest.creaLivello(10);
	printf("\n\n\n");
	gest.creaLivello(37);

	gest.dumpLevelList();
	return 0;
}
