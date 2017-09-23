# include <iostream>
# include <stdio.h>
# include <cmath>
using namespace std;

# define WALL_LIMIT .8
# define ROOM_SIZE 16
# define TRIES ROOM_SIZE*ROOM_SIZE
# define UNIT .5
class NoiseGenerator
{

private:
	double v[ROOM_SIZE][ROOM_SIZE];
	//int    c[330];
	int last = 0;
	float eps = .001;
public:
	NoiseGenerator()
	{
		for (int i = 0; i < ROOM_SIZE; ++i) {
			for (int j = 0; j < ROOM_SIZE; ++j) {
				v[i][j] = -2;
			}
		}
		printf("GENERATOR STARTED\n");
	}

	// Funzione di interpolazione. Permette di passare da rumore discreto (a fanculo) a rumore casuale,
	// che è quello che ci serve
	// Usiamo per ora l'interpolazione lineare
	double 	lerp (int a, int b, double weight)
	{
		double out =  a * (1 - weight) + b * weight;
		return out;
	}
	
	double 	discreteNoise (int seed)
	{
		seed = (seed >> 13) ^ seed;
		int mid = (seed * (seed * seed * 60493 + 19990303) + 1376312589) & 0x7fffffff;
		double out = 2.0 - ((double)mid/ 1073741824.0);
		return out;
	}

	double generate(int i, int j)
	{
		

	}
};

char printWall(double i){
	if (i > WALL_LIMIT) return '#';
	else return ' ';
}

int main()
{
	NoiseGenerator n = NoiseGenerator();
	int t = 0;
	double v[TRIES];
	for (int i = 0; i < TRIES; ++i) {
		v[i] = n.generate(i);
		//printf("%f\n", v[i]);
	}

	for (int i = 0; i < TRIES; ++i) {
		if (i % 18 != 0){
			printf("%c", printWall(v[i]));
		} else {
			printf("\n%c", printWall(v[i]));
		}
	}
	return 0;
}


/* DA FARE
+  controllare interpolazione. Valori nel discreto? Salvare e contare valori interpolati
+  interpolazione bilineare
+  stampare e testare interpolazione bilineare
*/