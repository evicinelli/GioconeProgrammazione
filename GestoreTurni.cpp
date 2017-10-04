# include "GestoreTurni.hpp"
# define ACTION_TRESHOLD 5

GestoreTurni::GestoreTurni()
{
	gestoreLivelli = GestoreLivelli();
	player = new Giocatore();
	ctrl = new Controller(gestoreLivelli, player);
	counter = 1;
	actionPoint = 0;
}

void GestoreTurni::init()
{
	// Schermata introduttiva al volo?
	initscr();
	raw();
	noecho();
	refresh();
}

void GestoreTurni::play()
{
	ctrl->gioca();
}

bool GestoreTurni::isPlayerTurn()
{
	return (counter % 2 != 0);
}

void GestoreTurni::changeTurn()
{

}