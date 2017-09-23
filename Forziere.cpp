#include "Forziere.hpp"
#include "Arma.hpp"

Forziere::Forziere(int lev)
{
    srand(time(0));
    int r=(int)rand()%3;
    switch (r)
    {
        case 0:
            interno=Arma(lev,"spada");
            break;
        case 1:
            interno=Arma(lev,"mazza");
            break;
        case 2:
            interno=Arma(lev,"pugnale");
            break;
    }

}
Arma Forziere::getInterno()
{
    return interno;
}
