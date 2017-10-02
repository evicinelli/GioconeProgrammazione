#include "GestoreLivelli.hpp"
#include "GeneratoreLivelli.hpp"
#include <stdio.h>
#include <stdlib.h>

GestoreLivelli::GestoreLivelli(){
    generatore = GeneratoreLivelli();
    head = NULL;
    this->creaLivello(1);
    this->livCorrente = 1;
    this->maxLiv = 1;
}

void GestoreLivelli::passaLivSucc(){
    ++(this->livCorrente);
    //printf("### LIVELLO CORRENTE: %p (%d) ###\n", this->getLevelById(livCorrente), livCorrente);
}

void GestoreLivelli::passaLivPrec(){
    (this->livCorrente)--;
}

void GestoreLivelli::aggiungiLivello(Livello* liv){
    lista *li = head;

    if(li!=NULL){
        while(li->next != NULL){
            li = li->next;
        }

        ++maxLiv;
        li->next = new(lista);
        li->next->l = liv;
        li->next->next = NULL;
    }
    else{
        head = new(lista);
        head->l = liv;
        head->next = NULL;
    }

}


Livello* GestoreLivelli::getLevelById(int id){
    ptr_listaLiv out = this->head;
    bool trovato=false;
    while(trovato!= true){
        if(out->l->getNStanze()==id){
            trovato=true;
        }
        else{
            out = out->next;
        }
    }
    return out->l;
}

Livello* GestoreLivelli::getInizio(){
	return head->l;
}

Livello* GestoreLivelli::creaLivello(int n){
    /*
    Creazione di un nuovo livello:
    1 - Inizializzazione dei collegamenti (tutti a -1)
    2 - Costruzione di stanze e collegamenti tra le stanze
    3 - Aggiunta alla lista dei livelli del gestore
    4 - Si passa al livello appena creato aggiornando l'indicatore del livello in gestore
    5 - Si ritorna il livello appena creato
    */

    Livello *l = new Livello(n);

    generatore.popolaLivello(l); // 3

    this->aggiungiLivello(l); // 4
    this->passaLivSucc(); // 5

    // GESTIONE DEI COLLEGAMENTI CON IL LIVELLO PRECEDENTE

    if (l->getNStanze() != 1){
        generatore.collegaLivelloPrec(l, getLevelById(livCorrente - 1));
    }

    return l;
}

int GestoreLivelli::getLevN(){
    return this->maxLiv;
}

int GestoreLivelli::getLivello(){
	return this->livCorrente;
}

void GestoreLivelli::stampaCollegamentiLivelli(){
    if(this->head==NULL){
        cout<<"[ ]"<<endl;
    }
    else{
        ptr_listaLiv temp=this->head;
        while(temp!=NULL){
            cout<<(temp->l)->getNStanze()<<endl;
            generatore.stampaCollegamenti(temp->l);
            temp=temp->next;
            cout<<"____________________________________"<<endl;
        }
    }
}
