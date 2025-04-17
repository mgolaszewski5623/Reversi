#include "Czlowiek.h"

/*
	Konstruktor
	Parametry:
		Plansza::Stan s - symbol gracza
		Plansza* p - wska�nik na plansze
	Zwracana warto��:
		Brak
	Opis:
		Konstruktor klasy Czlowiek, kt�ry inicjalizuje gracza o podanym symbolu
		i przypisuje wskazanie na obiekt planszy.
*/
Czlowiek::Czlowiek(Plansza::Stan s, Plansza* p) : Gracz(s, p) {}

/*
	ruch
	Parametry:
		Brak
	Zwracana warto��:
		Brak
	Opis:
		Funkcja odpowiedzialna za wykonanie ruchu przez gracza.
		Gracz podaje wsp�rz�dne pola, na kt�re chce wykona� ruch.
		Je�li pole jest dost�pne, ruch jest wykonywany. Je�li nie, gracz zostaje
		poinformowany o niepoprawno�ci ruchu i proszony o ponowny wyb�r.
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