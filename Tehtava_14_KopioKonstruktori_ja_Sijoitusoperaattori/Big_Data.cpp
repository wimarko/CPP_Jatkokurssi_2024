/*
Toteuta luokka Big_Data, jonka konstruktorin parametrina annetaan varattavan îbufferinî koko tavuina.
Konstruktori varaa muistin malloc:lla, ja destruktori vapauttaa muistin.
Toteuta luokalle kopiokonstruktori ja sijoitusoperaattori, niin ett‰ ao. ohjelmarivit toimivat korrektisti. Eri
oliot eiv‰t siis saa osoittaa samaan bufferiin, vaan tarpeen tullen bufferin sis‰ltˆ kopioidaan toisen olion
bufferiin. Testaa.
Big_Data a(1024);
Big_Data b(1024);
a = a;
a = b;
BigData c(a);*/

//#include <corecrt_malloc.h>
#include <iostream>

//using namespace std;

class Big_Data
{
public :
	Big_Data(unsigned int size)
	{
		_memory_pointer = malloc(size);
		_size = size;
	}

	//kopiokonstruktori
	Big_Data(const Big_Data& orig)
	{
		_memory_pointer = malloc(orig._size);
		_size = orig._size;
		memcpy(_memory_pointer, orig._memory_pointer, _size);
	}

	/* 15
	Toteuta Big_Data-luokalle move-konstruktori ja move-sijoitusoperaattori. N‰m‰ saavat parametrina
	rvalue-referenssin, îvarastavatî sen sis‰llˆn ja sen j‰lkeen îresetoivatî alkuper‰isen rvaluen.:*/

	//move constructor
	Big_Data(Big_Data&& other) noexcept  //this should not throw.. -> noexcept
	{
		_memory_pointer = other._memory_pointer;
		_size = other._size;

		other._memory_pointer = nullptr;
	}

	// Move Assignment Operator 
	Big_Data& operator= (Big_Data&& rhs) noexcept
	{
		free(_memory_pointer);

		//varastaminen
		_memory_pointer = rhs._memory_pointer;
		_size = rhs._size;
		rhs._size = 0;  //t‰n viel‰ vois tehd‰

		//alkup. pointterin resetointi
		rhs._memory_pointer = nullptr;

		return *this;
	}

	//Destro
	~Big_Data()
	{
		free(_memory_pointer);
	}

	//sijoitusoperaattori
	Big_Data& operator= (const Big_Data& rhs)  //Righ_Hand_side
	{
		if (this == &rhs) { return *this; } //sijoitus itseen, ei tehd‰k‰‰n mit‰‰n

		free(_memory_pointer);
		_memory_pointer = malloc(rhs._size);
		_size = rhs._size;
		memcpy(_memory_pointer, rhs._memory_pointer, _size);


		return *this;
	}

	unsigned int GetSize()
	{
		return _size;
	}

private:
	void* _memory_pointer;
	unsigned int _size; //c++, pit‰‰ pit‰‰ lukua kuinka iso oikeasti on..
};

int main()
{

	Big_Data a(1024);
	std::cout << "a:size: " << a.GetSize() << "\n";
	std::cout << "a:address: " << &a << "\n";
	Big_Data b(1024);
	std::cout << "b:address: " << &b << "\n";

	a = b;
	std::cout << "a:address: " << &a << "\n";
	std::cout << "b:address: " << &b << "\n";
	std::cout<<"\n C : \n";
	Big_Data c(1024);
	std::cout << "c:size: " << c.GetSize() << "\n";
	std::cout << "c:address: " << &c << "\n";
	c = Big_Data(2024);
	std::cout << "c:size: " << c.GetSize() << "\n";
	std::cout << "c:address: " << &c << "\n";

	return 0;
}