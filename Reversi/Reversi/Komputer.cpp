#include "Komputer.h"

/*
	Konstruktor
	Parametry:
		Plansza::Stan s - symbol gracza
		Plansza* p - wska�nik na plansze
	Zwracana warto��:
		Brak
	Opis:
		Konstruktor klasy Komputer, kt�ry inicjalizuje gracza o podanym symbolu
		i przypisuje wskazanie na obiekt planszy.
*/
Komputer::Komputer(Plansza::Stan s, Plansza* p) : Gracz(s, p) {}

/*
	ruch
	Parametry:
		Brak
	Zwracana warto��:
		Brak
	Opis:
		Funkcja odpowiedzialna za wykonanie ruchu przez komputer.
		Komputer losowo wybiera jeden z dost�pnych ruch�w i wykonuje go.
		Je�li nie ma dost�pnych ruch�w, komputer informuje o braku mo�liwo�ci wykonania ruchu.
*/
void Komputer::ruch() {
	srand(time(0));
	auto mozliwe_ruchy = plansza->mozliwe_ruchy(symbol);
	if (mozliwe_ruchy.size() != 0) {
		int random = rand() % mozliwe_ruchy.size();
		int y = mozliwe_ruchy[random].first;
		int x = mozliwe_ruchy[random].second;
		plansza->wykonaj_ruch(y, x, symbol);
	}
	else {
		std::cout << "\nBrak mozliwych ruchow.\n";
	}
}