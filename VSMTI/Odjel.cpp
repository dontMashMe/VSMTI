#include "pch.h"
#include "Odjel.h"
#include "Zaposlenik.h"
#include "Uloga.h"
#include "tinyxml2.h"
#include <iostream>


Odjel::Odjel(int i, string n):Ustrojstvo(i,n)
{
}
Odjel::~Odjel()
{

}

void Odjel::IspisiJedinicu() 
{
	cout << name << endl;
}
