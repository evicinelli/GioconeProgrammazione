#include "GestoreLivelli.hpp"
#include "Giocatore.hpp"
#include "Drawer.hpp"
#include <unistd.h>

class Controller
{
	protected:

		GestoreLivelli gestore;
		Giocatore* p;
		Drawer* d;
		Stanza stanza;
		bool ended;

	public:
		Controller(GestoreLivelli gl, Giocatore* player);

		void gestisciInput(char c);

       		void init();

		void gioca();

		bool hasGameEnded();

		void printDebugMsg(const char* s);

		Stanza* getCurrentRoom();

	private:
		void vaiSu();

		void vaiGiu();

		void vaiDx();

		void vaiSx();

		bool controllaMovimento(int posX, int posY);

		void cambiaStanza(int direzione);

		bool isVicinoPorta(int &dir);
};
