#include "GestoreLivelli.hpp"
#include "Giocatore.hpp"
#include "Drawer.hpp"
#include "Mostro.hpp"
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

		void aumentaLivello();
		
		bool hasGameEnded();

		void printDebugMsg(const char* s);

		Stanza* getCurrentRoom();

		void updateMonsterCoordinates(int oldY, int oldX, Mostro* m);
	private:
		void vaiSu();

		void vaiGiu();

		void vaiDx();

		void vaiSx();

		bool controllaMovimento(int posX, int posY);

		void cambiaStanza(int direzione);
		
		void scriviIstruzioni();
		
		void scegliArma(bool opt);

		bool isVicinoPorta(int &dir);
};
