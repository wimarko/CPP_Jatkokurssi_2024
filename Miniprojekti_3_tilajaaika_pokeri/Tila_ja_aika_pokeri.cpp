/*

  Harjoitus 3

  Optimoi suorien tunnistus. Älä muuta kääntäjäoptioita.
  Pidä ohjelma yksisäikeisenä.

  Vertaa alkuperäistä ja optimoitua versiota:

  - kuinka paljon enemmän muistia optimoitu versio kuluttaa?
  - kuinka paljon nopeammin optimoitu versio toimii?

  Käännös: gcc straight.c -o straight

*/

#include <stdio.h>
#include <time.h>
#include <iostream>
#include <algorithm> // (std::find) std::sort
#include <bitset>
#include <set>  //std::set
#include <vector>
#include <unordered_map>


inline int is_straight(int* k);
inline int is_straight_bitvector(int* k, std::unordered_map<std::bitset<15>, bool> table);

inline int is_quads_or_fullhouse(int* k);
inline int is_quads_or_fullhouse_bitvector(int* k);

void Printtaa(int* k, int size);

std::bitset<15> cards_vector;

std::unordered_map<std::bitset<15>, bool> straight_table;

int suoria = 0;

std::unordered_map<std::bitset<15>, bool> CreateTable()
{

}


int main()
{

#pragma region alustetaanmappi
	int k0, k1, k2, k3, k4; /* Pakan kortit, 0..51*/
	int k[5]; /* Korttien numeroarvot, 2..14*/
	std::unordered_map<std::bitset<15>, bool> table;

	//katsoo onko suora jokaiselle mahdolliselle pokerikädlle
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

						//tyhjennä bittivektori
						cards_vector.reset();

						//pitää ottaa arvot k-kädestä..
						for (int i = 0; i < 5; i++)
						{
							cards_vector.set(k[i]);
						}
						// korttien numeroarvot indekseinä.. 1 on ässä, kuten 14
						if (cards_vector.test(2)) {
							if (cards_vector.test(14))
							{
								cards_vector.set(1);
								cards_vector.reset(14);
							}
						}

						int first_index = -1;
						for (int i = 1; i < 15; i++)
						{

							if (cards_vector.test(i))
							{
								first_index = i;
								/*index_found = true;*/
								break;
							}

						}

						////pienin arvo on jo niin suuri, ettei voida saada suoraa
						if (first_index > 10) 
						{ 
							table[cards_vector] = false;
							break; 
						}

						if (cards_vector.test(first_index + 1) &&
							cards_vector.test(first_index + 2) &&
							cards_vector.test(first_index + 3) &&
							cards_vector.test(first_index + 4))
						{
							table[cards_vector] = true;
						}
						else
						{
							table[cards_vector] = false;
						}

					}
				}
			}
		}
	}
	std::cout << "mapin alustus tehty\n";
#pragma end region
	//alustetaan mappimikälie
	for (int i = 1; i < 11;i++) {
		std::bitset<15> hand;
		hand.set(i);
		hand.set(i + 1);
		hand.set(i + 2);
		hand.set(i + 3);
		hand.set(i + 4);
		straight_table[hand] = true;
		std::cout << "table luotu"<<i<<"-"<<i+4<<"\n";
	}
	/*

	  Käydään läpi kaikki viiden kortin permutaatiot, ja lasketaan
	  kuin monta suoraa (värisuoraa tai tavallista) löytyy.

	  Ks. Wikipedia http://en.wikipedia.org/wiki/Poker_probability :

	  Royal flush     4      combinations
	  Straight flush  36     combinations
	  Straight        10,200 combinations

	  Koska 5 korttia voi olla 5 x 4 x 3 x 2 x 1 = 120 järjestyksessä,
	  pitäisi suoria löytyä (10200 + 36 + 4) x 120 = 1228800 kappaletta.

	*/
	int k0, k1, k2, k3, k4; /* Pakan kortit, 0..51*/
	int k[5]; /* Korttien numeroarvot, 2..14*/
	//int suoria; /* Suorien lkm*/

	int fulls_or_quads;
	unsigned int combinations;
	
	clock_t t1, t2;

	fulls_or_quads = 0;
	combinations = 0;

	t1 = clock();
	

	 //katsoo onko suora jokaiselle mahdolliselle pokerikädlle
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
						combinations++;
						/*std::cout << combinations << "\n";*/
						/*if (is_straight(k))
							++suoria;*/
						if (is_straight_bitvector(k, straight_table))
							++suoria;
						/*if (is_quads_or_fullhouse_bitvector(k)) 
							++fulls_or_quads;*/
					}
				}	
			}
		}
	}
