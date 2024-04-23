


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
#include <unordered_map>


inline int is_straight(int* k);
inline int save_hand_to_map(int* k);
inline int is_straight_bit(int* k);
inline int new_straight_bitcheck(int* k);
void Printtaa(int* k, int size);
std::bitset<15> cards_vector;
std::unordered_map<std::bitset<15>, bool> table;


/*
alustetaan: short table{6xxxx} 16bittisten yhdistelmien määrä (joka bitin paikan indeksi vastaa kyseistä korttia(65536) tai char käy myös (short oli näyttäjällä)

sitten laitetaan short cards (alkaa paikasta toisessa laidassa 5 peräkkäistä (toisen äärilaidan kortit)on päällä, sitten siirretään loopissa yhdellä toiseen suuntaan kaikkia tms..
sitten vielä lisätään jos bitit 2,3,4,5, ja ässä, missä liekään päällä
kaikki muut jää pois päältä
*/


char hand_table[65536] = { }; //kaikki nollia

//ChatGPT kertoi miten bitwise operaatiolla:

uint16_t straight_hand = 15872;  //0011 1110 0000 0000  -> 14,13,12, 11,10 bits on, others off

//iterate through all positions until to 6,5,4,3,2 and add to array


int main()
{
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
	int suoria; /* Suorien lkm*/
	int talletettuja_suoria = 0;

	clock_t t1, t2;

	suoria = 0;
	int size = 1;
	////open mallia:
// 2^16 mahdollisuutta = 65536!


////0x001f   - 02000 ?
//for (straight_mask)
//
// 
// kun katotaan onko siellä..
//h |= 0x1 << k[0] - 2;
//h |= 0x1 << [1] - 2;  jne jne 
	std::cout << "aletaan suorien talletus\n";
	for (int i = 0; i <= 8; ++i)
	{
		hand_table[straight_hand] = 1;		//mark the pattern in the array

		straight_hand >>= 1;		// RIght-shift the bit pattern by 1 position
	}

 

	hand_table[8222] = 1;  //5,4,3,2,1 (missä ässä on ykklönen, lisätään myös

	/*for (int i = 0; i < 65536; ++i) {
		if (hand_table[i])
		{
			std::cout<< i << " = " << hand_table[i] << std::endl;
		}
		
	}
	return 0;*/

	std::cout << "aletaan tarkistus\n";
	t1 = clock();
	//nyt vasta katotaan onko suoria , mappia käyttäen..
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
						/*if (is_straight(k))
							++suoria;*/
						/*if (is_straight_bit(k))
							++suoria;*/
						if (new_straight_bitcheck(k))
						{
							suoria++;
						}
						
					}
				}
			}
		}
	}

	t2 = clock();
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
	std::sort(k, k + 5);
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


#pragma region bitmap_yrityksia
inline int save_hand_to_map(int* k)
{
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

	/*std::cout << "indexi on " << first_index << "\n";*/

	//ei pitäisi loopata, pitäisi vaan kattoa suoraan indeksejä... duh.. Eli loop unroll kannattaa käyttää jos voi!
	// 
	////pienin arvo on jo niin suuri, ettei voida saada suoraa
	if (first_index > 10) { return 0; }

	if (cards_vector.test(first_index + 1) &&
		cards_vector.test(first_index + 2) &&
		cards_vector.test(first_index + 3) &&
		cards_vector.test(first_index + 4))
	{
		table[cards_vector] = true;
		return 1;
	}
	else
	{
		table[cards_vector] = false;
	}
	//1. ajo aika 40.2 sek, 2. ajo 39.4 sek //jos kattoi tällä tavalla...
	//nyt siis vaan tallennettaan mappiin onko suora vai ei..
	return 0;
}

inline int is_straight_bit(int* k)
{
	cards_vector.reset();
	//pitää ottaa arvot k-kädestä..
	for (int i = 0; i < 5; i++)
	{
		cards_vector.set(k[i]);
	}

	if (table[cards_vector] == true) return 1;

	else return 0;

}



void Printtaa(int* k, int size)
{
	std::sort(k, k + size);
	/*std::cout << "koko: " << size << "\n";*/
	for (int i = 0; i < size; i++)
	{
		std::cout << k[i] << " ";
	}
	std::cout << std::endl;
}
#pragma endregion bitmap_yrityksia


inline int new_straight_bitcheck(int* k)
{

	uint16_t hand = 0;

	hand |= (0x1 << (k[0] - 1));  //-1 because my index 0 = 0, and index 1 = 1, "normally" it would be hand |= (0x1 << (k[0] - 2)); and so on..
	hand |= (0x1 << (k[1] - 1));
	hand |= (0x1 << (k[2] - 1));
	hand |= (0x1 << (k[3] - 1));
	hand |= (0x1 << (k[4] - 1));

	return hand_table[hand];
}

// täyskäsi ja pari.. siinä bittitaulukossa on silloin vain kaksi bittiä päällä! kahta eri arvoa siis..