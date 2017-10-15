#ifndef FORZIERE_HPP_INCLUDED
#define FORZIERE_HPP_INCLUDED
#include <stdlib.h>
#include <time.h>
#include "Arma.hpp"


class Forziere
{
protected:
    Arma interno;  //oggetto trovato all'interno del forziere
public:
    Forziere(int lev);
    Arma getInterno();
};

#endif // FORZIERE_HPP_INCLUDED
