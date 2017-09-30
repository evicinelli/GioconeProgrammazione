#include "GestoreLivelli.hpp"
#include "Giocatore.hpp"
#include "Drawer.hpp"

class Controller
{
	protected:

		GestoreLivelli gestore;
		Giocatore* p;
		Drawer* d;
		Stanza stanza;

	public:
		Controller(GestoreLivelli gl, Giocatore* player);

		void gestisciInput(char c);

		void gioca();

	private:
		void vaiSu();

		void vaiGiu();

		void vaiDx();

		void vaiSx();

		bool controllaMovimento(int posX, int posY);
};
