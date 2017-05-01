#ifndef STANZA_HPP_INCLUDED
#define STANZA_HPP_INCLUDED

class Stanza{

protected:
    int s;
public:
	
	/**
	Crea la stanza di id n
	*/
    Stanza(int n);
   

    /**
    ritorna:
    	- true se la stanza ha id -1 (considerata vuota)
    	- false altrimenti
    */
    bool isNull();

    /**
    ritorna id della stanza
    */
    int getS();

    /**
    risetta l'id di una stanza già esistente
    */
    void setS(int n);

};




#endif // STANZA_HPP_INCLUDED
