#include "Livello.hpp"
#include "stdio.h"
Livello::Livello (int n){
	nStanze=n;
	vettStanze= new Stanza [nStanze+2];
	vettColl= new Collegamento[nStanze];
	//cout<<vettColl<<endl;
}

Stanza Livello::getStanza(int id){
	return vettStanze[id];
}

void Livello::setStanza(int id, Stanza* s){
    int ma[MAXDIM][MAXDIM];
    s->getMatrice(ma);
	vettStanze[id].setMatrice(ma);
}

void Livello::setCollegamento(int id, Collegamento* c){
	vettColl[id].setId(c->getId());
	int v[4]={-1,-1,-1,-1};
	vettColl[id].setDirezioni(v);
	int h[4];
	vettColl[id].getDirezioni(h);

}

void Livello::getAdiacenze(int id, int adiacenze [4]){
	Collegamento c=this->vettColl[id];
	c.getDirezioni(adiacenze);

}


int Livello::getNStanze(){
	return this->nStanze;
}

void Livello::setAdiacenze(int id, int a [4]) {
	this->vettColl[id].setNord(a[0]);
	this->vettColl[id].setSud(a[1]);
	this->vettColl[id].setOvest(a[2]);
	this->vettColl[id].setEst(a[3]);
}

Stanza Livello::vaiNord(int id){
	Collegamento el=vettColl[id];
	int a[4];
	el.getDirezioni(a);
	return getStanza(a[0]);
}

Stanza Livello::vaiSud(int id){
	Collegamento el=vettColl[id];
	int a[4];
	el.getDirezioni(a);
	return getStanza(a[1]);
}

Stanza Livello::vaiOvest(int id){
	Collegamento el=vettColl[id];
	int a[4];
	el.getDirezioni(a);
	return getStanza(a[2]);
}

Stanza Livello::vaiEst(int id){
	Collegamento el=vettColl[id];
	int a[4];
	el.getDirezioni(a);
	return getStanza(a[3]);
}



void Livello::collegaStanza(int sPartenza, int sArrivo, int direz){

	if(direz==0){
		this->vettColl[sPartenza].setNord(sArrivo);
	}
	else if(direz==1){
		this->vettColl[sPartenza].setSud(sArrivo);
	}
	else if(direz==2){
		this->vettColl[sPartenza].setOvest(sArrivo);
	}
	else if(direz==3){
		this->vettColl[sPartenza].setEst(sArrivo);
	}

}

void Livello::dumpRoomList(){
	for (int i = 0; i < getNStanze(); ++i)
	{
		printf("i: %p\n", vettStanze[i]);
	}
}
Stanza* Livello::getPointerToStanza(int id){
    return &(vettStanze[id]);
}

Collegamento* Livello:: getVettColl(){
    return this->vettColl;
};



