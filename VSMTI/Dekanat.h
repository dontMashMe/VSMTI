#pragma once
#include "Ustrojstvo.h"
class Dekanat :
	public Ustrojstvo
{
public:
	Dekanat(int i, string n);
	~Dekanat();
	void IspisiDekanat() const;
	int Dekan() const; 
	int ProDekanNastava() const; 
	int ProDekanRazvoj() const;
	virtual void IspisiJedinicu();
};

