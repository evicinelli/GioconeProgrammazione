#include "Stanza.hpp"

Stanza::Stanza (int n){
	s=n;
}

bool Stanza::isNull(){
	bool ris=false;
	if(this->s==-2){
		ris=true;
	}
	return ris;
}

int Stanza::getS(){
	return s;
}

void Stanza::setS(int n){
	this->s=n;
}

