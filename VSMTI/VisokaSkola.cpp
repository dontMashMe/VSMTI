#include "pch.h"
#include "VisokaSkola.h"
#include "Uloga.h"
#include <iostream>
using namespace std;



VisokaSkola::VisokaSkola()
{
}


VisokaSkola::~VisokaSkola()
{
}



void VisokaSkola::GlavniIzbornik() const
{
	Zaposlenik *z1 = new Zaposlenik{ 1,"s","s" };
	Uloga *u1 = new Uloga{ 1,2,3 };
	int n;
	cout << "\t\t\t\tVisoka skola za menadzment u turizmu i informatici." << endl;
	cout << "Ul. Matije Gupca 78.\t\t\t\t\t\t\t\t\t\t       Tel: 033 721 099 \n33000, Virovitica" << endl;
	cout << "=======================================================================================================================" << endl;
	cout << "Svi podaci o ustrojstvu su preuzeti sa stranice Visoke skole." << endl;
	cout << "1...Ispisi sve zaposlenike." << endl;
	cout << "2...Pogledaj pojedinog zaposlenika." << endl;
	cout << "3...Pregled ustrojstva." << endl;
	cout << "4...Dodaj zaposlenika." << endl;
	cout << "5...Obrisi zaposlenika. " << endl;
	cout << "6...Administracija korisnika." << endl;
	cout << "Vas odabir: ";
	cin >> n;
	switch (n)
	{
	case 1:
		system("cls");
		z1->IspisiZaposlenike();
		Kontrole();
		break;
	case 2:
		system("cls");
		z1->PogledajPojedinogZaposlenika(); 
		Kontrole(); 
		break;
	case 3:
		system("cls");
		u1->PregledUstrojstva();
		KontroleU();
		break;
	case 4:
		system("cls");
		z1->DodajZaposlenika();
		Kontrole();
		break;
	case 5:
		system("cls");
		z1->IspisiZaposlenike();
		z1->ObrisiZaposlenika();
		Kontrole();
		break;
	case 6:
		system("cls");
		u1->Administracija();
		Kontrole();
		break;
	default:
		system("cls");
		GlavniIzbornik();
	}
	
}

int VisokaSkola::Kontrole() const
{
	cout << "\nPritisnite [Q] za povratak u glavni izbornik." << endl;
	cout << "Pritisnite [X] za izlaz iz programa." << endl;
	char odabir;
	cout << "odabir: ";
	cin >> odabir;
	while (odabir != 'X' && odabir != 'Q')
	{
		cout << "Krivi odabir." << endl;
		cout << "odabir: ";
		cin >> odabir;
	}
	switch (odabir)
	{
	case 'Q':
		system("cls");
		GlavniIzbornik();
		break;
	case 'X':
		return 0;
		break;
	}
}
int VisokaSkola::KontroleU() const
{
	Uloga *u1 = new Uloga{ 1,2,3 };
	cout << "\nPritisnite [Q] za povratak u glavni izbornik." << endl;
	cout << "Pritisnite [X] za izlaz iz programa." << endl;
	cout << "Pritisnite [Y] za povratak u prethodni izbornik." << endl;
	char odabir;
	cout << "odabir: ";
	cin >> odabir;
	while (odabir != 'X' && odabir != 'Q' && odabir != 'Y')
	{
		cout << "Krivi odabir." << endl;
		cout << "odabir: ";
		cin >> odabir;
	}
	switch (odabir)
	{
	case 'Q':
		system("cls");
		GlavniIzbornik();
		break;
	case 'Y':
		system("cls");
		u1->PregledUstrojstva();
		KontroleU();
		break;
	case 'X':
		return 0;
		break;
	}
}