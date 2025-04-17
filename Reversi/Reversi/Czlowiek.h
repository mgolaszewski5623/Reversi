#pragma once

#include "Gracz.h"

class Czlowiek : public Gracz{
public:
	Czlowiek(Plansza::Stan s, Plansza* p);
	void ruch() override;
};

