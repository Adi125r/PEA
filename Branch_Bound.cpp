#include "pch.h"
void Problem:: wczytaj(string nazwa) {

		fstream plik;
		plik.open(nazwa, ios::in);
		if (plik.good() == false) {

			cout << "Nie udalo sie otworzyc pliku";
			exit(0);
		}
		if (plik.good() == true)
		{
			plik >> liczba;
			waga = new int *[liczba];
			visited = new bool[liczba];
			sciezka = new int[liczba + 1];
			tym_S = new int[liczba + 1];
			for (int i = 0; i < liczba; i++)
			{

				waga[i] = new int[liczba];
				visited[i] = false;

			}



			for (int i = 0; i < liczba; i++) {
				for (int j = 0; j < liczba; j++) {
					plik >> waga[i][j];

				}

			}


		}plik.close();
	}

void Problem::copy(int *tym_S)					//kopiowanie tymczasowej drogi do najkrótszej 
	{
		for (int i = 0; i < liczba; i++)
			sciezka[i] = tym_S[i];
		sciezka[liczba] = tym_S[0];			// dodanie powrotu do startowego wierzcho³aka 
	}

int Problem::firstMin(int i)			// szukanie najmniejszego kosztu do kolejnego miasta z wierzcho³ka i 
	{
		int min = INT_MAX;
		for (int k = 0; k < liczba; k++)
			if (waga[i][k] < min && i != k)
				min = waga[i][k];
		return min;
	}


void Problem:: Branchp(int granica, int tym_k, int level, int *tym_S)
	{
		if (level == liczba)												// jeœli mamy wype³ninony tymczasowa scie¿kê iloœci¹  miastami 
		{
			if (tym_S[level - 1] != tym_S[0])								// sprawdzamy czy ostatnie miasto jest rózne od startowego 
			{

				int koszt_t = tym_k + waga[tym_S[level - 1]][tym_S[0]];	// obliczmy koszt drogi  

				if (koszt_t < koszt)										// sprawdzamy czy obliczony koszt jest mniejszy od ostatecznego kosztu  
				{
					copy(tym_S);											// kopiujemy przebyta drogê oraz przypisujemy  wartoœæ kosztowi 
					koszt = koszt_t;
				}
			}
			return;
		}
		for (int i = 0; i < liczba; i++)
		{
			if (tym_S[level - 1] != i && visited[i] == false)				//sprawdzamy czy miata nie sa takie same i czy nie zosta³o ju¿ odwiedzone
			{
				int temp = granica;
				tym_k += waga[tym_S[level - 1]][i];							// obliczamy tymczasowy koszt 

				granica -= ((firstMin(tym_S[level - 1]) + firstMin(i)) / 2);       //obliczamy granicê dla algorytmu
				
				if (granica + tym_k < koszt)									//Sprawdzamy czy tymczasowy koszt z granica nie przekrocza kosztu dojscia
				{
					tym_S[level] = i;											// przypisanie miasta do tymczasowej scie¿ki   
					visited[i] = true;											//zaznaczenie ze miasto jest ju¿ odwiedzone

					Branchp(granica, tym_k, level + 1, tym_S);				//Rekurencyjne wywo³anie szukania 
				}

				tym_k -= waga[tym_S[level - 1]][i];							//usuwamy z kosztu wage (level - 1) - i
				granica = temp;
				for (int i = 0; i < liczba; i++) {							//przypisanie wszystkim miast¹ ze nie sa odwiedzone 
					visited[i] = false;
				}

				for (int j = 0; j <= level - 1; j++)						//przypisanie miast¹ które sa ju¿ w tymczasowej scieszce  ze sa odwiedzone
					visited[tym_S[j]] = true;
			}
		}
	}

void Problem::Branch()
	{


		int granica = 0;

		for (int i = 0; i < liczba; i++)										//obliczenie watoœci granicy 
			granica += firstMin(i);

		//granica = granica / 2;+ secondMin(i)


		visited[0] = true;														// przypisanie odwiedzin dla wierzcho³ka 0
		tym_S[0] = 0;															//przypisanie wiezrcho³ka 0 do tymczasowej scie¿ki

		Branchp(granica, 0, 1, tym_S);
		cout << "Przebyta droga :";
		for (int i = 0; i < liczba + 1; i++)
			cout << sciezka[i] << " ";
		cout << endl;
		cout << "Minimalny koszt  : " << koszt << endl;


	}

