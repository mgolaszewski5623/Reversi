#pragma once

#include "Plansza.h"

class Gracz{
public:
	Plansza::Stan symbol;
	Plansza* plansza;

	Gracz(Plansza::Stan s, Plansza* p);

	virtual void ruch() = 0;
};

