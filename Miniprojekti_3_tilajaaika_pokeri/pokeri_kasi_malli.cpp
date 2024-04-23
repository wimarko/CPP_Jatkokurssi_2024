


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
void Printtaa(int* k, int size);

std::bitset<15> cards_vector;
std::unordered_map<std::bitset<15>, bool> table;


/*
alustetaan: short table{6xxxx} 16bittisten yhdistelmien määrä (joka bitin paikan indeksi vastaa kyseistä korttia(65536) tai char käy myös (short oli näyttäjällä)

sitten laitetaan short cards (alkaa paikasta toisessa laidassa 5 peräkkäistä (toisen äärilaidan kortit)on päällä,
sitten siirretään loopissa yhdellä toiseen suuntaan kaikkia tms..
sitten vielä lisätään jos bitit 2,3,4,5, ja ässä, missä liekään päällä
kaikki muut jää pois päältä
*/

////open mallia:
// 2^16 mahdollisuutta = 65536!
//char straight_table[65536] = { }; //kaikkia nollia
////0x001f   - 02000 ?
//for (straight_mask)
//
// 
// kun katotaan onko siellä..
//h != 0x1 << k[0] - 2;
//h != 0x1 << [1] - 2;  jne jne 

