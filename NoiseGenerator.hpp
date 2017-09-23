#ifndef NOISEGENERATOR_HPP_INCLUDED
#define NOISEGENERATOR_HPP_INCLUDED


double integerNoise(int a)
{
	a = (a >> 13) ^ a;
	double out = 2.0 - ((double)((a * (a * a * 60493 + 19990303) + 1376312589) & 0x7fffffff) / 1073741824.0);
	return out;
}

double descreteNoise(int i, int j, int span, int seed)
{
	return integerNoise(seed + (span * i + j));
}

#endif // NOISEGENERATOR_HPP_INCLUDED
