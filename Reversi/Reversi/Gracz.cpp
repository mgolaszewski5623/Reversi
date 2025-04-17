#include "Gracz.h"

/*
	Konstruktor
	Parametry:
		Plansza::Stan s - symbol gracza.
		Plansza* p - wska�nik na plansz�.
	Warto�� zwracana:
		brak.
	Opis:
		Inicjalizuje obiekt gracza, przypisuj�c mu symbol oraz wska�nik na plansz�.
*/
Gracz::Gracz(Plansza::Stan s, Plansza* p) {
	plansza = p;
	symbol = s;
}