#ifndef Brute_Force_H
#define Brute_Force_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <sstream>
using namespace std;
class Brute
{
public:
	int liczba;
	int **tab;
	int koszt_c = INT_MAX;
	int koszt;
	bool *visited;
	int *S, *Sh;
	int s = 0;
	int r = 0;
	Brute();
	~Brute();
	void  wczytaj(string nazwa);       
	
	void TSP(int v);
	
	void wynik();

};

#endif