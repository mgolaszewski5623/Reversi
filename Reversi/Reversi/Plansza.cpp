#include "Plansza.h"

/*
	Konstruktor
	Parametry:
		int r - rozmiar planszy
	Zwracana warto��:
		Brak
	Opis:
		Inicjalizuje plansz� o podanym rozmiarze. Je�li rozmiar jest mniejszy ni� 8
		lub nieparzysty, rzuca wyj�tek.
*/
Plansza::Plansza(int r) {
	// rozmiar = (r < 8 || r % 2 != 0) ? 8 : r;
	if (r < 8 || r % 2 != 0) {
		throw std::invalid_argument("\nNiewlasciwy rozmiar planszy (rozmiar musi byc wiekszy od 8 i parzysty).\n");
	}
	rozmiar = r;
	tablica = std::vector<std::vector<Stan>>(rozmiar, std::vector<Stan>(rozmiar, PUSTE));
	tablica[rozmiar / 2][rozmiar / 2] = CZARNE;
	tablica[rozmiar / 2 - 1][rozmiar / 2 - 1] = CZARNE;
	tablica[rozmiar / 2][rozmiar / 2 - 1] = BIALE;
	tablica[rozmiar / 2 - 1][rozmiar / 2] = BIALE;
}

/*
	dostan_rozmiar
	Parametry:
		Brak
	Zwracana warto��:
		int - rozmiar planszy
	Opis:
		Zwraca rozmiar planszy.
*/
int Plansza::dostan_rozmiar() {
	return rozmiar;
}

/*
	sprawdz_pole
	Parametry:
		int y - wsp�rz�dna wiersza
		int x - wsp�rz�dna kolumny
	Zwracana warto��:
		bool - true, je�li pole jest poprawne, false w przeciwnym razie
	Opis:
		Sprawdza, czy dane pole znajduje si� na planszy.
*/
bool Plansza::sprawdz_pole(int y, int x) {
	if (x < 0 || y < 0 || x >= rozmiar || y >= rozmiar) {
		return false;
	}
	return true;
}

/*
	dostan_pole
	Parametry:
		int y - wsp�rz�dna wiersza
		int x - wsp�rz�dna kolumny
	Zwracana warto��:
		Stan - stan danego pola (BRAK, CZARNE, BIALE, PUSTE)
	Opis:
		Zwraca stan pola na podstawie jego wsp�rz�dnych.
*/
Plansza::Stan Plansza::dostan_pole(int y, int x) {
	if (sprawdz_pole(y, x)) {
		return tablica[y][x];
	}
	return BRAK;
}

/*
	ustaw_pole
	Parametry:
		int y - wsp�rz�dna wiersza
		int x - wsp�rz�dna kolumny
		Stan s - stan do ustawienia
	Zwracana warto��:
		Brak
	Opis:
		Ustawia stan pola na planszy na podany stan, je�li pole jest poprawne.
*/
void Plansza::ustaw_pole(int y, int x, Plansza::Stan s) {
	if (sprawdz_pole(y, x)) {
		tablica[y][x] = s;
	}
}

/*
	wypisz_ramke
	Parametry:
		int pozycja - parametr steruj�cy wypisaniem ramki na pocz�tku lub ko�cu planszy
	Zwracana warto��:
		Brak
	Opis:
		Wypisuje ramk� z numerami kolumn i obramowaniem planszy na pocz�tku lub na ko�cu.
*/
void Plansza::wypisz_ramke(int pozycja) {
	int szerokosc = std::to_string(rozmiar - 1).length();
	std::stringstream ss1, ss2;

	ss1 << std::string(szerokosc + 1, ' ');
	for (int j = 0; j < rozmiar; j++) {
		ss1 << std::setw(szerokosc + 1) << j;
	}
	ss1 << "\n";

	ss2 << std::string(szerokosc + 1, ' ') << "+";
	for (int i = 0; i < rozmiar; i++) {
		ss2 << std::string(szerokosc, '-') << "-";
	}
	ss2 << "+\n";

	if (pozycja) {
		std::cout << ss2.str() << ss1.str();
	}
	else {
		std::cout << ss1.str() << ss2.str();
	}
}

