#include <iostream>
#include "GeneratoreLivelli.hpp"
using namespace std;

int main()
{
   Livello* l= new Livello(5);
   GeneratoreLivelli g=GeneratoreLivelli();
    cout<<"____________________"<<endl;

     g.popolaLivello(l);


     g.stampaCollegamenti(l);

   return 0;
}
