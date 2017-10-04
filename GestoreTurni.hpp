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
	bool victory,defeat;

public:
	GestoreTurni();	/* Inizializza i controller e i gestori */
	void play();	/* Loop del gioco */
};
