#include "pch.h"
#include "Uloga.h"
#include "tinyxml2.h"
#include "Dekanat.h"
#include "Odjel.h"
#include "Centar.h"
#include "ZajednickeSluzbe.h"
#include <iostream>
#include <algorithm>
using namespace tinyxml2;



Uloga::Uloga(int z, int rm, int u)
{
	zaposlenik = z; 
	radnoMjesto = rm; 
	uloga = u; 
}


Uloga::~Uloga()
{
}

vector<Uloga*> UcitajUlogee();
vector<Centar*> UcitajCentre();
vector<Zaposlenik*> UcitajZaposlenikee();
vector<Odjel*> UcitajOdjele();
vector<Dekanat*> UcitajDekanat();
vector<ZajednickeSluzbe*> UcitajSluzbe();

string Uloga::DajImeJedinice(int n) const
{
	vector<string> jedinice = { "Upravno vijece", "Strucno vijece", "Dekan", "Prodekan za nastavu", "Prodekan za razvoj", "Odjel za ICT", "Odjel za ekonomiju", "Odjel za turizam", "Centar za informaticku potporu", "Centar za knjiznicku i izdavacku djelatnost", "Centar za upravljanje kvalitetom", "Centar za istrazivanje i razvoj", "Tajnistvo", "Referada", "Racunovodstvo", "Pomocna tehnicka sluzba" };
	int counter = 0; 
	for (int p = 0; p < jedinice.size(); p++)
	{
		counter++; 
		if (n == counter)
		{
			return jedinice[p];
		}
	}
}

