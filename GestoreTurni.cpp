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
    while(!victory && !defeat && !ctrl->hasGameEnded()) {
        if(player->getAct()>0) {
            ctrl->gioca();
        } else {
            Mostro* m;
            int action=0;
            int mCounter = ctrl->getCurrentRoom()->getHowManyMonsters();
            int mat[MAXDIM][MAXDIM];
            int oX = -1;
            int oY = -1;

            for (int i = 0; i < mCounter; ++i) {
                m = ctrl->getCurrentRoom()->getMonster(i);
                if (m && m->isAlive()) {
                    while (m->getAct() > 0) {
                        oX = m->getPosX();
                        oY = m->getPosY();
                        ctrl->getCurrentRoom()->getMatrice(mat);
                        action=m->takeAction(player, mat, ctrl->getCurrentRoom()->getDimensione());
                        switch (action) {
							case 0:
								//il mostro diventa di colore verde/blu
								break;
							case 1:
								//usleep(100000);
								//il mostro diventa rosso perché ha visto il giocatore e lo insegue
								break;
							default:
								ctrl->animaAttacchi(m, false);
								ctrl->scriviInfoAttacco(m,action,false);
								break;
						}
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
		{
            defeat = true;
            ctrl->endGame(0);
		}
        if (player->getLev()>=LEV_VICTORY || player->getOro()>=GOLD_VICTORY)
		{
			victory = true;
			ctrl->endGame(1);
		}
    }
}

