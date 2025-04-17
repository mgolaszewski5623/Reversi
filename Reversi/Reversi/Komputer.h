#pragma once

#include "Gracz.h"

class Komputer : public Gracz{
public:
	Komputer(Plansza::Stan s, Plansza* p);
	void ruch() override;
};

