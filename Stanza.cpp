class Stanza{
    protected:
        int matrice[5][5];
        Stanza *nord;
        Stanza *sud;
        Stanza *ovest;
        Stanza *est;
    public:
        copiaMatrice(int dest[5][5], int src[5][5]){

        }

        Stanza(int m [5][5]){
           this->copiaMatrice(matrice, m);
        }



};
