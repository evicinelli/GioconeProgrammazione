#ifndef MOSTRO_HPP
#define MOSTRO_HPP

#include "Giocatore.hpp"

class Mostro : public Personaggio
{
    protected:
        std::string razza;
        char id;           //il carattere che rappresenta il mostro sulla mappa
    public:
        Mostro(int lev, std::string race);
        char getId();
        void morte(Giocatore g);    //metodo chiamato quando g uccide il mostro
};

#endif // MOSTRO_HPP