void Uloga::Administracija() const
{
	vector<int> radnaMjesta;
	vector<Uloga*> vUloge = UcitajUlogee();
	vector<Zaposlenik*> vZaposlenik = UcitajZaposlenikee();
	int novoRadnoMjesto, n, zaposlenik, pomocna=0, counter = 0, pozicija;
	Zaposlenik *z1 = new Zaposlenik{ 1, "n", "n" };
	XMLDocument oXmlDocument;
	oXmlDocument.LoadFile("uloge.xml");
	XMLElement *pRoot = oXmlDocument.FirstChildElement("data");
	XMLElement *pChild;
	z1->IspisiZaposlenike();
	cout << "odaberi redni broj: ";
	vector<int> zaposlenici;
	for (int i = 0; i < vZaposlenik.size(); i++)
	{
		zaposlenici.push_back(vZaposlenik[i]->id);
	}
	cin >> n;
	while (find(zaposlenici.begin(), zaposlenici.end(), n) == zaposlenici.end())
	{
		cout << "Pogresan odabir!" << endl;
		cout << "odabir:"; 
		cin >> n; 
	}
	for (int p = 0; p < vZaposlenik.size(); p++)
	{
		if (n == vZaposlenik[p]->id)
			zaposlenik = vZaposlenik[p]->id;
	}
	n = 0;
	system("cls");
	cout << "Zelite li obrisati ili dodati radno mjesto zaposleniku: " << DajImePoID(zaposlenik) << "?"<<endl;
	cout << "1..Dodavanje radnog mjesta.\n2..Brisanje radnog mjesta." << endl;
	cout << "odabir:";
	cin >> n; 
	while (n != 1 && n != 2)
	{
		cout << "Pogresan odabir!" << endl;
		cout << "odabir:";
		cin >> n;
	}
	if (n == 1)
	{
		system("cls");
		//ispis svih radnih mjesta gdje je zaposlenik trenutno zaposlen 
		cout << "Zaposlenik/ca: " << DajImePoID(zaposlenik) << "\nZaposlen/a u: " << endl;
		for (int p = 0; p < vUloge.size(); p++)
		{
			if (zaposlenik == vUloge[p]->zaposlenik)
			{
				radnaMjesta.push_back(vUloge[p]->radnoMjesto);
				cout << "\t " << "-" << DajImeJedinice(vUloge[p]->radnoMjesto) << endl;
			}
		}
		cout << "======================================================================" << endl;
		cout << "Odaberite jedinicu u koju zelite dodati zaposlenika: " << DajImePoID(zaposlenik) << endl;
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
		cin >> novoRadnoMjesto;
		//provjera jeli zaposlenik vec zaposlen na odabranom radnom mjestu 
		//prolazi kroz vektor radnaMjesta i trazi novoRadnoMjesto, ako ga pronades ponovno trazi unos
		while (find(radnaMjesta.begin(), radnaMjesta.end(), novoRadnoMjesto) != radnaMjesta.end())
		{
			cout << "Korisnik je vec zaposlen u toj jedinici!" << endl;
			cout << "odabir: ";
			cin >> novoRadnoMjesto;
		}

		//dekanat 3,4,5 ; centri 9,10,11,12
		//vJedini sadrzi id-eve jedinica koje imaju samo jednog ili dva èlana, pa se dodavanjem novih mora obrisati stari zaposlenik. 
		vector<int> vJedini = { 3,4,5,9,10,11,12 };
		//pronadi novoRadnoMjesto u vektoru vJedini, ako ga ne pronades samo dodaj novog zaposlenika
		if (find(vJedini.begin(), vJedini.end(), novoRadnoMjesto) != vJedini.end())
		{
			if (novoRadnoMjesto == 3 || novoRadnoMjesto == 4 || novoRadnoMjesto == 5)
				cout << "Odabirom novog dekana brise se stari, zelite li nastaviti? [Y]/[N]: ";
			else
				cout << "Odabirom novog voditelja centra brise se stari, zelite li nastaviti? [Y]/[N]: ";
			char odb;
			cin >> odb;
			if (odb == 'Y')
			{
				//pronadi poziciju uloge u XMLu
				for (int p = 0; p < vUloge.size(); p++)
				{				
					counter++;
					if (novoRadnoMjesto == vUloge[p]->radnoMjesto)
						pozicija = counter;
				}
				//cout << pozicija << endl;
				//obrisi child element uloge pomocu gore dobivene pozicije  
				for (pChild = pRoot->FirstChildElement("Uloga"); pChild != NULL; pChild =
					pChild->NextSiblingElement())
				{
					pomocna++;
					if (pomocna == pozicija)
					{
						pRoot->DeleteChild(pChild);
						oXmlDocument.SaveFile("uloge.xml");
						break;
					}

				}

				//spremi novu ulogu u XML 
				XMLElement *pElement = oXmlDocument.NewElement("Uloga");
				pElement->SetAttribute("zaposlenik", zaposlenik);
				pElement->SetAttribute("radnoMjesto", novoRadnoMjesto);
				pElement->SetAttribute("uloga", 1);
				pRoot->InsertEndChild(pElement);
				oXmlDocument.SaveFile("uloge.xml");
				cout << "Zaposlenik uspjesno dodan u novu jedinicu!" << endl;
			}
			else
				return;

		}
		//tajnistvo, referada, racunovodstvo
		else if (novoRadnoMjesto == 13 || novoRadnoMjesto == 14 || novoRadnoMjesto == 15)
		{
			int novaUloga;
			//tajnistvo 
			if (novoRadnoMjesto == 13)
			{
				cout << "Zelite li zaposlenika dodati kao tajnika/cu Visoke skole ili administrativnu tajnicu?" << endl;
				cout << "1..Voditelj\n2..Strucni referent." << endl;
			}
			//referada, racunovodstvo oboje imaju "voditelja" i "strucnog referenta"
			else if (novoRadnoMjesto == 14 || novoRadnoMjesto == 15)
			{
				cout << "Zelite li zaposlenika dodati kao voditelja/icu ili strucnog referenta?" << endl;
				cout << "1..Voditelj\n2..Strucni referent." << endl;
			}
			cout << "odabir: ";
			cin >> novaUloga;
			while (novaUloga != 1 && novaUloga != 2)
			{
				cout << "Pogresan unos." << endl;
				cout << "odabir: ";
				cin >> novaUloga;
			}
			if (novaUloga == 1)
			{
				for (int p = 0; p < vUloge.size(); p++)
				{
					counter++;
					if (novoRadnoMjesto == vUloge[p]->radnoMjesto && vUloge[p]->uloga == 1)
						pozicija = counter;
				}
				for (pChild = pRoot->FirstChildElement("Uloga"); pChild != NULL; pChild =
					pChild->NextSiblingElement())
				{
					pomocna++;
					if (pomocna == pozicija)
					{
						pRoot->DeleteChild(pChild);
						oXmlDocument.SaveFile("uloge.xml");
						break;
					}
				}
			}
			else if (novaUloga == 2)
			{
				for (int p = 0; p < vUloge.size(); p++)
				{
					counter++;
					if (novoRadnoMjesto == vUloge[p]->radnoMjesto && vUloge[p]->uloga == 2)
						pozicija = counter;
				}
				for (pChild = pRoot->FirstChildElement("Uloga"); pChild != NULL; pChild =
					pChild->NextSiblingElement())
				{
					pomocna++;
					if (pomocna == pozicija)
					{
						pRoot->DeleteChild(pChild);
						oXmlDocument.SaveFile("uloge.xml");
						break;
					}
				}
			}
			XMLElement *pElement = oXmlDocument.NewElement("Uloga");
			pElement->SetAttribute("zaposlenik", zaposlenik);
			pElement->SetAttribute("radnoMjesto", novoRadnoMjesto);
			pElement->SetAttribute("uloga", novaUloga);
			pRoot->InsertEndChild(pElement);
			oXmlDocument.SaveFile("uloge.xml");
			cout << "Zaposlenik uspjesno dodan u novu jedinicu!" << endl;

		}
		else
		{
			XMLElement *pElement = oXmlDocument.NewElement("Uloga");
			pElement->SetAttribute("zaposlenik", zaposlenik);
			pElement->SetAttribute("radnoMjesto", novoRadnoMjesto);
			pElement->SetAttribute("uloga", 2);
			pRoot->InsertEndChild(pElement);
			oXmlDocument.SaveFile("uloge.xml");
			cout << "Zaposlenik uspjesno dodan u novu jedinicu!" << endl;
		}
	}

	else if (n == 2)
	{
		int rbr = 0;
		n = 0;
		system("cls");
		cout << "Zaposlenik/ca: " << DajImePoID(zaposlenik) << "\nZaposlen/a u: " << endl;
		//ispis svih radnih mjesta gdje je zaposlenik trenutno zaposlen 
		for (int p = 0; p < vUloge.size(); p++)
		{
			if (zaposlenik == vUloge[p]->zaposlenik)
			{
				rbr++;
				radnaMjesta.push_back(vUloge[p]->radnoMjesto);
				cout << "\t" <<rbr << ". " << DajImeJedinice(vUloge[p]->radnoMjesto) << endl;
			}
		}
		cout << "odaberite redni broj: ";
		cin >> n;
		int radnoMjestoDel;
		//dobivanje id-a radnog mjesta preko odabira rednog broja
		for (int p = 0; p < radnaMjesta.size(); p++)
		{
			counter++;
			if (n == counter)
			{
				radnoMjestoDel = radnaMjesta[p];
			}
		}
		counter = 0; //potrebno resetirati counter na 0 jer se gore ikrementira 

		//pronalazak pozicije uloge u XML koju zelimo obrisati  
		for (int p = 0; p < vUloge.size(); p++)
		{
			counter++;
			if (zaposlenik == vUloge[p]->zaposlenik && radnoMjestoDel == vUloge[p]->radnoMjesto)
			{
				pozicija = counter;
			}
		}
		//brisanje child elementa pomoæu gore dobivene pozicije
		for (pChild = pRoot->FirstChildElement("Uloga"); pChild != NULL; pChild =
			pChild->NextSiblingElement())
		{
			pomocna++;
			if (pomocna == pozicija)
			{
				pRoot->DeleteChild(pChild);
				oXmlDocument.SaveFile("uloge.xml");
				break;
			}
		}
		cout << "Radno mjesto uspješno obrisano!" << endl;

		
	}

}
void Uloga::PregledUstrojstva() const
{
	int n=0, rbr = 0, iz=0;
	Dekanat *d1 = new Dekanat{ 1, "n"};
	Centar *c1 = new Centar{1, "n"};
	vector<Dekanat*> vDekanat = UcitajDekanat();
	vector<Odjel*> vOdjeli = UcitajOdjele();
	vector<Centar*> vCentri = UcitajCentre();
	vector<ZajednickeSluzbe*> vSluzbe = UcitajSluzbe();
	cout << "1..Upravno vijece" << "\n2..Strucno vijece" << "\n3..Dekanat" << "\n4..Odjeli" << "\n5..Centri" << "\n6..Zajednicke sluzbe" << endl;
	cout << "Za detaljan pregled jedinice ustrojstva odaberite redni broj." << endl;
	cout << "odabir: ";
	cin >> n;
	switch (n)
	{
	case 1: 
		IspisiUpravnoVijece();
		break;
	case 2:
		IspisiStrucnoVijece(); 
		break; 
	case 3: 
		system("cls");
		for (int p = 0U; p < vDekanat.size(); p++)
		{
			rbr++;
			cout << rbr << ". ";
			vDekanat[p]->IspisiJedinicu();
		}
		cout << "odabir: ";
		cin >> iz;
		switch (iz)
		{
		case 1:
			cout << "Dekan Visoke skole: " << DajImePoID(d1->Dekan()) << endl;
			break;
		case 2:
			cout << "Prodekan za nastavu: " << DajImePoID(d1->ProDekanNastava()) << endl;
			break;
		case 3:
			cout << "Prodekan za razvoj: " << DajImePoID(d1->ProDekanRazvoj()) << endl;
			break;		
		}
		break;
	case 4:
		system("cls");
		for (int p = 0; p < vOdjeli.size(); p++)
		{
			rbr++;
			cout << rbr << ". ";
			vOdjeli[p]->IspisiJedinicu();
		}
		cout << "odabir: ";
		cin >> iz;
		switch (iz)
		{
		case 1:
			IspisiICT();
			break;
		case 2:
			IspisiMenadazment();
			break;
		case 3:
			IspisiTurizam();
			break;
		}
		break;
	case 5:
		system("cls");
		for (int p = 0; p < vCentri.size(); p++)
		{
			rbr++;
			cout << rbr << ". ";
			vCentri[p]->IspisiJedinicu();
		}
		cout << "odabir: ";
		cin >> iz;
		switch (iz)
		{
		case 1:
			cout << "Voditelj centra: " << DajImePoID(c1->InformatickaPotpora()) << endl;
			break;
		case 2:
			cout << "Voditelj centra: " << DajImePoID(c1->Knjiznica()) << endl;
			break;
		case 3:
			cout << "Voditelj centra: " << DajImePoID(c1->UpravljanjeKvalitetom()) << endl;
			break;
		case 4:
			cout << "Voditelj centra: " << DajImePoID(c1->IstrazivanjeRazvoj()) << endl;
			break;
		}
		break;
	case 6:
		system("cls");
		for (int p = 0; p < vSluzbe.size(); p++)
		{
			rbr++;
			cout << rbr << ". ";
			vSluzbe[p]->IspisiJedinicu();
		}
		cout << "odabir: ";
		cin >> iz;
		switch (iz)
		{
		case 1:
			IspisiTajnistvo();
			break;
		case 2:
			IspisiReferada();
			break;
		case 3:
			IspisiRacunovodstvo();
			break;
		case 4:
			IspisiPomocnaTehnicka();
			break;
		}
		break;
	default:
		cout << "Pogresan unos." << endl;
	}
	delete d1, c1;
}

