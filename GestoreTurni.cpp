# include "GestoreTurni.hpp"
# include <stdio.h>

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
        /*if(player->getAct()>=0)
        {
            ctrl->gioca();
        }
        else
        {
            //while(Mostro->getAct()>=0)
            player->setAct(5);
        }*/
        ctrl->gioca();
    }
}

