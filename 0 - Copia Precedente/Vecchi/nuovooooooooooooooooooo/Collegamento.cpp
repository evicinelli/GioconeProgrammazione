#include "Collegamento.hpp"
Collegamento::Collegamento(int j){
        this->id=j;

        int i;
        for(i=0;i<4;i++){
            this->direzioni[i]=-1;
        }
}

int Collegamento::getId(){
    return this->id;
}

void Collegamento::setId(int i){
    this->id=i;
}

void Collegamento::getDirezioni(int a[4]){
    int i;
    for(i=0;i<4;i++){
        a[i]=this->direzioni[i];
    }
}

void Collegamento::setDirezioni(int a[4]){
    int i;
    for(i=0;i<4;i++){
        this->direzioni[i]=a[i];
    }
}


void Collegamento::setNord(int idArrivo){
    this->direzioni[0]=idArrivo;
}

void Collegamento::setSud(int idArrivo){
    this->direzioni[1]=idArrivo;
}

void Collegamento::setOvest(int idArrivo){
    this->direzioni[2]=idArrivo;
}

void Collegamento::setEst(int idArrivo){
    this->direzioni[3]=idArrivo;
}

