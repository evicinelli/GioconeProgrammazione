#ifndef COLLEGAMENTO_HPP_INCLUDED
#define COLLEGAMENTO_HPP_INCLUDED

class Collegamento{
protected:
    int id;

    /**
        direzioni[0]->N
        direzioni[1]->S
        direzioni[2]->O
        direzioni[3]->E
    */
    int direzioni[4];

public:
    Collegamento(int j);

    Collegamento();

    int getId();

    void setId(int i);

    void getDirezioni(int a[4]);

    void setDirezioni(int a[4]);

    void setNord(int idArrivo);

    void setSud(int idArrivo);

    void setOvest(int idArrivo);

    void setEst(int idArrivo);


};

#endif // COLLEGAMENTO_HPP_INCLUDED
