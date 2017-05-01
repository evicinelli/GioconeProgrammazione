#include "GestoreLivelli.hpp"
#include "GeneratoreLivelli.hpp"
#include <stdio.h>
	
	void GestoreLivelli::linkLivelli() {
		
	}

    GestoreLivelli::GestoreLivelli() {
    	
    }

    void GestoreLivelli::passaLivSucc() {
    	this->livCorrente++;
    }

    void GestoreLivelli::passaLivPrec() {
    	if (this->livCorrente > 1) {
    		this->livCorrente--;
    	}
    }

    void GestoreLivelli::aggiungiLivello() {
    	ptr_listaLiv list = this->head;
    	
    	while(list!= NULL) {
    		list = list->next;
    	}

    	list = new lista;
    	list->l = Livello(livCorrente++);
    	list->next = NULL;
    }

	Livello* GestoreLivelli::getLivello (int id) {
		lista *list = this->head;
		int ctr = 0;

		while(list && ctr < this->livMax && ctr < id) {
			list = list->next;
			ctr++;
		}

		return &(list->l);
	}

    Livello* GestoreLivelli::creaLivello(int n) {
    	generatore = GeneratoreLivelli();
    }
