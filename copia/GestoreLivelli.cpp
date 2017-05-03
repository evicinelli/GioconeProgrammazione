#include "GestoreLivelli.hpp"
#include "GeneratoreLivelli.hpp"
#include <stdio.h>
#include <stdlib.h>

GestoreLivelli::GestoreLivelli() {
	generatore = GeneratoreLivelli();
	head = NULL;
	this->creaLivello(1);
	this->livCorrente = 1;
	this->maxLiv = 1;
}

void GestoreLivelli::passaLivSucc() {
	++(this->livCorrente);
}

void GestoreLivelli::passaLivPrec() {
	--(this->livCorrente);
}

void GestoreLivelli::aggiungiLivello(Livello* liv) {
	lista *li = head;

	if(li) {
		while(li->next != NULL) {
			li = li->next;
		}

		++maxLiv;
		li->next = new(lista);
		li->next->l = liv;
		li->next->next = NULL;
	} else {
		head = new(lista);
		head->l = liv;
		head->next = NULL;
	}

}


Livello* GestoreLivelli::getLevelById(int id) {
	ptr_listaLiv out = this->head;
	int i = 0;
	while(i <= id && out) {
		out = out->next;
	}
	return out->l;
}

Livello* GestoreLivelli::creaLivello(int n) {
	/*
	Creazione di un nuovo livello:
	1 - Inizializzazione dei collegamenti (tutti a -1)
	2 - Costruzione di stanze e collegamenti tra le stanze
	3 - Aggiunta alla lista dei livelli del gestore
	4 - Si passa al livello appena creato aggiornando l'indicatore del livello in gestore
	5 - Si ritorna il livello appena creato
	*/
	printf("----------------------------\n");
	printf("\n(*) CREAZIONE LIVELLO %d\n", n);
	Livello *l = new Livello(n);
	printf("\n(*) INIZALIZZAZIONE COMPLETATA\n");

	printf("\n(*) POPOLO LIVELLO A INDIRIZZO %p\n", l);
	generatore.popolaLivello(l); // 3

	printf("\n(*) SITUAZIONE COLLEGAMENTI PER LIVELLO %d\n", l->getNStanze());
	generatore.stampaCollegamenti(l);

	this->aggiungiLivello(l); // 4
	this->passaLivSucc(); // 5
	printf("----------------------------------------\n");

	/**
		GESTIONE DEI COLLEGAMENTI CON IL LIVELLO SUCCESSIVO E PRECEDENTE
	*/

	if (l->getNStanze() != 1) {
		generatore.passaggioLivello(l, getLevelById(livCorrente--));
	}

	return l;
}

void GestoreLivelli::dumpLevelList(){
	printf("\n\n\n(*) LISTA LIVELLI\n");
	lista* list = this->head;
	printf("%p %p\n",list, head );
	int i = 0;
	while(list) {
		printf("%d : %p (%d)\n",i, list->l, list->l->getNStanze());
		list = list->next;
		++i;
	}
}


int GestoreLivelli::getLevN(){
	return this->maxLiv;
}