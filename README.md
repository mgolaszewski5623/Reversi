# Reversi  (C++ Console Game)

Projekt konsolowej gry **Reversi** napisanej w języku C++. Gra umożliwia rozgrywkę między dwoma graczami (człowiek-człowiek, człowiek-komputer, komputer-komputer), z możliwością zapisu i wczytywania stanu gry.

## Opis

Gra rozpoczyna się ekranem powitalnym oraz wyświetleniem zasad. Gracz wybiera, czy chce rozpocząć nową grę, czy wczytać zapisany stan. W zależności od konfiguracji, może grać człowiek lub komputer.



## Wymagania

- Kompilator C++ z obsługą C++11 lub nowszą (np. `g++`, `clang++`, MSVC)
- System Windows (użyto funkcji `Sleep()`, `system("cls")`, `_kbhit()`, `_getch()` z Windows.h)
- Terminal konsolowy

## Funkcjonalności
- Rozgrywka na planszy o wybranym rozmiarze
- Tryb:
    - człowiek vs człowiek
    - człowiek vs komputer
    - komputer vs komputer
 - Zapis i wczytywanie gry (konfig.txt)
- Czytelne wyświetlanie planszy
- Zasady wyświetlane na początku gry
- Informacja o zwycięzcy po zakończeniu partii

## Zasady gry
- Grę zaczyna gracz grający czarnymi pionami.

- Celem jest zdobycie jak największej liczby pionów poprzez otaczanie pionów przeciwnika w linii (poziomej, pionowej lub ukośnej).

- Jeśli gracz nie może wykonać ruchu — traci kolejkę.

- Gra kończy się, gdy żaden z graczy nie może wykonać ruchu.

## Pliki projektu

| Plik             | Opis                                         |
|------------------|----------------------------------------------|
| `Manager.cpp/.h`    | Główna logika gry                            |
| `Plansza.cpp/.h`    | Implementacja planszy do gry                 |
| `Czlowiek.cp/.h`   | Implementacja gracza sterowanego przez człowieka |
| `Komputer.cpp/.h`   | Implementacja gracza sterowanego przez komputer |
| `Gracz.h`        | Klasa bazowa dla graczy                      |


