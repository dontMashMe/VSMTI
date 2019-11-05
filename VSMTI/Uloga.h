#pragma once
#include <string>
#include <vector>
#include "Zaposlenik.h"
using namespace std;
class Uloga
{
public:
	Uloga(int z, int rm, int u);
	~Uloga();
	string DajImePoID(int n) const;
	string DajImeJedinice(int n) const;
	void IspisiUpravnoVijece() const;
	void IspisiStrucnoVijece() const;
	void IspisiICT() const;
	void IspisiMenadazment() const;
	void IspisiTurizam() const;
	void IspisiTajnistvo() const; 
	void IspisiReferada() const; 
	void IspisiRacunovodstvo() const;
	void IspisiPomocnaTehnicka() const;
	void PregledUstrojstva() const; 
	int zaposlenik;
	int radnoMjesto;
	int uloga;
	void Administracija() const;
};

