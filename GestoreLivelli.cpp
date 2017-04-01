#include "Livello.cpp"

class GestoreLivelli{
    protected:
        struct listaLivelli{
            Livello l;
            listaLivelli *next;
        };
        typedef listaLivelli *ptr_listaLivelli;

    public:
        GestoreLivelli(){

        }

        void aggiungiLivello(Livello nuovo){
            /** aggiungi livello in coda alla lista dei livelli*/
        }
};
