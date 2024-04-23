


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
#include <bitset>
#include <unordered_map>


inline int is_straight(int* k);
inline int save_hand_to_map(int* k);
inline int is_straight_bit(int* k);
void Printtaa(int* k, int size);

std::bitset<15> cards_vector;
std::unordered_map<std::bitset<15>, bool> table;


/*
alustetaan: short table{6xxxx} 16bittisten yhdistelmien m��r� (joka bitin paikan indeksi vastaa kyseist� korttia(65536) tai char k�y my�s (short oli n�ytt�j�ll�)

sitten laitetaan short cards (alkaa paikasta toisessa laidassa 5 per�kk�ist� (toisen ��rilaidan kortit)on p��ll�,
sitten siirret��n loopissa yhdell� toiseen suuntaan kaikkia tms..
sitten viel� lis�t��n jos bitit 2,3,4,5, ja �ss�, miss� liek��n p��ll�
kaikki muut j�� pois p��lt�
*/

////open mallia:
// 2^16 mahdollisuutta = 65536!
//char straight_table[65536] = { }; //kaikkia nollia
////0x001f   - 02000 ?
//for (straight_mask)
//
// 
// kun katotaan onko siell�..
//h != 0x1 << k[0] - 2;
//h != 0x1 << [1] - 2;  jne jne 

