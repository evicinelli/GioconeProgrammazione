#include "GestoreLivelli.hpp"
#include "Giocatore.hpp"
#include "Drawer.hpp"
#include "Mostro.hpp"
#include <unistd.h>

//Classe che mette insieme la parte grafica con il cuore del programma
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
		
		//Istruzioni che permetteranno al drawer di disegnare
       	void init();

		//iterazione che viene ripetuta ogni turno, aspetta il tasto in input
		void gioca();

		//apre la finestra dell'aumento di livello
		void aumentaLivello();
		
		//true se il gioco è finito
		bool hasGameEnded();

		//metodo per scrivere messaggi nella finestra
		void printMsg(const char* s);

		//Restituisce il puntatore della stanza
		Stanza* getCurrentRoom();

		//dice al drawer di disegnare il mostro nella nuova posizione
		void updateMonsterCoordinates(int oldY, int oldX, Mostro* m);
		
	private:
		//A seconda del tasto premuto, fa una determinata cosa
		void gestisciInput(char c);
		
		//Muove in su il personaggio
		void vaiSu();

		//Muove in giù il personaggio
		void vaiGiu();

		//Muove a destra il personaggio
		void vaiDx();

		//Muove a sinistra il personaggio
		void vaiSx();
		
		//Imposta la selezione nella finestra pop-up, ritorna l'elemento selezionato
		int selPopUp(char msg[20][40], int sel, int nStringhe);
		
		//true se ci si può nella cassella proposta
		bool controllaMovimento(int posX, int posY);

		//chiede a gestore livelli una nuova stanza e dice al drawer di disegnarla
		void cambiaStanza(int direzione);
		
		//dice al drawer di disegnare le struzioni
		void scriviIstruzioni();
		
		//dice al drawer di disegnare le armi
		void scegliArma(bool opt);
		
		//dice se c'è un arma nell'inventario
		bool thereisArma();
		
		//true se è vicino alla porta e in dir mette la direzione della porta
		bool isVicinoPorta(int &dir);
		
		//viene chiesta la conferma della chiusura del gioco
		bool chiudiGioco();
};
