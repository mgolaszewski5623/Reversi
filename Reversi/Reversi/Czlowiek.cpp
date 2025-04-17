#include "Czlowiek.h"

/*
	Konstruktor
	Parametry:
		Plansza::Stan s - symbol gracza
		Plansza* p - wskaŸnik na plansze
	Zwracana wartoœæ:
		Brak
	Opis:
		Konstruktor klasy Czlowiek, który inicjalizuje gracza o podanym symbolu
		i przypisuje wskazanie na obiekt planszy.
*/
Czlowiek::Czlowiek(Plansza::Stan s, Plansza* p) : Gracz(s, p) {}

/*
	ruch
	Parametry:
		Brak
	Zwracana wartoœæ:
		Brak
	Opis:
		Funkcja odpowiedzialna za wykonanie ruchu przez gracza.
		Gracz podaje wspó³rzêdne pola, na które chce wykonaæ ruch.
		Jeœli pole jest dostêpne, ruch jest wykonywany. Jeœli nie, gracz zostaje
		poinformowany o niepoprawnoœci ruchu i proszony o ponowny wybór.
*/
void Czlowiek::ruch() {
	int y, x;
	auto mozliwe_ruchy = plansza->mozliwe_ruchy(symbol);
	if (mozliwe_ruchy.size() != 0) {
		while (1) {
			std::cout << "\nPodaj y:\t";
			std::cin >> y;
			std::cout << "\nPodaj x:\t";
			std::cin >> x;
			if (plansza->sprawdz_ruch(y, x, symbol)) {
				plansza->wykonaj_ruch(y, x, symbol);
				break;
			}
			else {
				std::cout << "\nNie poprawny ruch.\n";
			}
		}
	}
	else {
		std::cout << "\nBrak mozliwosci ruchy.\n";
	}
}