/*

  Harjoitus 1

  Optimoi sini-funktion k�sittely. �l� muuta k��nt�j�optioita.
  Vertaa alkuper�ist� ja optimoitua versiota:

  - kuinka paljon enemm�n muistia optimoitu versio kuluttaa?
  - kuinka paljon nopeammin optimoitu versio toimii?

  K��nn�s: gcc sin.c -lm -o sin

*/

#include <stdio.h>
#include <time.h>
#include <math.h>

#define DEG_TO_RAD(A) (A / 57.296)
#define ITERATIONS 1000000




int main()
{


	double sin_t[360];

	//sin value of 0-359 to an array,
	//doesn't have to be calculated every time, just take value from array
	for (int i = 0; i < 360; i++)
	{
		sin_t[i] = sin(DEG_TO_RAD(i));
	}

	clock_t t1, t2;
	unsigned i, a;
	double val;

	t1 = clock();
	for (i = 0; i < ITERATIONS; ++i)
	{
		for (a = 0; a < 360; ++a)
		{
			/*
			  OptimizeIt!
			*/
			/*val = sin(DEG_TO_RAD(a));*/
			val = sin_t[a]; //take value of sin(a) from array from correct index
		}
	}
	t2 = clock();
	printf("%.1fs\n", (t2 - t1) / (float)CLOCKS_PER_SEC);

	return 0;
}
