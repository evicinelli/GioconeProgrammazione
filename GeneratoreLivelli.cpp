#include "Livello.cpp"

/**
    decidere il grafo delle stanze di ogni livello
    cioè
*/

class GeneratoreLivelli{
    protected:
        int prob={};
    public:
        Livello genera(int nLivello){
            /**
                -generare stanza centrale
                    -precedente=ULTIMA STANZA DEL LIVELLO PRECEDENTE
                    -prossimo=PRIMA STANZA DEL LIVELLO SUCCESSIVO

                -scegliere in base al numero del livello il numero delle stanze (livello 2 -> nStanze =2)
                -generare le stanze:
                    a partire dalla stanza centrale precedentemente generata si sceglie una delle 3 rimanenti direzioni in cui il livello si
                    può estendere, quindi bisogna ricordarsi di asoosciare i puntatore di entrabe le stanze in questione:
                        stanza A-nord -> stanzaB-sud
                        stanza A-sud -> stanzaB-nord
                        stanza A-est -> stanzaB-ovest
                        stanza A-ovest -> stanzaB-est
            */
        }

};
