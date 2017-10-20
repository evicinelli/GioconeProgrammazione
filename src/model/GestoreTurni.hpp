#include <time.h>       /* time */
#include "GeneratoreLivelli.hpp"
#include "GestoreLivelli.hpp"
#include "../controller/Controller.hpp"
#include <string.h>
# define MONSTERS 6
# define LEV_VICTORY 100
# define GOLD_VICTORY 100000

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
