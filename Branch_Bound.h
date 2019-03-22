#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <sstream>
using namespace std;
class Problem
{
public:
	int liczba;
	int **waga;
	int *sciezka;
	int *tym_S;
	bool *visited;
	int koszt = INT_MAX;
	void wczytaj(string nazwa);

	void copy(int *tym_S);
	
	int firstMin(int i);
	
	void Branchp(int granica, int tym_k, int level, int *tym_S);
	
	void Branch();
};