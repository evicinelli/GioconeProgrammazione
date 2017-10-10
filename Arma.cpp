#include "Arma.hpp"

Arma::Arma()
{
    disponibile=false;
}
Arma::Arma(int lev, std::string type)
{
    //srand(time(0));
    int n=0;
    if (type=="spada")
    {
        mindanno=5+(int)(2.1*lev);
        n=8;
        strMult=0.75;
        dexMult=0.75;
        strMin=(int)(0.8*lev)+4;
        dexMin=(int)(0.8*lev)+4;
    }
    else if (type=="mazza")
    {
        mindanno=7+(int)(3.5*lev);
        n=5;
        strMult=1.25;
        dexMult=0.05;
        strMin=(int)(1.3*lev)+6;
        dexMin=0;
    }
    else if (type=="pugnale")
    {
        mindanno=3+(int)(1.4*lev);
        n=15;
        strMult=0.05;
        dexMult=1.25;
        strMin=0;
        dexMin=(int)(1.3*lev)+6;
    }
    int r=(int)rand()%n;
    char buf[3], buf2[4];
    maxdanno=mindanno+(int)(lev*r+0.75*r);
    sprintf(buf,"%d",mindanno);
    sprintf(buf2,"%d",maxdanno);
    nome=type+": "+buf+"-"+buf2;
    disponibile=true;
    droprate=30;
    prezzo=20+(int)(lev*7.5)+(int)(maxdanno*0.05+mindanno*0.05);

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
