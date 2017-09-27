#include <iostream>
#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "GeneratoreLivelli.hpp"
#include "GestoreLivelli.hpp"
#include "Drawer.hpp"
using namespace std;

int main()
{

    //Creazione di un solo livello 3


    //Creazione e collegamento fino al terzo livello

	/*
    GestoreLivelli gestore = GestoreLivelli();
  /*  GestoreLivelli gestore = GestoreLivelli();

>>>>>>> Stashed changes
	cout<<"Livello 2"<<endl;
	gestore.creaLivello(gestore.getLevN() + 1);
	cout<<"Livello 3"<<endl;
	gestore.creaLivello(gestore.getLevN() + 1);
	cout<<"Livello 4"<<endl;
	gestore.creaLivello(gestore.getLevN() + 1);
	gestore.creaLivello(gestore.getLevN() + 1);

	gestore.creaLivello(gestore.getLevN() + 1);

<<<<<<< Updated upstream
	gestore.creaLivello(gestore.getLevN() + 1);

	gestore.creaLivello(gestore.getLevN() + 1);

	gestore.creaLivello(gestore.getLevN() + 1);

	gestore.creaLivello(gestore.getLevN() + 1);

	gestore.creaLivello(gestore.getLevN() + 1);


    gestore.stampaCollegamentiLivelli();

    //cout<<gestore.getLevN();
	*/
	
	Stanza* st= new Stanza();
	Giocatore* player=new Giocatore();
    int c[4]={-1,2,9,-2};
    st->riempiMatrice(50,c);
	Drawer d = Drawer(st, player);
	
	
	return 0;
}

