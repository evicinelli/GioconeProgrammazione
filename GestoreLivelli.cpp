#include "GestoreLivelli.hpp"
#include "GeneratoreLivelli.hpp"
#include <stdio.h>
#include <stdlib.h>

GestoreLivelli::GestoreLivelli(){
    //creazione di GeneratoreLivelli
    generatore = GeneratoreLivelli();
    //inizializzazione di head
    head = NULL;
    //creazione primo livello
    this->creaLivello(1);
    //set del livello corrente a 1
    this->livCorrente = 1;
    //set del livello massimo a 1
    this->maxLiv = 1;
}

void GestoreLivelli::passaLivSucc(){
    ++(this->livCorrente);
}

void GestoreLivelli::passaLivPrec(){
    (this->livCorrente)--;
}

void GestoreLivelli::aggiungiLivello(Livello* liv){
    //puntatore alla testa
    lista *li = head;
    //se head è diversa da NULL
    if(li!=NULL){
        //scorro la lista fino alla fine
        while(li->next != NULL){
            li = li->next;
        }
        //incremento max liv
        ++maxLiv;
        //aggiungo il livello liv nell'ultima posizione della lista
        li->next = new(lista);
        li->next->l = liv;
        li->next->next = NULL;
    }
    //altrimenti
    else{
        //il livello è il primo quindi head=liv
        head = new(lista);
        head->l = liv;
        head->next = NULL;
    }

}


Livello* GestoreLivelli::getLevelById(int id){
    //puntatore a head
    ptr_listaLiv out = this->head;
    //flag trovato settato a false
    bool trovato=false;
    //fino a quando flag è a false
    while(trovato!= true){
        //se ho trovato il livello setto trovato a true ed esco dal ciclo
        if(out->l->getNStanze()==id){
            trovato=true;
        }
        //altrimenti passo all'elemento successivo della lista
        else{
            out = out->next;
        }
    }
    //ritorno il livello
    return out->l;
}

Livello* GestoreLivelli::getInizio(){
	return head->l;
}

Livello* GestoreLivelli::creaLivello(int n){
    //creazione nuovo livello
    Livello *l = new Livello(n);
    //popolazione del livello
    generatore.popolaLivello(l);
    //aggiunta del livello alla lista del gestoreLivelli
    this->aggiungiLivello(l);
    //incrementato livello corrente
    this->passaLivSucc();
    //collegamento al livello precedente sse non è il livello 1
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
