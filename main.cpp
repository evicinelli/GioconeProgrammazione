#include <iostream>
#include <stdio.h> 
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
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
	/*
    srand(time(0));
    struct listaStanze {
	   Stanza *stanza;
	   struct listaStanze *next;
	}; 
	struct listaStanze *r;
	int liv=0;
	int c[4]={-1,2,9,-2};
	int m [MAXDIM][MAXDIM];
	int mo[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int b[5]={0,0,0,0,0};
	int v[10]={0,0,0,0,0,0,0,0,0,0};
	int mostri=0, bauli=0, vend=0;
	int dim=10000;
	
	struct listaStanze *p;
	r=NULL;
	for (int i=0;i<dim; i++){
		p=r;
        r=new listaStanze;  
        r->stanza=new Stanza();
        r->next=p;
	}
	for(int i=0; i<dim; i++){;
		r->stanza->inizializzaMatrice(m);
		liv=(rand()%100)+1;
		r->stanza->riempiMatrice(liv,c);
		r->stanza->getMatrice(m);
		//r->stanza->stampaMatrice(m);
		liv=0;
		for(int k=1; k<16; k++){
			for(int j=1; j<16; j++){
				if (m[k][j]==1) mostri++;
				if (m[k][j]==3) bauli++;
				if (m[k][j]==2) vend++;
			}
		}
		if (mostri<15)
			mo[mostri]++;
		if (bauli<5)
			b[bauli]++;
		if (vend<10)
			v[vend]++;
		mostri=0;
		bauli=0;
		vend=0;
		r=r->next;
	}
	for(int i=0; i<15; i++)
		cout << i << " mostri:"<<mo[i]<<"\n";
	for(int i=0; i<5; i++)
		cout << i << " bauli:"<<b[i]<<"\n";
	for(int i=0; i<10; i++)
		cout << i << " venditori:"<<v[i]<<"\n";
		
	*/
	Stanza* st= new Stanza();
    int c[4]={-1,2,9,-2};
    st->riempiMatrice(50,c);
    int m [MAXDIM][MAXDIM];
    st->getMatrice(m);
	st->stampaMatrice(m);
	return 0;
}
