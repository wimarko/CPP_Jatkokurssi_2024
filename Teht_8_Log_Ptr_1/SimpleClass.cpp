#include "SimpleClass.h"
#include <iostream>

SimpleClass::SimpleClass(unsigned int id)
{	
	_id = id;
	std::cout << "Simple Class created id: "<<_id << "\n";
}

SimpleClass::~SimpleClass()
{
	std::cout << "Simple Class destructed id: "<<_id << "\n";
}

void SimpleClass::Act()
{
	std::cout << "Simple Class " << this << " is acting\n";
}
