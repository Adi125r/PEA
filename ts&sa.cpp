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
class Sym{
public:
vector<vector<int>> macierzOdleglosci;
float TemperaturaPoczatkowa;
float TemperaturaChlodzenia;
float TemperaturaMinimalna;
float TemperaturaObecna;
int liczbaIteracji;
int bylo = 0;
double dlugoscNajlepszejTrasy;
vector<int> najlepszaTrasa;
double dlugoscKTrasy= INT_MAX;
vector<int> KTrasa;
double dlugoscTrasy;
vector<int> Trasa;
double dlugoscObecnejTrasy;
vector<int> obecnaTrasa;
double dlugoscnajwiekszejTrasy;
vector<int> najwiekszaTrasa;
int poprzedniElement = 0;
pair<int, int> szukana;
list <pair<int, int>> Tabu;
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
void zach³any()
{
int min = INT_MAX;
	int wierzcho³ek;
	bool * visited;
	visited = new bool[macierzOdleglosci.size()];
	for (int i = 0; i < (macierzOdleglosci.size()); i++)
	{
		visited[i] = false;
	}
	obecnaTrasa.push_back(0);
	dlugoscObecnejTrasy = 0;
	for (int i = 1; i < macierzOdleglosci.size(); i++)
	{
		
			for (int k = 1; k < macierzOdleglosci.size(); k++)
			{
				if (macierzOdleglosci[poprzedniElement][k] < min && poprzedniElement != k && visited[k] != true)
				{
					min = macierzOdleglosci[poprzedniElement][k];
					wierzcho³ek = k;
				}
			}
			visited[wierzcho³ek] = true;
			dlugoscObecnejTrasy += min;
			obecnaTrasa.push_back(wierzcho³ek);
			min = INT_MAX;
			poprzedniElement = wierzcho³ek;
		
	}
	dlugoscObecnejTrasy += macierzOdleglosci[poprzedniElement][0];
	obecnaTrasa.push_back(0);
	dlugoscNajlepszejTrasy = dlugoscObecnejTrasy;
	najlepszaTrasa = obecnaTrasa;
	Trasa = obecnaTrasa;
	dlugoscTrasy = dlugoscObecnejTrasy;
	cout << "dlugosc zachlanym :" << dlugoscObecnejTrasy << endl;
	cout << "dlugosc tr :" << obecnaTrasa.size() << endl;

}
void najwieksza()
{
	int min = 0;
	int wierzcho³ek;
	bool * visited;
	visited = new bool[macierzOdleglosci.size()];
	for (int i = 0; i < (macierzOdleglosci.size()); i++)
	{
		visited[i] = false;
	}
	najwiekszaTrasa.push_back(0);
	dlugoscnajwiekszejTrasy = 0;
	for (int i = 0; i < macierzOdleglosci.size(); i++)
	{
		if (i != poprzedniElement)
		{
			for (int k = 1; k < macierzOdleglosci.size(); k++)
			{
				if (macierzOdleglosci[poprzedniElement][k] > min && poprzedniElement != k && visited[k] != true)
				{
					min = macierzOdleglosci[poprzedniElement][k];
					wierzcho³ek = k;
				}
			}
			visited[wierzcho³ek] = true;
			dlugoscnajwiekszejTrasy += min;
			najwiekszaTrasa.push_back(wierzcho³ek);
			min = 0;
			poprzedniElement = wierzcho³ek;
		}
	}
	dlugoscnajwiekszejTrasy += macierzOdleglosci[poprzedniElement][0];
	najwiekszaTrasa.push_back(0);
	

}

void generowanieDanych() 
{
	double lo = log(0.8);
	TemperaturaPoczatkowa = -(dlugoscnajwiekszejTrasy - dlugoscObecnejTrasy) / 2;
	TemperaturaPoczatkowa = TemperaturaPoczatkowa / lo;
	cout << "Temperatura chlodzenia: ";
	cin >> TemperaturaChlodzenia;

	TemperaturaMinimalna = 0.001;

	liczbaIteracji= macierzOdleglosci.size();
	
	TemperaturaObecna = TemperaturaPoczatkowa;

}
void generowanie()
{
	double lo = log(0.8);
	TemperaturaPoczatkowa = -(dlugoscnajwiekszejTrasy - dlugoscObecnejTrasy) / 2;
	TemperaturaPoczatkowa = TemperaturaPoczatkowa / lo;
TemperaturaChlodzenia = 0.9;
TemperaturaMinimalna = 0.001;
liczbaIteracji = macierzOdleglosci.size();
TemperaturaObecna = TemperaturaPoczatkowa;
cout<<"Pocztkowa temperatura"<<TemperaturaObecna<<endl;

}
void losuj()
{
	int temp;
	int a;
	int b;
	int liczba = obecnaTrasa.size();
	a = (rand() % (liczba - 3)) + 1;
	b = (rand() % (liczba - 3)) + 1;
	//cout << "a : " << a << "  b ; " << b << endl;
	if (a != b)
	{
		temp = obecnaTrasa[a];
		obecnaTrasa[a] = obecnaTrasa[b];
		obecnaTrasa[b] = temp;
	}
}
void zamiana()
{
	int temp;
	int a;
	int b;
	int liczba = obecnaTrasa.size();
	int znalazl = 0;
while(znalazl != 2)
{
	a = (rand() % (liczba -2 )) + 1 ;
	b = (rand() % (liczba -2) ) + 1;

	//cout << "a :: " << a << "b :: " << b << endl;
	szukana.first = a;
	szukana.second = b;
	if (find(Tabu.begin(), Tabu.end(), szukana) != Tabu.end() )
		znalazl = 1;
	else
	{
		if(a!=b)
		znalazl = 2;
	}
	if (aspiracja(a,b) < 0)
		znalazl = 2;
}
		//cout << "a :: b :::" << a << ":" << b << endl;
	if (a != b && znalazl != true)
	{
		
		temp = obecnaTrasa[a];
		obecnaTrasa[a] = obecnaTrasa[b];
		obecnaTrasa[b] = temp;
	}
	Tabu.push_front(pair <int, int>(a,b));
	
	Tabu.resize(10);
}
int aspiracja (int x, int y)
{
	int temp;
	int roznica;
	Trasa.clear();
	Trasa = obecnaTrasa;
	dlugoscTrasy = 0;
	temp = Trasa[x];
	Trasa[x] = Trasa[y];
	Trasa[y] = temp;
	poprzedniElement = 0;
	for (int i = 1; i < Trasa.size(); i++)
	{
		dlugoscTrasy += macierzOdleglosci[poprzedniElement][Trasa[i]];
		poprzedniElement = Trasa[i];
	}
	roznica = dlugoscTrasy - dlugoscNajlepszejTrasy;
	return roznica;
}
void dywer() 
{
	int min = INT_MAX;
	int wierzcho³ek;
	bool * visited;
	bool jest = false;
	visited = new bool[macierzOdleglosci.size()];
	for (int i = 0; i < (macierzOdleglosci.size()); i++)
	{
		visited[i] = false;
	}
	obecnaTrasa.clear();
	obecnaTrasa.push_back(0);
	dlugoscObecnejTrasy = 0;
	for (int i = 1; i < macierzOdleglosci.size() ; i++)
	{
		
			for (int k = 1; k < macierzOdleglosci.size(); k++)
			{
				for (int j = 0; j < macierzOdleglosci.size(); j++)
				{
					if (najlepszaTrasa[j] == poprzedniElement && najlepszaTrasa[j + 1] == k)
					{
						jest = true;
						
					}
				}		
				if (macierzOdleglosci[poprzedniElement][k] < min && poprzedniElement != k && visited[k] != true && jest != true)
				{
					min = macierzOdleglosci[poprzedniElement][k];
					wierzcho³ek = k;
				}
				
				jest = false;

				
					

			}
			
			visited[wierzcho³ek] = true;
			dlugoscObecnejTrasy += min;
			obecnaTrasa.push_back(wierzcho³ek);
			min = INT_MAX;
			poprzedniElement = wierzcho³ek;
		
	}
	dlugoscObecnejTrasy += macierzOdleglosci[poprzedniElement][0];
	obecnaTrasa.push_back(0);
	dlugoscNajlepszejTrasy = dlugoscObecnejTrasy;
	najlepszaTrasa = obecnaTrasa;
	//cout<<"d³ugoœæ losowej drogi "<<dlugoscObecnejTrasy<<endl;
	delete visited;
	bylo = 0;
	poprzedniElement = 0;
	//	cout << "dl po dy" << obecnaTrasa.size() << endl;
}
void koszt() 
{
	dlugoscObecnejTrasy = 0;
	poprzedniElement = 0;
	for (int i = 1; i < obecnaTrasa.size(); i++) 
	{
		dlugoscObecnejTrasy += macierzOdleglosci[poprzedniElement][obecnaTrasa[i]];
			poprzedniElement = obecnaTrasa[i];
	}
	//cout << "koszt w funkcji " << dlugoscObecnejTrasy << endl;
}
long long int read_QPC() //funkcja do pomiaru czasu
{
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return((long long int)count.QuadPart);
}
void SA() 
{
	
	int roznica;
	for (int i = 0; i < liczbaIteracji; i++)
	{
		//cout << "ob1  " << dlugoscObecnejTrasy << endl;
		losuj();
 		koszt();
		
		if (dlugoscKTrasy> dlugoscObecnejTrasy)
		{
			dlugoscKTrasy = dlugoscObecnejTrasy;
			KTrasa = obecnaTrasa;
			
		
		}
		roznica = dlugoscObecnejTrasy - dlugoscNajlepszejTrasy;
		
		if (roznica < 0) 
		{
		
			dlugoscNajlepszejTrasy = dlugoscObecnejTrasy;
			najlepszaTrasa = obecnaTrasa;
		}
		else
		{
			int losowa = rand() % (100) ;
			float wylosuj = 0.0;
			if (losowa > 0)
			wylosuj = losowa / 100;
		else
			wylosuj = 0.97;

		double potega = -((roznica)/(TemperaturaObecna));
		double prawdopodobienstwo = pow(M_E, potega);
			//cout << "wy " << wylosuj << "pra : " << prawdopodobienstwo << endl;
		if(wylosuj<prawdopodobienstwo){
				dlugoscNajlepszejTrasy = dlugoscObecnejTrasy;
				najlepszaTrasa = obecnaTrasa;
				//cout << "jest" << dlugoscNajlepszejTrasy << endl;
				
		}
	}
}
TemperaturaObecna = TemperaturaObecna * TemperaturaChlodzenia;

}

void symulowaneS(std::chrono::seconds s)
{
	auto start = std::chrono::high_resolution_clock::now();
	auto end = start + s;
	do {
		std::this_thread::yield();

		SA();
	} while (std::chrono::high_resolution_clock::now() < end);

}
void TabuS() 
{
	
	zamiana();
	koszt();
	if (dlugoscObecnejTrasy < dlugoscNajlepszejTrasy)
	{
		
		dlugoscNajlepszejTrasy = dlugoscObecnejTrasy;
		najlepszaTrasa = obecnaTrasa;
		if(dlugoscObecnejTrasy< dlugoscKTrasy){
		dlugoscKTrasy = dlugoscObecnejTrasy;
		KTrasa = obecnaTrasa;}
		bylo = 0;
		
	}
	else
	{
		bylo++;
		
	}
	if (bylo > obecnaTrasa.size()) {
		dywer();
	}
		
	
	if (dlugoscObecnejTrasy < dlugoscKTrasy) {
			dlugoscKTrasy = dlugoscObecnejTrasy;
			KTrasa = obecnaTrasa;
		}
	//cout << "bylo :" << dlugoscNajlepszejTrasy << endl;
}
void symulowaneT(std::chrono::seconds s)
{
	auto start = std::chrono::high_resolution_clock::now();
	auto end = start + s;
	do {
		//std::this_thread::yield();
		TabuS();

	} while (std::chrono::high_resolution_clock::now() < end);

}
void symulowaneTa(std::chrono::seconds s)
{
	auto start = std::chrono::high_resolution_clock::now();
	auto end = start + s;
	do {
		std::this_thread::yield();
		auto start = std::chrono::high_resolution_clock::now();

		symulowaneS(std::chrono::seconds(10));

		auto elapsed = std::chrono::high_resolution_clock::now() - start;
		cout << "czakano "
			<< std::chrono::duration_cast <std::chrono::seconds>(elapsed).count()
			<< " sekund.\n";
		cout << endl;
		cout << endl << "Jej dlugosc: " << dlugoscNajlepszejTrasy << endl;
		cout << endl;


	} while (std::chrono::high_resolution_clock::now() < end);

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
	s.zach³any();
	s.najwieksza();
	s.generowanie();
	cout << "Podaj czas trwania algorytmu: ";
	cin >> czas;
	string wybor;
	cout << " Symulowane Wyzarzanie - s \n Tabu Search - t " << endl;
	cin >> wybor;

	if (wybor == "s")
	{
		auto start = std::chrono::high_resolution_clock::now();

		s.symulowaneS(std::chrono::seconds(czas));

		auto elapsed = std::chrono::high_resolution_clock::now() - start;
		cout << "czakano "
			<< std::chrono::duration_cast <std::chrono::seconds>(elapsed).count()
			<< " sekund.\n";
		cout << endl;
		cout << "Najlepsza trasa : " << endl;
		for (int i = 0; i < s.Trasa.size(); i++)
			cout << s.KTrasa[i] << ", ";
		cout << endl << "Jej dlugosc: " << s.dlugoscKTrasy << endl;
		cout <<"rozmiar "<<s.KTrasa.size()<< endl;
	}
	if (wybor == "t")
	{
		
		
		auto start = std::chrono::high_resolution_clock::now();

		s.symulowaneT(std::chrono::seconds(czas));

		auto elapsed = std::chrono::high_resolution_clock::now() - start;
		cout << "czakano "
			<< std::chrono::duration_cast <std::chrono::seconds>(elapsed).count()
			<< " sekund.\n";
		cout << endl;
	cout << "Najlepsza trasa : " << endl;
	for (int i = 0; i < s.KTrasa.size(); i++)
		cout << s.KTrasa[i] << ", ";
	cout << endl << "Jej dlugosc: " << s.dlugoscKTrasy << endl;
	cout << "rozmiar " << s.KTrasa.size() << endl;
	cout << endl;
	}
	


	system("pause"); 
	return 0;
}

