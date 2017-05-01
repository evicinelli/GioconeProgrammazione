#include <iostream>
#include "GeneratoreLivelli.hpp"
using namespace std;

int main()
{
   Livello* l= new Livello(25);
   GeneratoreLivelli g=GeneratoreLivelli();
    cout<<"____________________"<<endl;
g.stampaCollegamenti(l);
    g.popolaLivello(l);

     g.stampaCollegamenti(l);

   return 0;
}
