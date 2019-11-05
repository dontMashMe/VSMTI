#pragma once
#include "Ustrojstvo.h"
class Odjel :
	public Ustrojstvo
{
public:
	Odjel(int i, string n);
	~Odjel();
	virtual void IspisiJedinicu();

};

