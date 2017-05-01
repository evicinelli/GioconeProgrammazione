#include "Livello.hpp"
Livello::Livello (int n){
	nStanze=n;
	vettStanze= (Stanza*) malloc(sizeof(Stanza*) * (nStanze+2));
	vettColl= (Collegamento*) malloc(sizeof(Collegamento*) * (nStanze));
}

Stanza Livello::getStanza(int id){
	return vettStanze[id];
}

void Livello::setStanza(int id, Stanza* s){
	vettStanze[id].setS(s->getS());
}

void Livello::setCollegamento(int id, Collegamento* c){
	//vettColl[id].setId(c->getId());
	vettColl[id]=Collegamento(id);
	cout<<"Id: "<<vettColl[id].id<<"\n";
	int v[4]={-1,-1,-1,-1};
	for (int i=0;i<4;i++){
		cout<<"Direzioni: "<<vettColl[id].direzioni[i]<<"\n";
	}
	//vettColl[id].setDirezioni(v);
	int w[4];
	vettColl[id].setNord(-1);
	vettColl[id].setSud(-1);
	vettColl[id].setOvest(-1);
	vettColl[id].setEst(-1);
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