string Uloga::DajImePoID(int n) const
{
	vector<Zaposlenik*> vZaposlenici = UcitajZaposlenikee();
	string imeprezime = " "; 
	for (int p = 0; p < vZaposlenici.size(); p++)
	{
		if (n == vZaposlenici[p]->id)
			imeprezime = vZaposlenici[p]->name + " " + vZaposlenici[p]->surname;
	}
	return imeprezime;
}

void Uloga::IspisiTajnistvo() const
{
	vector<Uloga*> vUloge = UcitajUlogee();
	int rbr = 0;
	string tajnica = " ", adminTajnica = " ";
	system("cls");
	cout << "**CLANOVI TAJNISTVA**" << endl;
	for (int p = 0; p < vUloge.size(); p++)
	{	
		if (vUloge[p]->radnoMjesto == 13 && vUloge[p]->uloga == 1)
			tajnica = DajImePoID(vUloge[p]->zaposlenik);
		if (vUloge[p]->radnoMjesto == 13 && vUloge[p]->uloga == 2)
			adminTajnica = DajImePoID(vUloge[p]->zaposlenik);
	}
	cout << (tajnica == " " ? "Visoka skola trenutno nema tajnicu/ka." : "Tajnik/ca visoke skole: ") << tajnica << (adminTajnica == " " ? "Visoka skola trenutno nema administrativnu tajnicu/ka." : "\nAdministrativna tajnica: " )<< adminTajnica << endl;
}

