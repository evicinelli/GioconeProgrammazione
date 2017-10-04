# include "GestoreTurni.hpp"
# define ACTION_TRESHOLD 5

GestoreTurni::GestoreTurni()
{
	gestoreLivelli = GestoreLivelli();
	player = new Giocatore();
	ctrl = new Controller(gestoreLivelli, player);
	victory=false;
	defeat=false;
	ctrl->init();
}


void GestoreTurni::play()
{
    while(!victory && !defeat && !ctrl->hasEnded())
    {
        if(player->getAct()>=0) {
            ctrl->gioca();
        } else {
            // Mostro
        }
    }
}

