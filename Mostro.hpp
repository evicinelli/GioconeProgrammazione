#ifndef MOSTRO_HPP
#define MOSTRO_HPP

#include "Personaggio.hpp"

class Mostro : public Personaggio
{
    protected:
        std::string razza;
    public:
        Mostro(int lev, std::string race);
};

#endif // MOSTRO_HPP
