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
    //printf("### LIVELLO CORRENTE: %p (%d) ###\n", this->getLevelById(livCorrente), livCorrente);
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
    bool trovato=false;
    while(trovato!= true) {
            if(out->l->getNStanze()==id){
                trovato=true;
            }
            else{
                out = out->next;
            }
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
    //printf("**************************************************\n");
   // printf("\n\n(*) CREAZIONE LIVELLO %d\n", n);
    Livello *l = new Livello(n);
   // printf("\n\n(*) INIZALIZZAZIONE COMPLETATA\n");

  //  printf("\n\n(*) POPOLO LIVELLO A INDIRIZZO %p\n", l);
    generatore.popolaLivello(l); // 3

    //printf("\n\n(*) SITUAZIONE COLLEGAMENTI PER LIVELLO %d\n", l->getNStanze());
    //printf("\n\n(*) SITUAZIONE STANZE PER LIVELLO %d\n", l->getNStanze());

    //generatore.stampaCollegamenti(l);
    //l->dumpRoomList();

    this->aggiungiLivello(l); // 4
    this->passaLivSucc(); // 5

    /**
        GESTIONE DEI COLLEGAMENTI CON IL LIVELLO PRECEDENTE
    */

    if (l->getNStanze() != 1) {
        //cout<<"NUMERO STANZE LIV CORRENTE "<<livCorrente<<endl;
        //cout<<"NUMERO STANZE LIV PRECEDENTE"<<getLevelById(livCorrente - 1)->getNStanze()<<endl;
        generatore.collegaLivelloPrec(l, getLevelById(livCorrente - 1));
    }

    //this->dumpLevelList();
    //printf("**************************************************\n");

    return l;
}

void GestoreLivelli::dumpLevelList(){
    printf("\n\n\n(*) LISTA LIVELLI\n");
    lista* list = this->head;
    printf("%d\n", livCorrente);
    printf("%p %p\n",list, head );
    int i = 0;
    while(list) {
        printf("%d : %p (%d)",i, list->l, list->l->getNStanze());
        if (i == this->livCorrente - 1)
            printf(" <-- \n");
        else
            printf("\n");
        list = list->next;
        ++i;
    }
}


int GestoreLivelli::getLevN(){
    return this->maxLiv;
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
