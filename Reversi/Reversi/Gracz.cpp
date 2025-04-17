#include "Gracz.h"

/*
	Konstruktor
	Parametry:
		Plansza::Stan s - symbol gracza.
		Plansza* p - wskaŸnik na planszê.
	Wartoœæ zwracana:
		brak.
	Opis:
		Inicjalizuje obiekt gracza, przypisuj¹c mu symbol oraz wskaŸnik na planszê.
*/
Gracz::Gracz(Plansza::Stan s, Plansza* p) {
	plansza = p;
	symbol = s;
}