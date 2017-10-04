#include <time.h>       /* time */
#include "GeneratoreLivelli.hpp"
#include "GestoreLivelli.hpp"
#include "Controller.hpp"
#include <string.h>


class GestoreTurni
{
private:
	GestoreLivelli gestoreLivelli;
	Giocatore* player;
	Controller* ctrl;
	int counter;
	int actionPoint;
	
	bool isPlayerTurn();	/* Turno del giocatore sse true, del mostro altrimenti */
	void changeTurn();	/* Logica per il cambio del turno */

public:
	GestoreTurni();	/* Inizializza i controller e i gestori */
	void init();	/* Inizializza le impostazioni del gioco */
	void play();	/* Loop del gioco */
	void actionPerformed();
};
