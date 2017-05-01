#include <iostream>
#include "GeneratoreLivelli.hpp"
using namespace std;

int main() {
	Livello* l= new Livello(10);
	GeneratoreLivelli g=GeneratoreLivelli();
	g.inizializzaVettColl(l);
	g.stampaCollegamenti(l);

	// TODO: il livello va creato tramite generatoreLivelli

	

	cout<<" Inizializzazione completata"<<endl;

	g.link(9,7,l);
	g.link(1,5,l);
	g.link(4,6,l);
	g.link(2,3,l);

	g.stampaCollegamenti(l);

	return 0;
}
