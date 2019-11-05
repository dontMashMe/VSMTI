#pragma once
#include "Zaposlenik.h"
#include <string>
#include <vector>
using namespace std;
class Ustrojstvo
{
public:
	Ustrojstvo(int i, string n);
	~Ustrojstvo();
	int id;
	string name;
	int members;
protected:
	virtual void IspisiJedinicu();
};