/*
	wypisz_plansze
	Parametry:
		Brak
	Zwracana warto��:
		Brak
	Opis:
		Wypisuje ca�� plansz� z oznaczeniami p�l oraz numerami wierszy i kolumn.
*/
void Plansza::wypisz_plansze() {
	int szerokosc = std::to_string(rozmiar - 1).length();
	std::cout << "\n";
	wypisz_ramke(0);
	for (int i = 0; i < rozmiar; i++) {
		std::cout << std::setw(szerokosc) << i << " | ";
		for (int j = 0; j < rozmiar; j++) {
			switch (tablica[i][j]) {
			case CZARNE:
				std::cout << "B" << std::string(szerokosc, ' ');
				break;
			case BIALE:
				std::cout << "W" << std::string(szerokosc, ' ');
				break;
			case PUSTE:
				std::cout << "." << std::string(szerokosc, ' ');
				break;
			}
		}
		std::cout << "| " << i << "\n";
	}
	wypisz_ramke(1);
}

/*
	zlicz_pola
	Parametry:
		Stan s - stan, kt�ry ma zosta� zliczony (CZARNE, BIALE, PUSTE)
	Zwracana warto��:
		int - liczba p�l o danym stanie
	Opis:
		Zlicza i zwraca liczb� p�l na planszy o podanym stanie.
*/
int Plansza::zlicz_pola(Plansza::Stan s) {
	int ilosc = 0;
	for (int i = 0; i < rozmiar; i++) {
		for (int j = 0; j < rozmiar; j++) {
			if (tablica[i][j] == s) {
				ilosc++;
			}
		}
	}

	return ilosc;
}

/*
	zapisz
	Parametry:
		Brak
	Zwracana warto��:
		Brak
	Opis:
		Zapisuje aktualny stan planszy do pliku plansza.txt.
		W pliku zapisywany jest rozmiar planszy oraz stan ka�dego pola.
		W przypadku problemu z zapisem rzuca wyj�tek.
*/
void Plansza::zapisz() {
	std::ofstream plik("plansza.txt");

	if (plik.is_open()) {
		plik << rozmiar << "\n";
		for (int i = 0; i < rozmiar; i++) {
			for (int j = 0; j < rozmiar; j++) {
				switch (tablica[i][j]) {
				case CZARNE:
					plik << "C";
					break;
				case BIALE:
					plik << "B";
					break;
				default:
					plik << ".";
				}
			}
		}
		plik.close();
	}
	else {
		throw "\nProblem z zapisem pliku.\n";
	}
}

/*
	wczytaj
	Parametry:
		Brak
	Zwracana warto��:
		Brak
	Opis:
		Wczytuje stan planszy z pliku plansza.txt.
		Odczytuje rozmiar planszy oraz stany poszczeg�lnych p�l.
		W przypadku problemu z otwarciem pliku rzuca wyj�tek.
*/
void Plansza::wczytaj() {
	std::ifstream plik("plansza.txt");
	if (plik.is_open()) {
		plik >> rozmiar;
		tablica = std::vector<std::vector<Stan>>(rozmiar, std::vector<Stan>(rozmiar));
		char znak;
		for (int i = 0; i < rozmiar; i++) {
			for (int j = 0; j < rozmiar; j++) {
				char ch;
				plik >> ch;
				switch (ch) {
				case 'C':
					tablica[i][j] = CZARNE;
					break;
				case 'B':
					tablica[i][j] = BIALE;
					break;
				default:
					tablica[i][j] = PUSTE;
					break;
				}
			}
		}
		plik.close();
	}
	else {
		throw "\nProblem z wczytaniem pliku.\n";
	}
}

