#include "Log_Ptr.h"
#include <ctime>
#include <iostream>


template <class T>
Log_Ptr<T>::Log_Ptr(T* i)
{
	_i = i;
	refs = new int(1);
	std::cout << "omistajuus siirretty " << _i << "\n";
}

template<class T>
Log_Ptr<T>::~Log_Ptr()
{
	
}

template<class T>
T* Log_Ptr<T>::operator->()
{
	return _i;
}

template<class T>
T& Log_Ptr<T>::operator*()
{
	return *_i;
}


/*
Log_Ptr ylläpitää osoitinta viitattuun olioon. Olio voi olla
minkä tahansa tyyppinen (templateluokka).

· Log_Ptr:lle annetaan viitattava olio konstruktorin
parametrina. Konstruktori kirjoittaa vastaavan
rivin lokitiedostoon:
<aikaleima> omistajuus siirretty <viitatun olion 
muistiosoite>

· Viitattu olio tuhotaan Log_Ptr:n destruktorissa.
Destruktori kirjoittaa vastaavan rivin
lokitiedostoon:
<aikaleima> olio tuhottu <viitatun olion muistiosoite>

Log_Ptr:n sijoitusoperaattorin ja kopiokonstrukorin käyttö estetään (vihje:
https://www.geeksforgeeks.org/explicitly-defaulted-deleted-functions-c-11/)
*/