void Uloga::IspisiReferada() const
{
	vector<Uloga*> vUloge = UcitajUlogee();
	int rbr = 0;
	string voditeljica = " ", referent = " ";
	system("cls");
	cout << "**CLANOVI REFERADE**" << endl;
	for (int p = 0; p < vUloge.size(); p++)
	{
		if (vUloge[p]->radnoMjesto == 14 && vUloge[p]->uloga == 1)
			voditeljica = DajImePoID(vUloge[p]->zaposlenik);
		if (vUloge[p]->radnoMjesto == 14 && vUloge[p]->uloga == 2)
			referent = DajImePoID(vUloge[p]->zaposlenik);
	}
	cout << (voditeljica == " " ? "Visoka skola trenutno nema voditelj/icu referade" : "Voditelj/ica referade: ") << voditeljica << (referent == "" ? "Visoka skola trenutno nema strucnog referenta." : "\nStrucni referent: ") << referent << endl;
}

void Uloga::IspisiRacunovodstvo() const
{
	vector<Uloga*> vUloge = UcitajUlogee();
	int rbr = 0;
	string voditeljica = " ", referent = " ";
	system("cls");
	cout << "**CLANOVI RACUNOVODSTVA**" << endl;
	for (int p = 0; p < vUloge.size(); p++)
	{
		if (vUloge[p]->radnoMjesto == 15 && vUloge[p]->uloga == 1)
			voditeljica = DajImePoID(vUloge[p]->zaposlenik);
		if (vUloge[p]->radnoMjesto == 15 && vUloge[p]->uloga == 2)
			referent = DajImePoID(vUloge[p]->zaposlenik);
	}
	cout << (voditeljica == " " ? "Visoka skola trenutno nema voditelj/icu racunovodstva" : "Voditelj/ica racunovodstva: ") << voditeljica << (referent == "" ? "Visoka skola trenutno nema strucnog referenta." : "\nStrucni referent: ") << referent << endl;
}

