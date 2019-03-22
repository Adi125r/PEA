#include "pch.h"
	Brute::Brute() {}
	Brute::~Brute() {
		for (int i = 0; i < liczba; i++)
		{
			delete[] tab[i];
		}
		delete[] tab;
		delete[] S;
		delete[] Sh;
		delete[] visited;
	}
	void Brute:: wczytaj(string nazwa)         //wczytuje dane z pliku
	{

		fstream plik;
		plik.open(nazwa, ios::in);
		if (plik.good() == false) {

			cout << "Nie udalo sie otworzyc pliku";
			exit(0);
		}
		if (plik.good() == true)
		{
			plik >> liczba;
			tab = new int *[liczba];
			visited = new bool[liczba];
			S = new int[liczba];
			Sh = new int[liczba];
			for (int i = 0; i < liczba; i++)
			{
				tab[i] = new int[liczba];
				visited[i] = false;
			}
			for (int i = 0; i < liczba; i++)
			{
				for (int j = 0; j < liczba; j++)
				{
					plik >> tab[i][j];
				}
			}
			
		}plik.close();
	}
	void Brute::TSP(int v)
	{
		int u;

		Sh[r++] = v;                // zapami�tujemy na stosie bie��cy wierzcho�ek

		if (r < liczba)                  
		{
			visited[v] = true;            // Oznaczamy bie��cy wierzcho�ek jako odwiedzony
			for (u = 0; u < liczba; u++)        // Przegl�damy s�siad�w wierzcho�ka v
				if (v != u && !visited[u])  // Szukamy nieodwiedzonego jeszcze s�siada
				{
					koszt += tab[v][u];            // Dodajemy wag� kraw�dzi v-u do sumy
					TSP(u);                   // Rekurencyjnie wywo�ujemy szukanie 
					koszt -= tab[v][u];            // Usuwamy wag� kraw�dzi z sumy
				}
			visited[v] = false;           // Zwalniamy bie��cy wierzcho�ek
		}
		else if (tab[0][v] > 0)               
		{
			koszt += tab[v][0];               // to sprawdzamy, czy ma najmniejsz� sum� wag
			if (koszt < koszt_c)                    // Je�li tak,
			{
				koszt_c = koszt;                     // To zapami�tujemy t� sum�
				for (u = 0; u < r; u++)  // oraz kopiujemy stos Sh do S
					S[u] = Sh[u];
				s = r;
			}
			koszt -= tab[v][0];               // Usuwamy wag� kraw�dzi v-v0 z sumy
		}
		r--;                        // Usuwamy bie��cy wierzcho�ek ze �cie�ki
	}
	void Brute::wynik() {
		TSP(0);
		if (s)
		{
			cout << "Przebyta droga : ";   //Wy�wietla przebyt� drog� oraz jej koszt 
			for (int i = 0; i < s; i++)
				cout << S[i] << " ";
			cout << "0" << endl;
			cout << "Minimalny koszt : " << koszt_c << endl;
		}

	}

