#include "pch.h"
#include "Ustrojstvo.h"
#include <iostream>



Ustrojstvo::Ustrojstvo(int i, string n)
{
	id = i; 
	name = n; 
}


Ustrojstvo::~Ustrojstvo()
{
}

void Ustrojstvo::IspisiJedinicu()
{
	std::cout << name << endl; 
}