void Uloga::IspisiPomocnaTehnicka() const
{
	vector<Uloga*> vUloge = UcitajUlogee(); 
	int rbr = 0;
	system("cls");
	cout << "**CLANOVI POMOCNE TEHNICKE SLUZBE**" << endl;
	for (int p = 0; p < vUloge.size(); p++)
	{
		if (vUloge[p]->radnoMjesto == 16)
		{
			rbr++;
			cout << rbr << ". "<< vUloge[p]->DajImePoID(vUloge[p]->zaposlenik) << endl;
		}
	}
}
void Uloga::IspisiUpravnoVijece() const
{
	vector<Uloga*> vUloge = UcitajUlogee(); 
	int rbr = 0; 
	system("cls");
	cout << "**CLANOVI UPRAVNOG VIJECA**" << endl;
	for (int p = 0; p < vUloge.size(); p++)
	{
		if (vUloge[p]->radnoMjesto == 1)
		{
			rbr++;
			cout << rbr << ". " << DajImePoID(vUloge[p]->zaposlenik) << endl;
		}

	}
}

void Uloga::IspisiStrucnoVijece() const
{
	vector<Uloga*> vUloge = UcitajUlogee();
	string ime = " ";
	int rbr = 0;
	system("cls");
	cout << "**CLANOVI STRUCNOG VIJECA**" << endl;
	for (int p = 0; p < vUloge.size(); p++)
	{
		if (vUloge[p]->radnoMjesto == 2)
		{
			rbr++;
			cout << rbr << ". " << DajImePoID(vUloge[p]->zaposlenik) << endl;
		}
	}

}

