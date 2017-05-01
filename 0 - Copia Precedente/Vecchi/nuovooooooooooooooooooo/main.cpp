#include <iostream>
#include "GeneratoreLivelli.hpp"
using namespace std;

int main()
{
/*   Livello* l= new Livello(10);
   GeneratoreLivelli g=GeneratoreLivelli();
    g.inizializzaVettColl(l);
    g.stampaCollegamenti(l);

    cout<<"____________________"<<endl;

     g.link(9,7,l);
     g.link(1,5,l);
     g.link(4,6,l);
     g.link(2,3,l);

     g.stampaCollegamenti(l);
*/
   		srand(time(NULL));
	int da = 0, a = 0, stanze = 10;
	int dA = (rand() % 4);

   		// direzione di partenza a -> da
   		for (int i = 0; i < stanze; ++i)
   		{
   			int dP = (rand() % 4);

   		// controlliamo nessuna direzione proibita nel collegamento da/a la prima e l'ultima stanza
   		if (da == stanze && dP == 0 ) {
   			do {
   				dP = rand() % 4;
   			} while (dP == 0);
   		}

   		if (da == 0 && dP == 1) {
   			do {
   				dP = rand() % 4;
   			} while (dP == 1);
   		}

   		if (a == 0 && dA == 1)
   		{
   			do {
   				dA = rand() % 4;
   			} while (dA == 1);
   		}

   		if (a == stanze && dA == 0)
   		{
   			do {
   				dA = rand() % 4;
   			} while (dA == 0);
   		}
   		cout<<"s1: "<<da<<" s2: "<<a<<endl;
        cout<<"dA "<<dA<<endl;
        cout<<"dP "<<dP<<endl;
   		}
   return 0;
}
