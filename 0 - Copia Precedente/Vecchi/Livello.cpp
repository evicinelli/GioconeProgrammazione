#include "Livello.hpp"
        Livello::Livello (int n){
            nStanze=n;
            vettStanze= (Stanza*) malloc(sizeof(Stanza*) * (nStanze+2));
            vettColl= (prt_coll) malloc(sizeof(prt_coll) * (nStanze));
        }

        Stanza Livello::getStanza(int id){
            return vettStanze[id];
        }

        void Livello::setStanza(int id, Stanza* s){
            vettStanze[id].setS(s->getS());
        }


        void Livello::getAdiacenze(int id, int adiacenze [4]){
            collegamenti el=vettColl[id];
            int i;
            for(i=0; i<4; i++){
                adiacenze[i]=el.direzioni[i];
            }
        }

        Stanza Livello::vaiNord(int id){
            collegamenti el=vettColl[id];
            int ncoll=el.direzioni[0];
            return getStanza(ncoll);
        }

        Stanza Livello::vaiSud(int id){
            collegamenti el=vettColl[id];
            int ncoll=el.direzioni[1];
            return getStanza(ncoll);
        }

        Stanza Livello::vaiOvest(int id){
            collegamenti el=vettColl[id];
            int ncoll=el.direzioni[2];
            return getStanza(ncoll);
        }

        Stanza Livello::vaiEst(int id){
            collegamenti el=vettColl[id];
            int ncoll=el.direzioni[3];
            return getStanza(ncoll);
        }

        int Livello::getNStanze(){
            return this->nStanze;
        }

