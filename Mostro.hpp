#ifndef MOSTRO_HPP
#define MOSTRO_HPP

#include "Personaggio.hpp"

class Mostro : public Personaggio
{
    protected:
        std::string razza;
        char id;           //il carattere che rappresenta il mostro sulla mappa
    public:
        Mostro(int lev, std::string race);
        char getId();
        void morte(Personaggio p);    //metodo chiamato quando p uccide il mostro
};

#endif // MOSTRO_HPP
