#define _USE_MATH_DEFINES
#include "Windows.h"
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <chrono>
#include <thread>
#include <list>

using namespace std;
class Sym {
public:
	vector<vector<int>> macierzOdleglosci;
	double dlugoscTrasy;
	vector<int> Trasa;
	vector<int> Trasa2;
	int poprzedniElement;
	vector<vector<int>>rodzic;
	vector <double> dlugoscRodzica;
	double dlugoscObecnejTrasy;
	vector<int> obecnaTrasa;
	int rozmiarTrasy;
	int liczbaRodziców;
	double wspKrzyzowania;
	double wspMutacji;
	Sym() {
		srand(time(NULL));
	}
	void wczytajMacierzOdleglosci(string nazwa)
	{
		ifstream plik;
		plik.open(nazwa);

		if (plik.is_open())
		{
			string tmp, typ;
			int liczbaMiast;
			while (tmp != "DIMENSION:")
				plik >> tmp;
			if (tmp == "DIMENSION") plik >> tmp;
			plik >> liczbaMiast;

			cout << liczbaMiast << endl;
			double odleglosc;
			while (tmp != "EDGE_WEIGHT_SECTION")
				plik >> tmp;

			for (int i = 0; i < liczbaMiast; i++)
			{
				vector<int> wiersz;
				macierzOdleglosci.push_back(wiersz);
				for (int j = 0; j < liczbaMiast; j++)
				{
					plik >> odleglosc;
					macierzOdleglosci[i].push_back(odleglosc);
				}
			}

		}
	}
	void stworz()
	{
		int wierzcho³ek;
		bool * visited;
		visited = new bool[macierzOdleglosci.size()];
		for (int i = 0; i < (macierzOdleglosci.size()); i++)
		{
			visited[i] = false;
		}
		Trasa.push_back(0);
		visited[0] = true;
		for (int i = 1; i < (macierzOdleglosci.size()); i++) {
			do
			{
				wierzcho³ek = (rand() % macierzOdleglosci.size() - 1) + 1;
			} while (visited[wierzcho³ek] == true);
			Trasa.push_back(wierzcho³ek);
			visited[wierzcho³ek] = true;

		}
		Trasa.push_back(0);
		/*for (int j = 0; j < Trasa.size() - 1; j++) {
			for (int i = 0; i < Trasa.size() - 1; i++)
				if (Trasa[i] > Trasa[i + 1]) {
					swap(Trasa[i], Trasa[i + 1]);
				}
		}*/
	}
	void koszt()
	{
		dlugoscTrasy = 0;
		poprzedniElement = 0;
		for (int i = 1; i < Trasa.size(); i++)
		{
			dlugoscTrasy += macierzOdleglosci[poprzedniElement][Trasa[i]];
			poprzedniElement = Trasa[i];
		}
		rozmiarTrasy = Trasa.size();
		//cout << "koszt w funkcji " << dlugoscObecnejTrasy << endl;
	}
	void tworzRodzicow() {
		cout << "Podaj liczbe rodzicow" << endl;
		cin >> liczbaRodziców;
		for (int i = 0; i < liczbaRodziców; i++) {
			stworz();
			koszt();
			rodzic.push_back(Trasa);
			dlugoscRodzica.push_back(dlugoscTrasy);
			Trasa.clear();
			dlugoscTrasy = 0;
		}
		sortuj();
	}
	void sortuj()
	{
		for (int j = 0; j < dlugoscRodzica.size() - 1; j++) {
			for (int i = 0; i < dlugoscRodzica.size() - 1; i++)
				if (dlugoscRodzica[i] > dlugoscRodzica[i + 1]) {
					swap(dlugoscRodzica[i], dlugoscRodzica[i + 1]);
					swap(rodzic[i], rodzic[i + 1]);
				}
		}
	}
	void losuj()
	{
		int temp;
		int a;
		int b;

		a = (rand() % (rozmiarTrasy - 3)) + 1;
		b = (rand() % (rozmiarTrasy - 3)) + 1;
		//cout << "a : " << a << "  b ; " << b << endl;
		if (a != b)
		{
			//cout << "a : " << Trasa[a]  << "  b ; " << Trasa[b] << endl;
			temp = Trasa[a];
			Trasa[a] = Trasa[b];
			Trasa[b] = temp;
		}
	}

