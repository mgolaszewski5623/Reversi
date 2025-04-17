#pragma once

#include "Plansza.h"
#include "Gracz.h"
#include <Windows.h>
#include <conio.h>

class Manager{
private:
	Plansza* p1;
	Gracz* g1;
	Gracz* g2;

	std::vector<int> ustawienia();
	void zapisz(std::vector<int> dane);
	void rezultat();
	void zasady();
	void start_img();
	void gra();
	std::vector<int> ustawienia_nowa();
	std::vector<int> ustawienia_wczytaj();

public:
	Manager();
	void start();
};

