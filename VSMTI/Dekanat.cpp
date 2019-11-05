#include "pch.h"
#include "Dekanat.h"
#include "Zaposlenik.h"
#include "tinyxml2.h"
#include "Uloga.h"
#include <iostream>
#include <vector>
using namespace std;
using namespace tinyxml2;


Dekanat::Dekanat(int i, string n) : Ustrojstvo(i, n)
{

}


Dekanat::~Dekanat()
{
}

vector<Uloga*> UcitajUloges();

void Dekanat::IspisiJedinicu() 
{
	cout << name << endl;
}

int Dekanat::Dekan() const
{
	int n;
	vector<Uloga*> vUloga = UcitajUloges();
	for (int p = 0; p < vUloga.size(); p++)
	{
		if (vUloga[p]->radnoMjesto == 3)
			n = vUloga[p]->zaposlenik;
	}
	return n;

}

int Dekanat::ProDekanNastava() const
{
	int n; 
	vector<Uloga*> vUloga = UcitajUloges();
	for (int p = 0; p < vUloga.size(); p++)
	{
		if (vUloga[p]->radnoMjesto == 4)
			n = vUloga[p]->zaposlenik;
	}
	return n;
}

int Dekanat::ProDekanRazvoj() const
{
	int n;
	vector<Uloga*> vUloga = UcitajUloges();
	for (int p = 0; p < vUloga.size(); p++)
	{
		if (vUloga[p]->radnoMjesto == 5)
			n = vUloga[p]->zaposlenik;
	}
	return n;
}

vector<Uloga*> UcitajUloges()
{
	vector<Uloga*> vUloge;
	XMLDocument oXmlDocument;
	oXmlDocument.LoadFile("uloge.xml");
	XMLElement *pRoot = oXmlDocument.FirstChildElement("data");
	XMLElement *pChild;
	for (pChild = pRoot->FirstChildElement("Uloga"); pChild != NULL; pChild =
		pChild->NextSiblingElement())
	{
		int id = stoi(pChild->Attribute("zaposlenik"));
		int rm = stoi(pChild->Attribute("radnoMjesto"));
		int u = stoi(pChild->Attribute("uloga"));
		vUloge.push_back(new Uloga(id, rm, u));
	}
	return vUloge;
}
