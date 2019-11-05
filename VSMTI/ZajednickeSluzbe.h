#pragma once
#include "Ustrojstvo.h"
class ZajednickeSluzbe :
	public Ustrojstvo
{
public:
	ZajednickeSluzbe(int i, string n);
	~ZajednickeSluzbe();
	virtual void IspisiJedinicu();
};

