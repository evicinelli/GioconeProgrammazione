#ifndef ARMA_HPP_INCLUDED
#define ARMA_HPP_INCLUDED
#include <stdlib.h>
#include <time.h>
#include <string>
class Arma
{
    protected:
        int mindanno, maxdanno, livello, prezzo;
        int strMin, dexMin;  //forza e destrezza minime per usare l'arma
        double droprate;     //possibilità che venga lasciata come loot
        double strMult;      //moltiplicatore di forza     (quanto influisce sul danno)
        double dexMult;      //moltiplicatore di destrezza (quanto influisce sul danno)
        std::string tipologia;
    public:
        Arma();
        Arma(int lev, std::string type);
        int getMin();
        int getMax();
        int getPrezzo();
        int getDexMin();
        int getStrMin();
        double getStrMult();
        double getDexMult();
        double getDropRate();


};

#endif // ARMA_HPP_INCLUDED