void Uloga::IspisiICT() const
{
	vector<Uloga*> vUloge = UcitajUlogee();
	int rbr = 0; 
	int priv = 0;
	system("cls");
	cout << "**ODJEL ZA INFORMACIJSKO-KOMUNIKACIJSKE TEHNOLOGIJE VISOKE SKOLE ZA MENADZMENT U TURIZMU I INFORMATICI U VIROVITICI**" << endl;
	for (int p = 0; p < vUloge.size(); p++)
	{
		if (vUloge[p]->radnoMjesto == 6)
		{
			rbr++;
			cout << rbr << ". " << DajImePoID(vUloge[p]->zaposlenik) << endl;
			if (vUloge[p]->radnoMjesto == 6 && vUloge[p]->uloga == 1)
				priv = vUloge[p]->zaposlenik;				
		}	
	}
	cout << "Voditelj/ica odjela: " << DajImePoID(priv) << endl;
}
void Uloga::IspisiMenadazment() const
{
	vector<Uloga*> vUloge = UcitajUlogee();
	int rbr = 0;
	int priv = 0;
	system("cls");
	cout << "**ODJEL ZA EKONOMIJU VISOKE SKOLE ZA MENADZMENT U TURIZMU I INFORMATICI U VIROVITICI**" << endl;
	for (int p = 0; p < vUloge.size(); p++)
	{
		if (vUloge[p]->radnoMjesto == 7)
		{
			rbr++;
			cout << rbr << ". " << DajImePoID(vUloge[p]->zaposlenik) << endl;
			if (vUloge[p]->radnoMjesto == 7 && vUloge[p]->uloga == 1)
				priv = vUloge[p]->zaposlenik;
		}
	}
	cout << "Voditelj/ica odjela: " << DajImePoID(priv) << endl;
}

void Uloga::IspisiTurizam() const
{
	vector<Uloga*> vUloge = UcitajUlogee();
	int rbr = 0;
	int priv = 0;
	system("cls");
	cout << "**ODJEL ZA TURIZAM VISOKE SKOLE ZA MENADZMENT U TURIZMU I INFORMATICI U VIROVITICI**" << endl;
	for (int p = 0; p < vUloge.size(); p++)
	{
		if (vUloge[p]->radnoMjesto == 8)
		{
			rbr++;
			cout << rbr << ". " << DajImePoID(vUloge[p]->zaposlenik) << endl;
			if (vUloge[p]->radnoMjesto == 8 && vUloge[p]->uloga == 1)
				priv = vUloge[p]->zaposlenik;
		}
	}
	cout << "Voditelj/ica odjela: " << DajImePoID(priv) << endl;
}


