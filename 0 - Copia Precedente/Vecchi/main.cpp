#include <iostream>
#include "GeneratoreLivelli.hpp"
using namespace std;

int main()
{
   Livello* l= new Livello(5);
   GeneratoreLivelli g=GeneratoreLivelli();
   g.popolaLivello(l);
   return 0;
}
