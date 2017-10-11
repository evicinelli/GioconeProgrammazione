# ifndef MOSTRO_HPP
# define MOSTRO_HPP
# include "Giocatore.hpp"
# define AGGRO 6 /* range di aggressività del mostro */

/* Struttura per una casella di una matrice */
struct spot {
    int r;
    int c;
    int val;
};


class Mostro : public Personaggio
{
    protected:
        
        int dmap[24][24];     /* Mappa della conoscenza del mostro */
        int d[24*24];
        std::string razza;  /* razza */
        char id;            /* Carattere del mostro sulla mappa */
        bool alive;         /* il mostro è vivo? */
        bool chasing;       /* Il mostro sta inseguendo? */
        void muovi(int targetX, int targetY, int matrix[24][24], int dimensione);
        void insegui(int targetX, int targetY, int matrix[24][24], int dimensione);
   
    public:
        Mostro(int lev, std::string race);
        
        /* ritorna carattere identificativo del mostro */
        char getId();
		
        /* Ritorna la razza del mostro */
        std::string getRazza();
        
        /* true sse mostro è vivo */
        bool isAlive();

        /* true sse mostro sta inseguendo il giocatore */
        bool isChasing();
        
        /* Metodo per decidere cosa fare nel turno del mostro. Ritorna valore diverso a seconda 
         * dell'azione intrapresa */
        int takeAction(Giocatore* g, int matrix[24][24], int dim);
        
        /* metodo chiamato quando g uccide il mostro */
        void morte(Giocatore *g);

        /* Costruisce la mappa di Dijkstra per un quadrato VIEW_RANGE x VIEW_RANGE centrato nel mostro. 
         * Usata dai metodi di movimento per avere un movimento sensato verso l'obiettivo 
         * Parametri: le coordinate dell'obiettivo, e la matrice della stanza */
        void buildDMap(int targetX, int targetY, int matrix[24][24], int dimensione);
    
    private:
        /* Decide se il mostro deve attaccare */
        bool needToAttack(Giocatore* g);
        
        /* Decide se il mostro deve inseguire */
        bool needToChase(Giocatore* g);

        /* Funzioni di servizio per la generazione della mappa e la gestione della coda */
        int hash(int r, int c, int dim);
        int getR(int a, int dim);
        int getC(int a, int dim);
        bool isAlreadyEnqueued(int r, int c, int dim);
        spot* _min(spot* a, spot* b);
        spot* min(spot* a, spot* b, spot* c, spot* d);
};

#endif // MOSTRO_HPP