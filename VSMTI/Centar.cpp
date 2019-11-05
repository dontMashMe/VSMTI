#include "pch.h"
#include "Centar.h"
#include "Uloga.h"
#include "tinyxml2.h"
#include <iostream>
#include <vector>
using namespace tinyxml2;
using namespace std; 



Centar::Centar(int i, string n) : Ustrojstvo(i,n)
{
}


Centar::~Centar()
{
}

void Centar::IspisiJedinicu()
{
	std::cout << name << endl;
}

vector<Uloga*> UcitavajUloge();

int Centar::InformatickaPotpora()
{
	vector<Uloga*> vUloge = UcitavajUloge(); 
	for (int p = 0; p < vUloge.size(); p++)
	{
		if (vUloge[p]->radnoMjesto == 9)
			return vUloge[p]->zaposlenik;
	}
}

int Centar::Knjiznica()
{
	vector<Uloga*> vUloge = UcitavajUloge(); 
	for (int p = 0; p < vUloge.size(); p++)
	{
		if (vUloge[p]->radnoMjesto == 10)
			return vUloge[p]->zaposlenik;
	}
}

int Centar::UpravljanjeKvalitetom()
{
	vector<Uloga*> vUloge = UcitavajUloge();
	for (int p = 0; p < vUloge.size(); p++)
	{
		if (vUloge[p]->radnoMjesto == 11)
			return vUloge[p]->zaposlenik;
	}
}

int Centar::IstrazivanjeRazvoj()
{
	vector<Uloga*> vUloge = UcitavajUloge();
	for (int p = 0; p < vUloge.size(); p++)
	{
		if (vUloge[p]->radnoMjesto == 12)
			return vUloge[p]->zaposlenik;
	}
}

vector<Uloga*> UcitavajUloge()
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