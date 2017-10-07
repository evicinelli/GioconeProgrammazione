#ifndef COLLEGAMENTO_HPP_INCLUDED
#define COLLEGAMENTO_HPP_INCLUDED

class Collegamento{
protected:
    /**
    Indice della stanza del vettore delle stanze della classe livello alla quale il collegamento si riferisce
    */
    int id;

    /** Le stanze possono avere una "porta" su ogni lato del quadrato che le rappresenta, per questo motivo la
    dimensione del vettore delle direzioni è 4.

        direzioni[0]->N
        direzioni[1]->S
        direzioni[2]->O
        direzioni[3]->E
    */
    int direzioni[4];

public:
    /**
    Costruttore utilizzato per inizializzare il vettore dei collegamenti della classe Livello nel metodo
    inizializzaVettColl(Livello* l) in GeneratoreLivelli, inoltre tale costruttore settaa -1 tutte le adiacenze.
    */
    Collegamento(int j);

    /**
    Costruttore di dafault utilizzato nel costruttore di Livello quando viene creato l'array dei collegamenti esso
    è quindi utilizzato per allocare la giusta parte di memoria ad ogni elemento dell'array.
    */
    Collegamento();

    /**
    Metodo che restituisce l'id del collegamento
    */
    int getId();

    /**
    Metodo che modifica l'id del collegamento in base all'intero passato come parametro
    */
    void setId(int i);

    /**
    Metodo che restituisce l'array delle direzioni
    */
    void getDirezioni(int a[4]);

    /**
    Metodo che modifica l'array delle direzioni in base all'array passato come parametro
    */
    void setDirezioni(int a[4]);

    /**
    Metodi che modificano solo un indice dell'array delle direzioni attribuendo all'elemento che si trova a tale indice
    l'intero passato come parametro
    */
    void setNord(int idArrivo);

    void setSud(int idArrivo);

    void setOvest(int idArrivo);

    void setEst(int idArrivo);


};

#endif // COLLEGAMENTO_HPP_INCLUDED
