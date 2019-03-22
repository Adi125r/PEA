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

		Sh[r++] = v;                // zapamiêtujemy na stosie bie¿¹cy wierzcho³ek

		if (r < liczba)                  
		{
			visited[v] = true;            // Oznaczamy bie¿¹cy wierzcho³ek jako odwiedzony
			for (u = 0; u < liczba; u++)        // Przegl¹damy s¹siadów wierzcho³ka v
				if (v != u && !visited[u])  // Szukamy nieodwiedzonego jeszcze s¹siada
				{
					koszt += tab[v][u];            // Dodajemy wagê krawêdzi v-u do sumy
					TSP(u);                   // Rekurencyjnie wywo³ujemy szukanie 
					koszt -= tab[v][u];            // Usuwamy wagê krawêdzi z sumy
				}
			visited[v] = false;           // Zwalniamy bie¿¹cy wierzcho³ek
		}
		else if (tab[0][v] > 0)               
		{
			koszt += tab[v][0];               // to sprawdzamy, czy ma najmniejsz¹ sumê wag
			if (koszt < koszt_c)                    // Jeœli tak,
			{
				koszt_c = koszt;                     // To zapamiêtujemy tê sumê
				for (u = 0; u < r; u++)  // oraz kopiujemy stos Sh do S
					S[u] = Sh[u];
				s = r;
			}
			koszt -= tab[v][0];               // Usuwamy wagê krawêdzi v-v0 z sumy
		}
		r--;                        // Usuwamy bie¿¹cy wierzcho³ek ze œcie¿ki
	}
	void Brute::wynik() {
		TSP(0);
		if (s)
		{
			cout << "Przebyta droga : ";   //Wyœwietla przebyt¹ drogê oraz jej koszt 
			for (int i = 0; i < s; i++)
				cout << S[i] << " ";
			cout << "0" << endl;
			cout << "Minimalny koszt : " << koszt_c << endl;
		}

	}

