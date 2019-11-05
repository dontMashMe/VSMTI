#pragma once
#include <string>
using namespace std;
class Zaposlenik
{
public:
	Zaposlenik(int i, string n, string s);
	~Zaposlenik();
	int id; 
	string name; 
	string surname;
	void IspisiZaposlenike() const;
	void DodajZaposlenika() const;
	void ObrisiZaposlenika() const; 
	void PogledajPojedinogZaposlenika() const;
	int PronadiZaposlenika() const;
};

