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
            int mat[24][24];
            int oX = -1;
            int oY = -1;

            for (int i = 0; i < mCounter; ++i) {
                m = ctrl->getCurrentRoom()->getMonster(i);
                if (m && m->isAlive()) {
                    while (m->getAct() > 0) {
                        oX = m->getPosX();
                        oY = m->getPosY();
                        ctrl->getCurrentRoom()->getMatrice(mat);
                        m->takeAction(player, mat, ctrl->getCurrentRoom()->getDimensione());
                        ctrl->updateMonsterCoordinates(oY, oX, m, m->isChasing());
                        usleep(100000);
                    }
                }
            }

            player->setAct(5);
            for (int i = 0; i < mCounter; ++i) {
                ctrl->getCurrentRoom()->getMonster(i)->setAct(5);
            }

            //scarta gli input precedenti, in modo da evitare la memorizzazione dei tasti premuti durante il turno del mostro
            flushinp();

        }

        if (player->getHp() <= 0)
            defeat = true;
        if (defeat) {
            ctrl->endGame();
        }
    }
}

