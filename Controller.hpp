#include "GestoreLivelli.hpp"
#include "Giocatore.hpp"
#include "Drawer.hpp"

class Controller
{	
	protected:
	
		GestoreLivelli gestore;
		Giocatore* p;
		Drawer* d;
		
	public:
		Controller(GestoreLivelli gl, Giocatore* player);
		
		void gioca();

};
