#include "Arma.hpp"

Arma::Arma()
{
    disponibile=false;
}
Arma::Arma(int lev, std::string type)
{
    srand(time(0));
    int n;
    if (type=="spada")
    {
        mindanno=4+(int)(0.8*lev);
        n=8;
        strMult=0.75;
        dexMult=0.75;
        strMin=2*lev;
        dexMin=2*lev;
    }
    else if (type=="mazza")
    {
        mindanno=4+(int)(1.1*lev);
        n=5;
        strMult=1.25;
        dexMult=0.05;
        strMin=4*lev;
        dexMin=0;
    }
    else if (type=="pugnale")
    {
        mindanno=3+(int)(0.5*lev);
        n=15;
        strMult=0.05;
        dexMult=1.25;
        strMin=0;
        dexMin=4*lev;
    }
    int r=(int)rand()%n;
    char buf[2];
    sprintf(buf,"%d",r);
    maxdanno=mindanno+(3*r);
    nome=type+" con random = "+buf;
    disponibile=true;
    droprate=30;

}
int Arma::getMin()
{
    return mindanno;
}
int Arma::getMax()
{
    return maxdanno;
}
int Arma::getPrezzo()
{
    return prezzo;
}

int Arma::getDexMin()
{
    return dexMin;
}
int Arma::getStrMin()
{
    return strMin;
}

double Arma::getStrMult()
{
    return strMult;
}
double Arma::getDexMult()
{
    return dexMult;
}
double Arma::getDropRate()
{
    return droprate;
}
std::string Arma::getNome()
{
    return nome;
}
void Arma::scarta()
{
    disponibile=false;
}
bool Arma::isAvailable()
{
    return disponibile;
}
