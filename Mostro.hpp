# ifndef MOSTRO_HPP
# define MOSTRO_HPP
# include "Giocatore.hpp"
# define AGGRO 2 /* range di aggressività del mostro */
# define SCAN_RANGE 3 /* Range entro il quale il mostro segue il giocatore */

class Mostro : public Personaggio
{
    protected:
        std::string razza;
        char id;           	//il carattere che rappresenta il mostro sulla mappa
        bool alive;
        bool chasing;
        void muovi(int targetX, int targetY, int matrix[24][24], int dimensione);
        void insegui(int targetX, int targetY, int matrix[24][24], int dimensione);
    public:
        Mostro(int lev, std::string race);
        char getId();
		std::string getRazza();
        bool isAlive();
        bool isChasing();
        int takeAction(Giocatore* g, int matrix[24][24], int dim);		//restituisce un valore diverso a seconda dell'azione intrapresa
        void morte(Giocatore *g);    //metodo chiamato quando g uccide il mostro

    private:
        /* Decide se il mostro deve attaccare */
        bool needToAttack(Giocatore* g);
        bool needToChase(Giocatore* g);
};

#endif // MOSTRO_HPP
