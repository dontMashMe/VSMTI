#include "pch.h"
#include "ZajednickeSluzbe.h"
#include <iostream>



ZajednickeSluzbe::ZajednickeSluzbe(int i, string n):Ustrojstvo(i,n)
{
}


ZajednickeSluzbe::~ZajednickeSluzbe()
{
}

void ZajednickeSluzbe::IspisiJedinicu()
{
	std::cout << name << endl;
}