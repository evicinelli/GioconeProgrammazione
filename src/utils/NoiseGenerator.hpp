# include <stdlib.h>
# include <limits.h>
#ifndef NOISEGENERATOR_HPP_INCLUDED
#define NOISEGENERATOR_HPP_INCLUDED


double integerNoise(int a)
{
    a = (a >> 13) ^ a; /* rshift(a, 13) XOR a */
    double out = 2.0 - ((double)((a * (a * a * 60493 + 19990303) + 1376312589) & 0x7fffffff) / 1073741824.0);
    return out;
}

/* Ritorna il rumore a partire da una coppia <i, j> Span è la larghezza della matrice, perchè la
 * tratta come un array lungo DIMENSIONE*DIMENSIONE, mentre seed mi shifta la funzione del rumore
 * verso destra o verso sinistra */
double descreteNoise(int i, int j, int span, int seed)
{
    if (seed == 0) seed = rand() % INT_MAX;
    return integerNoise(seed + (span * i + j));
}

#endif // NOISEGENERATOR_HPP_INCLUDED
