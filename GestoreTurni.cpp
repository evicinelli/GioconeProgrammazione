# include "GestoreTurni.hpp"
# include <stdio.h>
# define MONSTERS 6

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
    while(!victory && !defeat && !ctrl->hasGameEnded()) {
	if(player->getAct()>0) {
		ctrl->gioca();
	} else {
		Mostro* m;
		int mCounter = ctrl->getCurrentRoom()->getHowManyMonsters();
//		while(Mostro->getAct()>=0) {
//		}
		for (int i = 0; i < mCounter; ++i) {
			m = ctrl->getCurrentRoom()->getMonster(i);
			if (m && m->isAlive())
				m->takeAction(player);
		}
		player->setAct(5);
	}
    }
}

