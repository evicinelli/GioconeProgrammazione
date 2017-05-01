#include <iostream>
#include "GeneratoreLivelli.hpp"
using namespace std;

int main()
{
   Livello* l= new Livello(10);
   GeneratoreLivelli g=GeneratoreLivelli();
    g.inizializzaVettColl(l);
    g.stampaCollegamenti(l);
/**
    cout<<"____________________"<<endl;

   g.link(1,7,l);
   g.link(9,7,l);
   g.stampaCollegamenti(l);
*/
   return 0;
}
