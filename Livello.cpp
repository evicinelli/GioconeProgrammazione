#include "Stanza.cpp"
class Livello{
    protected:
        Stanza *prossimo;
        Stanza *precedente;
        int nLivello;

    public:
        Livello (int n){
            this->nStanze=n;
            //gestore livelli che restistusce il grafo del livello corrente dopo aver creato adeguatamente l'interno delle stanze
        }

};
