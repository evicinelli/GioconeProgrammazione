# include <iostream>
# include <stdio.h>
# include <cmath>
using namespace std;

# define WALL_LIMIT 1.47
# define ROOM_SIZE 16
# define TRIES ROOM_SIZE*ROOM_SIZE
# define UNIT .5
class NoiseGenerator
{

private:
	double v[330];
	int    c[330];
	int last = 0;
	float eps = .001;
public:
	NoiseGenerator()
	{
		for (int i = 0; i < 330; ++i)
		{
			v[i] = 0;
			c[i] = 0;
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
		//save(out);
		return out;
	}

	double generate(int i)
	{
		/*int x1 = discreteNoise(i);
		int x2 = discreteNoise(i + 3);
		return lerp(x1, x2, .5);*/
		return discreteNoise(i);
	}

	// si salva i risultati e conta quanti sono simili, per capire un po' come si distribuisce la faccenda (a scopo statistico per quando dovremo usare i valori giusti per i numeri)
	void save(double in) 
	{
		bool success;
		in = abs(in);
		if (last == 0) {
			v[last] = in;
			++last;
		} else {
			for (int i = 0; i < 330; ++i) {
				if (abs (in - abs(v[i])) < eps) {
					++c[i];
					success = true;
					printf("%f già visto %d volte con %f (scarto di %f)\n",in, c[i], v[i], (abs (in - abs(v[i]))));
				}
			}
			if (!success){
				printf("nuovo\n");
				++last;
				v[last] = in;
				++c[last];
			}
		}
	}
};

char* printWall(double i){
	if (i > WALL_LIMIT) return "# ";
	else return ". ";
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
			printf("%s", printWall(v[i]));
		} else {
			printf("\n%s", printWall(v[i]));
		}
	}
	return 0;
}


/* DA FARE
+  controllare interpolazione. Valori nel discreto? Salvare e contare valori interpolati
+  interpolazione bilineare
+  stampare e testare interpolazione bilineare
*/