/*
	sprawdz_ruch
	Parametry:
		int y - wsp�rz�dna wiersza
		int x - wsp�rz�dna kolumny
		Stan s - stan gracza (CZARNE lub BIALE)
	Zwracana warto��:
		bool - true, je�li ruch jest poprawny, false w przeciwnym razie
	Opis:
		Sprawdza, czy wykonanie ruchu w podanym miejscu jest mo�liwe zgodnie z zasadami gry.
*/
bool Plansza::sprawdz_ruch(int y, int x, Plansza::Stan s) {
	if (!sprawdz_pole(y, x) || tablica[y][x] != PUSTE) {
		return false;
	}
	Stan przeciwnik = (s == CZARNE) ? BIALE : CZARNE;
	std::vector<std::pair<int, int>> kierunki = {{-1,  0}, {1,  0}, {0, -1}, {0,  1}, {-1, -1}, {-1,  1}, {1, -1}, {1,  1}};
	for (const auto& k : kierunki) {
		int ky = k.first;
		int kx = k.second;
		int y2 = y + ky;
		int x2 = x + kx;
		bool linia = false;
		while (dostan_pole(y2, x2) == przeciwnik) {
			y2 += ky;
			x2 += kx;
			linia = true;
		}
		if (linia && dostan_pole(y2, x2) == s) {
			return true;
		}
	}
	return false;
}

/*
	wykonaj_ruch
	Parametry:
		int y - wsp�rz�dna wiersza
		int x - wsp�rz�dna kolumny
		Stan s - stan gracza (CZARNE lub BIALE)
	Zwracana warto��:
		Brak
	Opis:
		Wykonuje ruch gracza w podanym miejscu i aktualizuje plansz�, odwracaj�c pionki przeciwnika w linii.
*/
void Plansza::wykonaj_ruch(int y, int x, Plansza::Stan s) {
	ustaw_pole(y, x, s);
	Stan przeciwnik = (s == CZARNE) ? BIALE : CZARNE;
	std::vector<std::pair<int, int>> kierunki = { {-1,  0}, {1,  0}, {0, -1}, {0,  1}, {-1, -1}, {-1,  1}, {1, -1}, {1,  1} };
	for (const auto& k : kierunki) {
		int ky = k.first;
		int kx = k.second;
		int y2 = y + ky;
		int x2 = x + kx;
		bool linia = false;
		while (sprawdz_pole(y2, x2) && dostan_pole(y2, x2) == przeciwnik) {
			y2 += ky;
			x2 += kx;
			linia = true;
		}
		if (linia && dostan_pole(y2, x2) == s) {
			y2 -= ky;
			x2 -= kx;
			while (sprawdz_pole(y2, x2) && (y2 != y || x2 != x)) {
				ustaw_pole(y2, x2, s);
				y2 -= ky;
				x2 -= kx;
			}
		}
	}
}

/*
	mozliwe_ruchy
	Parametry:
		Stan s - stan gracza (CZARNE lub BIALE)
	Zwracana warto��:
		std::vector<std::pair<int, int>> - lista wsp�rz�dnych mo�liwych ruch�w
	Opis:
		Generuje list� wszystkich mo�liwych ruch�w dla danego gracza.
*/
std::vector<std::pair<int, int>> Plansza::mozliwe_ruchy(Plansza::Stan s) {
	std::vector<std::pair<int, int>> wynik;
	for (int y = 0; y < rozmiar; y++) {
		for (int x = 0; x < rozmiar; x++) {
			if (sprawdz_ruch(y, x, s)) {
				wynik.push_back({ y, x });
			}
		}
	}
	return wynik;
}

/*
	czy_koniec
	Parametry:
		Brak
	Zwracana warto��:
		bool - true, je�li nie ma mo�liwych ruch�w dla obu graczy, false w przeciwnym razie
	Opis:
		Sprawdza, czy gra dobieg�a ko�ca, czyli czy �aden z graczy nie ma ju� mo�liwych ruch�w.
*/
bool Plansza::czy_koniec() {
	auto ruchy_czarne = mozliwe_ruchy(CZARNE);
	auto ruchy_biale = mozliwe_ruchy(BIALE);
	if (ruchy_czarne.size() != 0 || ruchy_biale.size() != 0) {
		return false;
	}
	return true;
}