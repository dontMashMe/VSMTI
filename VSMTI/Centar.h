#pragma once
#include "Ustrojstvo.h"
class Centar :
	public Ustrojstvo
{
public:
	Centar(int i, string n);
	~Centar();
	virtual void IspisiJedinicu();
	int InformatickaPotpora(); 
	int Knjiznica();
	int UpravljanjeKvalitetom();
	int IstrazivanjeRazvoj(); 

};