vector<Uloga*> UcitajUlogee()
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
vector<Zaposlenik*> UcitajZaposlenikee()
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
vector<Centar*> UcitajCentre()
{
	vector<Centar*> vCentri;
	XMLDocument oXmlDocument;
	oXmlDocument.LoadFile("ustrojstvo.xml");
	XMLElement *pRoot = oXmlDocument.FirstChildElement("data");
	XMLElement *pChild;
	XMLElement *pChild2;
	XMLElement *pChild3;
	for (pChild = pRoot->FirstChildElement("Ustrojstvo"); pChild != NULL; pChild =
		pChild->NextSiblingElement())
	{
		for (pChild2 = pChild->FirstChildElement("Centri"); pChild2 != NULL; pChild2 = pChild2->NextSiblingElement())
		{
			for (pChild3 = pChild2->FirstChildElement("Centar"); pChild3 != NULL; pChild3 = pChild3->NextSiblingElement())
			{
				int id = stoi(pChild3->Attribute("id"));
				string n = pChild3->Attribute("name");
				vCentri.push_back(new Centar(id, n));
			}
		}
	}
	return vCentri;
}
vector<ZajednickeSluzbe*> UcitajSluzbe()
{
	vector<ZajednickeSluzbe*> vSluzbe;
	XMLDocument oXmlDocument;
	oXmlDocument.LoadFile("ustrojstvo.xml");
	XMLElement *pRoot = oXmlDocument.FirstChildElement("data");
	XMLElement *pChild;
	XMLElement *pChild2;
	XMLElement *pChild3;
	for (pChild = pRoot->FirstChildElement("Ustrojstvo"); pChild != NULL; pChild =
		pChild->NextSiblingElement())
	{
		for (pChild2 = pChild->FirstChildElement("ZajednickeSluzbe"); pChild2 != NULL; pChild2 = pChild2->NextSiblingElement())
		{
			for (pChild3 = pChild2->FirstChildElement("Sluzba"); pChild3 != NULL; pChild3 = pChild3->NextSiblingElement())
			{
				int id = stoi(pChild3->Attribute("id"));
				string n = pChild3->Attribute("name");
				vSluzbe.push_back(new ZajednickeSluzbe(id, n));
			}
		}
	}
	return vSluzbe;
}
vector<Odjel*> UcitajOdjele()
{
	vector<Odjel*> vOdjeli;
	XMLDocument oXmlDocument;
	oXmlDocument.LoadFile("ustrojstvo.xml");
	XMLElement *pRoot = oXmlDocument.FirstChildElement("data");
	XMLElement *pChild;
	XMLElement *pChild2;
	XMLElement *pChild3;
	for (pChild = pRoot->FirstChildElement("Ustrojstvo"); pChild != NULL; pChild =
		pChild->NextSiblingElement())
	{
		for (pChild2 = pChild->FirstChildElement("Odjeli"); pChild2 != NULL; pChild2 = pChild2->NextSiblingElement())
		{
			for (pChild3 = pChild2->FirstChildElement("Odjel"); pChild3 != NULL; pChild3 = pChild3->NextSiblingElement())
			{
				int id = stoi(pChild3->Attribute("id"));
				string n = pChild3->Attribute("name");
				vOdjeli.push_back(new Odjel(id, n));
			}
		}
	}
	return vOdjeli;
}
vector<Dekanat*> UcitajDekanat()
{
	vector<Dekanat*> vDekanat;
	XMLDocument oXmlDocument;
	oXmlDocument.LoadFile("ustrojstvo.xml");
	XMLElement *pRoot = oXmlDocument.FirstChildElement("data");
	XMLElement *pChild;
	XMLElement *pChild2;
	XMLElement *pChild3;
	for (pChild = pRoot->FirstChildElement("Ustrojstvo"); pChild != NULL; pChild =
		pChild->NextSiblingElement())
	{
		for (pChild2 = pChild->FirstChildElement("Dekanat"); pChild2 != NULL; pChild2 = pChild2->NextSiblingElement())
		{
			for (pChild3 = pChild2->FirstChildElement("Podjedinica"); pChild3 != NULL; pChild3 = pChild3->NextSiblingElement())
			{
				int id = stoi(pChild3->Attribute("id"));
				string n = pChild3->Attribute("name");
				vDekanat.push_back(new Dekanat(id, n));
			}
		}
	}
	return vDekanat;
}

