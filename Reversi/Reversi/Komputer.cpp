#include "Komputer.h"

/*
	Konstruktor
	Parametry:
		Plansza::Stan s - symbol gracza
		Plansza* p - wskaŸnik na plansze
	Zwracana wartoœæ:
		Brak
	Opis:
		Konstruktor klasy Komputer, który inicjalizuje gracza o podanym symbolu
		i przypisuje wskazanie na obiekt planszy.
*/
Komputer::Komputer(Plansza::Stan s, Plansza* p) : Gracz(s, p) {}

/*
	ruch
	Parametry:
		Brak
	Zwracana wartoœæ:
		Brak
	Opis:
		Funkcja odpowiedzialna za wykonanie ruchu przez komputer.
		Komputer losowo wybiera jeden z dostêpnych ruchów i wykonuje go.
		Jeœli nie ma dostêpnych ruchów, komputer informuje o braku mo¿liwoœci wykonania ruchu.
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