#pragma region omaa_testausta
	////////omaa testausta
	//int kasi[5] = { 3, 3,3, 3, 6};//oma testikäsi
	//////is_straight(kasi);
	////if (is_straight_table(kasi)) ++suoria;
	//if (is_quads_or_fullhouse_bitvector(kasi)) ++fulls_or_quads;

#pragma endregion
	t2 = clock();
	std::cout << "different hands: " << combinations << "\n";
printf("nelosia tai täyskäsiä     : %d kpl (oikea arvo 4368)\n", fulls_or_quads);
	printf("Suoria     : %d kpl (oikea arvo 1228800)\n", suoria);
	printf("Aikaa kului: %.1fs\n", (t2 - t1) / (float)CLOCKS_PER_SEC);

	return 0;
}


/*
  Parametrina 5 pelikortin numeroarvoa k, 2..14 (ei välttämättä
  numerojärjesteyksessä).

  Palauttaa 1, jos numeroarvot voidaan järjestää siten, että
  ne muodostavat suoran (esim. 4,5,6,7,8).

  Huom! Ässää (arvo 14) voidaan käyttää suorissa myös arvona 1
  (esim. 1,2,3,4,5).
*/
inline int is_straight(int* k)
{

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
	//katotaan korttipaikat 1-4, onko seuraava yhdellä isompi?
	for (int i = 0; i < 4; i++)
	{	//eli jos arvo + 1 ei ole sama kuin seuraavan kortin arvo, ei voi olla suora
		if (k[i] + 1 != k[i + 1])
		{
			return 0;
		}
	}
	//1. ajo kesti 70.4 sek, 2. ajo 71.7 sek

	//jos ei lopeteta aikaisemmin, käsi on suora, palautetaan 1
	return 1;
}


//EI valmistu koskaan
inline int is_straight_bitvector(int* k, std::unordered_map<std::bitset<15>, bool> table)
{
	
	//tyhjennä bittivektori
	cards_vector.reset();
	
	//pitää ottaa arvot k-kädestä..
	for (int i = 0; i < 5; i++)
	{
		cards_vector.set(k[i]);
	}
	// korttien numeroarvot indekseinä.. 1 on ässä, kuten 14
	/*if (cards_vector.test(2)) {*/
		if (cards_vector.test(14))
		{
			cards_vector.set(1);
			/*cards_vector.reset(14);*/ //ei muutosta nopeuteen
		}
	/*}*/
	if (straight_table.count(cards_vector)) {
		if (straight_table.at(cards_vector)) {
			std::cout << "loytyi " << suoria << "\n";
			return 1;
		}
	}
	

	return 0;
}



inline int is_quads_or_fullhouse(int* k)
{
	Printtaa(k, 5);
 //yhteensä kahta eri numeroarvoa..
	std::set<int> uniques(k, k + 5);
	if (uniques.size() == 2) { return 1; }
	/*std::cout << uniques.size() << "\n";*/

	return 0;
}

inline int is_quads_or_fullhouse_bitvector(int* k)
{
	//tyhjennä bittivektori
	cards_vector.reset();

	//pitää ottaa arvot k-kädestä..
	for (int i = 0; i < 5; i++)
	{
		cards_vector.set(k[i]);
	}

	if (cards_vector.count() == 2) {
		/*Printtaa(k, 5);*/
		return 1; 
	}

	return 0;
	
}

void Printtaa(int* k, int size)
{
	std::sort(k, k+size);
	/*std::cout << "koko: " << size << "\n";*/
	for (int i = 0; i < size; i++)
	{
		std::cout << k[i] << " ";
	}
	std::cout<<std::endl;
}



