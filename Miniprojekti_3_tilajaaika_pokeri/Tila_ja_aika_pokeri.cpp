/*

  Harjoitus 3

  Optimoi suorien tunnistus. �l� muuta k��nt�j�optioita.
  Pid� ohjelma yksis�ikeisen�.

  Vertaa alkuper�ist� ja optimoitua versiota:

  - kuinka paljon enemm�n muistia optimoitu versio kuluttaa?
  - kuinka paljon nopeammin optimoitu versio toimii?

  K��nn�s: gcc straight.c -o straight

*/

#include <stdio.h>
#include <time.h>
#include <iostream>
#include <algorithm> // (std::find) std::sort

inline int is_straight(int* k);
void Printtaa(int* k, int size);



int main()
{
	/*

	  K�yd��n l�pi kaikki viiden kortin permutaatiot, ja lasketaan
	  kuin monta suoraa (v�risuoraa tai tavallista) l�ytyy.

	  Ks. Wikipedia http://en.wikipedia.org/wiki/Poker_probability :

	  Royal flush     4      combinations
	  Straight flush  36     combinations
	  Straight        10,200 combinations

	  Koska 5 korttia voi olla 5 x 4 x 3 x 2 x 1 = 120 j�rjestyksess�,
	  pit�isi suoria l�yty� (10200 + 36 + 4) x 120 = 1228800 kappaletta.

	*/
	int k0, k1, k2, k3, k4; /* Pakan kortit, 0..51*/
	int k[5]; /* Korttien numeroarvot, 2..14*/
	int suoria; /* Suorien lkm*/
	
	clock_t t1, t2;

	t1 = clock();
	
	suoria = 0;
	// //katsoo onko suora jokaiselle mahdolliselle pokerik�dlle
	for (k0 = 0; k0 < 52; ++k0) {
		for (k1 = 0; k1 < 52; ++k1) {
			if (k1 == k0)continue;
			for (k2 = 0; k2 < 52; ++k2) {
				if (k2 == k0 || k2 == k1)continue;
				for (k3 = 0; k3 < 52; ++k3) {
					if (k3 == k0 || k3 == k1 || k3 == k2)continue;
					for (k4 = 0; k4 < 52; ++k4) {
						if (k4 == k0 || k4 == k1 || k4 == k2 || k4 == k3)continue;

						/*
						  Lasketaan korttien numeroarvot ja
						  tarkistetaan onko suora.
						*/
						k[0] = (k0 % 13) + 2;
						k[1] = (k1 % 13) + 2;
						k[2] = (k2 % 13) + 2;
						k[3] = (k3 % 13) + 2;
						k[4] = (k4 % 13) + 2;
						if (is_straight(k))
							++suoria;
					}
				}
			}
		}
	}
	////omaa testausta
	//int kasi[5] = { 4, 2, 3, 14, 13 };//oma testik�si
	//is_straight(kasi);
	t2 = clock();
	printf("Suoria     : %d kpl (oikea arvo 1228800)\n", suoria);
	printf("Aikaa kului: %.1fs\n", (t2 - t1) / (float)CLOCKS_PER_SEC);

	return 0;
}


/*
  Parametrina 5 pelikortin numeroarvoa k, 2..14 (ei v�ltt�m�tt�
  numeroj�rjesteyksess�).

  Palauttaa 1, jos numeroarvot voidaan j�rjest�� siten, ett�
  ne muodostavat suoran (esim. 4,5,6,7,8).

  Huom! �ss�� (arvo 14) voidaan k�ytt�� suorissa my�s arvona 1
  (esim. 1,2,3,4,5).
*/
inline int is_straight(int* k)
{
	// TODO
	/*int* kasi[5];*/

	//sorttaa ekaksi.. ja kato onko 0 indeksi 2, jos on, niin jos on 14 = 1
	std::sort(k, k+5);
	//jos kakkonen, kato onko 14 ja laita 1:ksi
	if (k[0] == 2)
	{
		if (k[4] == 14) {
			k[4] = 1;
			std::sort(k, k + 5);
		}		
	}
	/*Printtaa(k,5);*/
	//katotaan korttipaikat 1-4, onko seuraava yhdell� isompi?
	for (int i = 0; i < 4; i++)
	{	//eli jos arvo + 1 ei ole sama kuin seuraavan kortin arvo, ei voi olla suora
		if (k[i] + 1 != k[i + 1])
		{
			return 0;
		}
	}
	//1. ajo kesti 70.4 sek, 2. ajo 71.7 sek


//Bittitaulukko?
//pit�� olla globaali lista, koko 14, booleaneja?

//kato onko kakkosta
	//jos on, ja on 14, laita se ykk�seen..?

//


	return 1;
}

void Printtaa(int* k, int size)
{
	std::cout << "koko: " << size << "\n";
	for (int i = 0; i < size; i++)
	{
		std::cout << k[i] << " ";
	}
	std::cout<<std::endl;
}

// t�ysk�si ja pari.. siin� bittitaulukossa on silloin vain kaksi bitti� p��ll�! kahta eri arvoa siis..

