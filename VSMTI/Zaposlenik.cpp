#include "pch.h"
#include "Zaposlenik.h"
#include <iostream>
#include <vector>
#include "tinyxml2.h"
#include "Uloga.h"

using namespace tinyxml2;

vector<Zaposlenik*> UcitajZaposlenikssda();


Zaposlenik::Zaposlenik(int i, string n, string s)
{
	id = i; 
	name = n; 
	surname = s;
}


Zaposlenik::~Zaposlenik()
{

}
vector<Uloga*> UcitavanjeUloga()
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

void Zaposlenik::IspisiZaposlenike() const
{
	cout << "**POPIS ZAPOSLENIKA VISOKE SKOLE**" << endl;
	vector<Zaposlenik*> vZaposlenici = UcitajZaposlenikssda();
	cout << "+--------------------------+" << endl;
	for (int p = 0; p < vZaposlenici.size(); p++)
	{
		cout << "|" <<vZaposlenici[p]->id << ". " << vZaposlenici[p] -> name << " " << vZaposlenici[p] -> surname << endl;
		cout << "+--------------------------|" << endl;
	}

}

int Zaposlenik::PronadiZaposlenika() const
{
	vector<Zaposlenik*> vZaposlenici = UcitajZaposlenikssda();
	cout << "Unesi ime/prezime/ImePrezime: "; 
	string name = " "; 
	cin >> name; 
	for (size_t i = 0; i < vZaposlenici.size(); i++)
	{
		if (name == vZaposlenici[i]->name || name == vZaposlenici[i]->surname || name == (vZaposlenici[i]->name +vZaposlenici[i]->surname))
			return vZaposlenici[i]->id;
	}
}
void Zaposlenik::PogledajPojedinogZaposlenika() const
{
	cout << "**POPIS ZAPOSLENIKA VISOKE SKOLE**" << endl;
	Uloga *u1 = new Uloga{ 1,2,3 };
	IspisiZaposlenike();
	int n, zaposlenik;
	//cout << "Odaberite redni broj zaposlenika: ";
	//cin >> n;
	//for (int p = 0; p < vZaposlenici.size(); p++)
	//{
	//	if (n == vZaposlenici[p]->id)
	//	{
	//		zaposlenik = vZaposlenici[p]->id;
	//		break;
	//	}

	//}
	zaposlenik = PronadiZaposlenika();
	system("cls");
	vector<Uloga*> vUloge = UcitavanjeUloga();
	cout << "Zaposlenik/ca: " << u1->DajImePoID(zaposlenik) << "\nZaposlen/a u: " << endl;
	for (int p = 0; p < vUloge.size(); p++)
	{

		if (zaposlenik == vUloge[p]->zaposlenik)
		{
			cout <<"\t " << "-" << u1->DajImeJedinice(vUloge[p]->radnoMjesto) << endl;
		}
		
	}
	delete u1;
}
void Zaposlenik::DodajZaposlenika() const
{
	cout << "**DODAVANJE NOVOG ZAPOSLENIKA**" << endl;
	vector<Zaposlenik*> vZaposlenik = UcitajZaposlenikssda();
	XMLDocument xmlDoc;
	xmlDoc.LoadFile("zaposlenici.xml");
	XMLElement *pRoot = xmlDoc.FirstChildElement("data");
	XMLElement *pElement = xmlDoc.NewElement("Zaposlenik");
	int id = vZaposlenik.size() + 1;
	string name = " ";
	string surname = " ";
	cout << "Ime: ";
	cin >> name;
	cout << "Prezime: ";
	cin >> surname;
	int radnoMjesto = 0, iz = 0;
	cout << "======================================================================" << endl;
	cout << "Odaberite jedinicu u koju zelite smjestiti novo-dodanog zaposlenika." << endl; 
	cout << "Vijeca:" << endl;
	cout << "\t1..Upravno vijece.\n\t2..Strucno vijece." << endl;
	cout << "Dekanat:" << endl;
	cout << "\t3..Dekan.\n\t4..Prodekan za nastavu.\n\t5..Prodekan za razvoj." << endl;
	cout << "Odjeli:" << endl;
	cout << "\t6..Odjel za ICT.\n\t7..Odjel za ekonomiju.\n\t8..Odjel za turizam." << endl;
	cout << "Centri:" << endl;
	cout << "\t9..Centar za informaticku potporu.\n\t10..Centar za knjiznicku izdavacku djelatnost.\n\t11..Centar za upravljanje kvalitetom.\n\t12...Centar za istrazivanje i razvoj." << endl;
	cout << "Sluzbe:";
	cout << "\n\t13..Tajnistvo.\n\t14..Referada.\n\t15..Racunovodstvo.\n\t16..Pomocna tehnicka sluzba." << endl;
	cout << "odabir: ";
	cin >> radnoMjesto;

	pElement->SetAttribute("id", id);
	pElement->SetAttribute("name", name.c_str());
	pElement->SetAttribute("surname", surname.c_str());
	pRoot->InsertEndChild(pElement);
	xmlDoc.SaveFile("zaposlenici.xml");
	XMLDocument xmlDocU;
	xmlDocU.LoadFile("uloge.xml");
	XMLElement *pRootU = xmlDocU.FirstChildElement("data");
	XMLElement *pElementU = xmlDocU.NewElement("Uloga");
	pElementU->SetAttribute("zaposlenik", id);
	pElementU->SetAttribute("radnoMjesto", radnoMjesto);
	pElementU->SetAttribute("uloga", 2);
	pRootU->InsertEndChild(pElementU);
	xmlDocU.SaveFile("uloge.xml");
	cout << "Korisnik uspjesno dodan!" << endl;
}

void Zaposlenik::ObrisiZaposlenika() const
{
	int pomocna = 0, n = 0;
	cout << "Odaberite redni broj zaposlenika kojeg zelite obrisati: ";
	cin >> n;
	XMLDocument oXmlDocument;
	oXmlDocument.LoadFile("zaposlenici.xml");
	XMLElement *pRoot = oXmlDocument.FirstChildElement("data");
	XMLElement *pChild;
	for (pChild = pRoot->FirstChildElement("Zaposlenik"); pChild != NULL; pChild =
		pChild->NextSiblingElement())
	{
		pomocna++;
		if (pomocna == n)
		{
			pRoot->DeleteChild(pChild);
			oXmlDocument.SaveFile("zaposlenici.xml");
			break;
		}
	}
	cout << "Zaposlenik uspjesno obrisan!" << endl;
}

vector<Zaposlenik*> UcitajZaposlenikssda()
{
	vector<Zaposlenik*> vZaposlenici;
	XMLDocument oXmlDocument;
	oXmlDocument.LoadFile("zaposlenici.xml");
	XMLElement *pRoot = oXmlDocument.FirstChildElement("data");
	XMLElement *pChild;
	for (pChild = pRoot->FirstChildElement("Zaposlenik"); pChild != NULL; pChild =
		pChild->NextSiblingElement())
	{
		int id = stoi(pChild->Attribute("id"));
		string name = pChild->Attribute("name");
		string surname = pChild->Attribute("surname");
		vZaposlenici.push_back(new Zaposlenik(id, name, surname));
	}

	return vZaposlenici;
}
