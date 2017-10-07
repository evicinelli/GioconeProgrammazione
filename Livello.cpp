#include "Livello.hpp"
#include "stdio.h"

Livello::Livello (int n){
    //inizializza il numero di stanze del livello
	nStanze=n;

	//alloca il vettore delle stanze cha avrà dimensione pari al numero delle stanze+2 perchè nell'indice nStanze ci sarà l'ultima stanza del livello precedente e nell'indice nStanze+1 ci sarà il
    //puntatore alla prima stanza del livello successivo
    vettStanze= new Stanza [nStanze+2];

    //alloca il vettore dei collegamenti tra le stanze che avrà dimensione pari al numero di stanze
	vettColl= new Collegamento[nStanze];

	//inizializza id delle prime nStanze del vettore delle stanze
	for (int i=0; i<nStanze; i++){
        vettStanze[i].setId(i);
	}

}

void Livello::setMatriceStanza(int id){
    //vettore direzioni da passare alla stanza
    int vett [4];
    this->getAdiacenze(id,vett);

    //se è il primo livello allora nel collegamento a nord vi è il passaggio di livello
    //il primo livello è un caso speciale poichè non vi è il collegamento al livello precedente
    if(this->getNStanze()==1){
        vett[0]=-2;
    }
    //se non è il primo livello
    else{
        //a sud della prima stanza vi è il collegamento al livello precedente
        if(id==0){
            vett[1]=-2;
        }
        //a nord dell'ultima stanza vi è il collegamento al livello successivo
        else if(id==this->getNStanze()-1){
            vett[0]=-2;
        }
    }

    //infine viene richiamato il metodo che crea la matrice della stanza
    vettStanze[id].riempiMatrice(this->nStanze, vett);
}

Stanza Livello::getStanza(int id){
	return vettStanze[id];
}

void Livello::setStanza(int id, Stanza* s){
    //matrice di appoggio
    int ma[MAXDIM][MAXDIM];
    //matrice di appoggio contiene la matrice della stanza passata come paramentro
    s->getMatrice(ma);
    //modifica della matrice della stanza che si trova all'indice id del vettore delle stanze del livello
	vettStanze[id].setMatrice(ma);
}

void Livello::setCollegamento(int id, Collegamento* c){
    //set id collegamento
	vettColl[id].setId(c->getId());
	//vettore di appoggio
	int v[4]={-1,-1,-1,-1};
	//modifica collegamento
	vettColl[id].setDirezioni(v);

}

void Livello::getAdiacenze(int id, int adiacenze [4]){
    //collegamento relativo all'id
	Collegamento c=this->vettColl[id];
	//get delle direzioni nell'array adiacenze
	c.getDirezioni(adiacenze);

}

int Livello::getNStanze(){
	return this->nStanze;
}

Stanza Livello::vaiNord(int id){
    //collegamento relativo all'id
	Collegamento el=vettColl[id];
	//get delle direzioni usando all'array di appoggio
	int a[4];
	el.getDirezioni(a);
	//ritorno della stanza avente id pari a quello contenuto nell'elemento a indice zero (perchè 0 -> Nord) dell'array delle direzioni
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
    //collegamento a nord
	if(direz==0){
		this->vettColl[sPartenza].setNord(sArrivo);
	}
	//collegamento a sud
	else if(direz==1){
		this->vettColl[sPartenza].setSud(sArrivo);
	}
	//collegamento a ovest
	else if(direz==2){
		this->vettColl[sPartenza].setOvest(sArrivo);
	}
	//collegamento a est
	else if(direz==3){
		this->vettColl[sPartenza].setEst(sArrivo);
	}

}

Stanza* Livello::getPointerToStanza(int id){
    return &(vettStanze[id]);
}
void Livello::visitStanza(int id){
	vettStanze[id].visit();
}
Collegamento* Livello:: getVettColl(){
    return this->vettColl;
};