	void mutacja1()
	{

		int ileRazy = 1;//liczbaRodziców * wspMutacji;
		bool powtorka = false;
		//cout << "ile :  " << ileRazy << endl;
		for (int i = 0; i < ileRazy; i++) {
			int a = (rand() % (dlugoscRodzica.size()));
			Trasa = rodzic[a];
			dlugoscTrasy = dlugoscRodzica[a];
			losuj();
			koszt();
			for (int i = 0; i < dlugoscRodzica.size(); i++)
				if (dlugoscRodzica[i] == dlugoscTrasy)
					powtorka = true;

			if (powtorka != true) {
				rodzic.push_back(Trasa);
				dlugoscRodzica.push_back(dlugoscTrasy);
			}
			//cout << "koszt po  mutacji: " << dlugoscTrasy << endl;
			Trasa.clear();
		}
		
	}
	void symulowaneM1(std::chrono::seconds s)
	{

		cout << "Podaj wspolczynik Krzyzowania :" << endl;
		cin >> wspKrzyzowania;
		cout << "Podaj wspolczynik Mutacji :" << endl;
		cin >> wspMutacji;
		int ileMutacji = liczbaRodziców * wspMutacji;
		int ileKrzyzowan = liczbaRodziców * wspKrzyzowania; auto start = std::chrono::high_resolution_clock::now();
		auto end = start + s;
		do {
			for (int i = 0; i < ileKrzyzowan; i++) {
				krzyzowy1();
				if (ileMutacji > 0) {
					mutacja1();
					ileMutacji--;

				}
			}
			sortuj();
			rodzic.resize(liczbaRodziców);
			dlugoscRodzica.resize(liczbaRodziców);

		} while (std::chrono::high_resolution_clock::now() < end);

	}
	void mutacja2() {

		int temp;
		bool powtorka = false;
		int ileRazy = 1; //liczbaRodziców * wspMutacji;
		//cout << "ile :  " << ileRazy << endl;
		for (int i = 0; i < ileRazy; i++) {
			int a = (rand() % (dlugoscRodzica.size()));
			Trasa = rodzic[a];
			dlugoscTrasy = dlugoscRodzica[a];
			int b = (rand() % macierzOdleglosci.size());
			temp = Trasa[b];
			for (int i = b; i < (Trasa.size() - 1); i++) {
				Trasa[i] = Trasa[i + 1];
			}
			Trasa[Trasa.size() - 2] = temp;
			koszt();
			for (int i = 0; i < dlugoscRodzica.size(); i++)
				if (dlugoscRodzica[i] == dlugoscTrasy)
					powtorka = true;

			if (powtorka != true) {
				rodzic.push_back(Trasa);
				dlugoscRodzica.push_back(dlugoscTrasy);
			}
			Trasa.clear();
		}

	}
	void symulowaneM2(std::chrono::seconds s)
	{

		cout << "Podaj wspolczynik Krzyzowania :" << endl;
		cin >> wspKrzyzowania;
		cout << "Podaj wspolczynik Mutacji :" << endl;
		cin >> wspMutacji;
		int ileMutacji = liczbaRodziców * wspMutacji;
		int ileKrzyzowan = liczbaRodziców * wspKrzyzowania; auto start = std::chrono::high_resolution_clock::now();
		auto end = start + s;
		do {
			for (int i = 0; i < ileKrzyzowan; i++) {
				krzyzowy1();
				if (ileMutacji > 0) {
					mutacja2();
					ileMutacji--;

				}
			}
			sortuj();
			rodzic.resize(liczbaRodziców);
			dlugoscRodzica.resize(liczbaRodziców);

		} while (std::chrono::high_resolution_clock::now() < end);

	}
	void krzyzowy1()
	{
		bool powtorka = false;
		bool * visited;
		visited = new bool[macierzOdleglosci.size()];
		int ileRazy = 1;// liczbaRodziców * wspKrzyzowania;
		int a;
		int d;
		int b;
		int c;
		int test = 0;
		//cout << "ile :  " << ileRazy << endl;
		for (int i = 0; i < ileRazy; i++) {
			for (int l = 0; l < (macierzOdleglosci.size()); l++)
			{
				visited[l] = false;
				obecnaTrasa.push_back(0);
			}
			do {
				a = (rand() % (dlugoscRodzica.size()));
				d = (rand() % (dlugoscRodzica.size()));
			} while (a == d);
			test = 0;
			Trasa = rodzic[a];
			do {
				b = (rand() % (Trasa.size() - 1)) + 1;
				c = (rand() % (Trasa.size() - 1)) + 1;
			} while (b == c);
			if (b > c)
				swap(b, c);

			for (int j = b; j < c; j++)
			{
				obecnaTrasa[j] = Trasa[j];
				visited[Trasa[j]] = true;

			}

			Trasa.clear();
			Trasa = rodzic[d];
			int numer = 1;
			for (int k = 1; k < Trasa.size(); k++)
			{
				if (visited[Trasa[k]] != true) {
					obecnaTrasa[numer] = Trasa[k];
					//cout << "  k:  :" << k << endl
					numer++;
					if (numer == b)
						numer = c;


				}

			}
			for (int l = 1; l < obecnaTrasa.size(); l++)
			{
				if (obecnaTrasa[l] == 0)
					test = 9;
			}
			obecnaTrasa.push_back(0);
			Trasa.clear();
			Trasa = obecnaTrasa;
			//wysObecna();
			obecnaTrasa.clear();
			koszt();
			for (int i = 0; i < dlugoscRodzica.size(); i++)
				if (dlugoscRodzica[i] == dlugoscTrasy)
					powtorka = true;

			if (powtorka != true && test != 9) {
				rodzic.push_back(Trasa);
				dlugoscRodzica.push_back(dlugoscTrasy);
			}
			Trasa.clear();
		}
		
	}
	void symulowaneK1(std::chrono::seconds s)
	{
		cout << "Podaj wspolczynik Krzyzowania :" << endl;
		cin >> wspKrzyzowania;
		cout << "Podaj wspolczynik Mutacji :" << endl;
		cin >> wspMutacji;
		int ileMutacji = liczbaRodziców * wspMutacji;
		int ileKrzyzowan = liczbaRodziców * wspKrzyzowania; auto start = std::chrono::high_resolution_clock::now();
		auto end = start + s;
		do {
			for (int i = 0; i < ileKrzyzowan; i++) {
				krzyzowy2();
				if (ileMutacji > 0) {
					mutacja1();
					ileMutacji--;

				}
			}
			sortuj();
			rodzic.resize(liczbaRodziców);
			dlugoscRodzica.resize(liczbaRodziców);


		} while (std::chrono::high_resolution_clock::now() < end);

	}
	void krzyzowy2()
	{
		bool powtorka = false;
		bool * visited;
		visited = new bool[macierzOdleglosci.size()];
		bool * szuka;
		szuka = new bool[macierzOdleglosci.size()];
		int ileRazy = 1;// liczbaRodziców * wspKrzyzowania;
		int a;
		int d;
		int b;
		int c;
		int liczba;
		int szukana;
		int test = 0;
		//cout << "ile :  " << ileRazy << endl;
		for (int i = 0; i < ileRazy; i++) {
			for (int l = 0; l < (macierzOdleglosci.size()); l++)
			{
				visited[l] = false;
				szuka[l] = false;
				obecnaTrasa.push_back(0);
			}
			do {
				a = (rand() % (dlugoscRodzica.size()));
				d = (rand() % (dlugoscRodzica.size()));
			} while (a == d);

			Trasa = rodzic[a];
			test = 0;
			Trasa2 = rodzic[d];

			do {
				b = (rand() % (Trasa.size() - 1)) + 1;
				c = (rand() % (Trasa.size() - 1)) + 1;
			} while (b == c);
			if (b > c)
				swap(b, c);
			for (int j = b; j < c; j++)
			{
				obecnaTrasa[j] = Trasa[j];
				visited[Trasa[j]] = true;
				liczba = Trasa2[j];
				visited[liczba] = true;
				szukana = Trasa[j];
				;
				if (szukana != liczba && szukana != 0 && liczba != 0)
					for (int k = 0; k < Trasa2.size(); k++) {

						if (Trasa2[k] == szukana && szukana != liczba && szukana != 0 && liczba != 0 && szuka[szukana] != true)
						{
							szuka[szukana] = true;
							/*cout << "szukana: " << szukana << endl;
							cout << "liczba: " << liczba << endl;
							cout << "gdzie jest: " << k << endl;
							cout << "j: " << j << endl;
							cout << "b: " << b << endl;
							cout << "c: " << c << endl;*/
							if (k<b || k>c)
								obecnaTrasa[k] = liczba;
							else
							{
								szukana = Trasa[k];
								k = 0;
							}
						}
					}

			}


			int numer = 1;
			for (int l = 1; l < Trasa2.size(); l++)
			{
				if (visited[Trasa2[l]] != true) {
					if (obecnaTrasa[numer] == 0) {
						obecnaTrasa[numer] = Trasa2[l];
						//cout << "  k:  :" << l << endl;
						numer++;
						if (numer == b)
							numer = c;
					}
					else {
						numer++;
						l--;
					}
				}

			}
			for (int l = 1; l < obecnaTrasa.size(); l++)
			{
				if (obecnaTrasa[l] == 0)
					test = 9;
			}
			obecnaTrasa.push_back(0);
			Trasa.clear();
			Trasa = obecnaTrasa;
			obecnaTrasa.clear();
			Trasa2.clear();
			koszt();
			//wysObecna();
			for (int i = 0; i < dlugoscRodzica.size(); i++)
				if (dlugoscRodzica[i] == dlugoscTrasy)
					powtorka = true;

			if (powtorka != true && test != 9) {
				rodzic.push_back(Trasa);
				dlugoscRodzica.push_back(dlugoscTrasy);
			}
			Trasa.clear();

		}


	}
	void symulowaneK2(std::chrono::seconds s)
	{
		cout << "Podaj wspolczynik Krzyzowania :" << endl;
		cin >> wspKrzyzowania;
		cout << "Podaj wspolczynik Mutacji :" << endl;
		cin >> wspMutacji;
		int ileMutacji = liczbaRodziców * wspMutacji;
		int ileKrzyzowan = liczbaRodziców * wspKrzyzowania; auto start = std::chrono::high_resolution_clock::now();
		auto end = start + s;
		do {
			for (int i = 0; i < ileKrzyzowan; i++) {
				krzyzowy2();
				if (ileMutacji > 0) {
					mutacja2();
					ileMutacji--;

				}
			}
			sortuj();
			rodzic.resize(liczbaRodziców);
			dlugoscRodzica.resize(liczbaRodziców);

		} while (std::chrono::high_resolution_clock::now() < end);

	}
	void wysRodzicow() {
		cout << endl;
		cout << "Trasa : " << endl;
		for (int i = 0; i < 1; i++) {
			for (int j = 0; j < rozmiarTrasy; j++)
			{
				cout << rodzic[i][j] << ",";
			}
			cout << endl << "Jej dlugosc: ";

			cout << dlugoscRodzica[i] << endl;
		}

		cout << endl;
	}
	void wysObecna()
	{
		cout << endl;
		cout << "Obecna trasa : " << endl;
		for (int i = 0; i < Trasa.size(); i++)
			cout << Trasa[i] << ", ";
		cout << endl << "Jej dlugosc: " << dlugoscTrasy << endl;
		cout << "rozmiar " << Trasa.size() << endl;
		cout << endl;
	}
};
int main()
{
	Sym s;
	string nazwa;
	int czas;
	cout << "Podaj sciezke dostepu do pliku z instancja problemu: ";
	cin >> nazwa;
	s.wczytajMacierzOdleglosci(nazwa);
	s.tworzRodzicow();
	cout << "Podaj czas trwania algorytmu: ";
	cin >> czas;
	string wybor;
	do {
		cout << " Mutacja (zamiana) i Krzyzowanie (OX) - 1 \n Mutacja (na koniec) i Krzyzowanie (OX)- 2 \n Mutacja (zamiana) i  Krzyzowanie (PMX)- 3  \n Mutacja (na koniec) i  Krzyzowanie (PMX)- 4 \n Koniec- z" << endl;
		cin >> wybor;
		if (wybor == "1")
		{
			auto start = std::chrono::high_resolution_clock::now();

			s.symulowaneM1(std::chrono::seconds(czas));

			auto elapsed = std::chrono::high_resolution_clock::now() - start;
			cout << "czakano "
				<< std::chrono::duration_cast <std::chrono::seconds>(elapsed).count()
				<< " sekund.\n";
			cout << endl;
			s.wysRodzicow();
		}
		if (wybor == "2")
		{
			auto start = std::chrono::high_resolution_clock::now();

			s.symulowaneM2(std::chrono::seconds(czas));

			auto elapsed = std::chrono::high_resolution_clock::now() - start;
			cout << "czakano "
				<< std::chrono::duration_cast <std::chrono::seconds>(elapsed).count()
				<< " sekund.\n";
			cout << endl;
			s.wysRodzicow();
		}
		if (wybor == "3")
		{
			auto start = std::chrono::high_resolution_clock::now();

			s.symulowaneK1(std::chrono::seconds(czas));

			auto elapsed = std::chrono::high_resolution_clock::now() - start;
			cout << "czakano "
				<< std::chrono::duration_cast <std::chrono::seconds>(elapsed).count()
				<< " sekund.\n";
			cout << endl;
			s.wysRodzicow();
		}
		if (wybor == "4")
		{



			auto start = std::chrono::high_resolution_clock::now();

			s.symulowaneK2(std::chrono::seconds(czas));

			auto elapsed = std::chrono::high_resolution_clock::now() - start;
			cout << "czakano "
				<< std::chrono::duration_cast <std::chrono::seconds>(elapsed).count()
				<< " sekund.\n";
			cout << endl;
			s.wysRodzicow();
		}
	} while (wybor != "z");

	system("pause");
	return 0;
}