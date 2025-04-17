#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <Windows.h>

class Plansza {
public:
	enum Stan {
		PUSTE,
		CZARNE,
		BIALE,
		BRAK
	};

private:
	int rozmiar;
	std::vector<std::vector<Stan>> tablica;

public:
	Plansza(int r);
	int dostan_rozmiar();
	bool sprawdz_pole(int y, int x);
	Stan dostan_pole(int y, int x);
	void ustaw_pole(int y, int x, Stan s);
	void wypisz_ramke(int pozycja);
	void wypisz_plansze();
	int zlicz_pola(Stan s);
	void zapisz();
	void wczytaj();
	bool sprawdz_ruch(int y, int x, Stan s);
	void wykonaj_ruch(int y, int x, Stan s);
	std::vector<std::pair<int, int>> mozliwe_ruchy(Stan s);
	bool czy_koniec();
};