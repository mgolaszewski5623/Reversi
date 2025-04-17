#include "Manager.h"

#include "Czlowiek.h"
#include "Komputer.h"

/*
	Konstruktor+
	Parametry:
		Brak
	Zwracana wartoœæ:
		Brak
	Opis:
		Inicjalizuje wskaŸniki na graczy (g1, g2) i planszê (p1) jako NULL.
*/
Manager::Manager() {
	p1 = NULL;
	g1 = NULL;
	g2 = NULL;
}

/*
	ustawienia_wczytaj
	Parametry:
		Brak
	Zwracana wartoœæ:
		std::vector<int> - lista ustawieñ odczytanych z pliku
	Opis:
		Funkcja wczytuje ustawienia gry z pliku konfiguracyjnego.
		Jeœli plik jest poprawnie odczytany, ustawia odpowiednich graczy (Cz³owiek lub Komputer)
		i zwraca ustawienia w postaci wektora.
		W przypadku b³êdu odczytu lub pliku, rzuca wyj¹tek.
*/
std::vector<int> Manager::ustawienia_wczytaj() {
	int wybor;
	std::vector<int> wyniki;
	Plansza::Stan c = Plansza::Stan::CZARNE;
	Plansza::Stan b = Plansza::Stan::BIALE;
	p1 = new Plansza(8);
	try {
		p1->wczytaj();
	}
	catch(const char* e){
		std::cout << e;
		exit(0);
	}
	std::ifstream plik("konfig.txt");
	if (plik.is_open()) {
		for (int i = 0; i < 4; i++) {
			plik >> wybor;
			wyniki.push_back(wybor);
		}
		plik.close();
		if (wyniki[0]) {
			g1 = new Czlowiek(c, p1);
		}
		else {
			g1 = new Komputer(c, p1);
		}
		if (wyniki[1]) {
			g2 = new Czlowiek(b, p1);
		}
		else {
			g2 = new Komputer(b, p1);
		}
	}
	else {
		throw "\nProblem z wczytaniem pliku.\n";
	}
	return wyniki;
}

/*
	ustawienia_nowa
	Parametry:
		Brak
	Zwracana wartoœæ:
		std::vector<int> - lista ustawieñ nowej gry
	Opis:
		Funkcja pozwala na rêczne ustawienie rozmiaru planszy oraz wyboru graczy.
		Zwraca wektor zawieraj¹cy informacje o graczach i innych ustawieniach.
*/
std::vector<int> Manager::ustawienia_nowa() {
	int wybor;
	std::vector<int> wyniki;
	Plansza::Stan c = Plansza::Stan::CZARNE;
	Plansza::Stan b = Plansza::Stan::BIALE;
	while(true){
		std::cout << "\nPodaj rozmiar planszy:\t";
		std::cin >> wybor;
		try {
			p1 = new Plansza(wybor);
			break;
		}
		catch (std::invalid_argument& e) {
			std::cout << e.what();
		}
	}
	std::cout << "\nGracz 1 to komputer(0), czy czlowiek(1):\t";
	std::cin >> wybor;
	if (wybor) {
		g1 = new Czlowiek(c, p1);
	}
	else {
		g1 = new Komputer(c, p1);
	}
	wyniki.push_back(wybor);
	std::cout << "\nGracz 2 to komputer(0), czy czlowiek(1):\t";
	std::cin >> wybor;
	if (wybor) {
		g2 = new Czlowiek(b, p1);
	}
	else {
		g2 = new Komputer(b, p1);
	}
	wyniki.push_back(wybor);
	if (wyniki[0] && wyniki[1]) {
		wyniki.push_back(0);
	}
	else {
		wyniki.push_back(1);
	}
	wyniki.push_back(1);
	return wyniki;
}

/*
	ustawienia
	Parametry:
		Brak
	Zwracana wartoœæ:
		std::vector<int> - ustawienia gry
	Opis:
		Funkcja wyœwietla menu i wybiera, czy gra ma byæ nowa, czy wczytana z pliku.
		Zwraca odpowiednie ustawienia.
*/
std::vector<int> Manager::ustawienia() {
	int wybor;
	std::vector<int> wyniki;
	Plansza::Stan c = Plansza::Stan::CZARNE;
	Plansza::Stan b = Plansza::Stan::BIALE;
	std::cout << "\nNowa gra(0), czy wczytaj gre(1)\t";
	std::cin >> wybor;
	if (wybor) {
		try {
			wyniki = ustawienia_wczytaj();
		}
		catch (const char* e) {
			std::cout << e;
			exit(0);
		}
	}
	else {
		wyniki = ustawienia_nowa();
	}
	return wyniki;
}

/*
	zapisz
	Parametry:
		dane - dane do zapisania
	Zwracana wartoœæ:
		Brak
	Opis:
		Zapisuje aktualny stan gry do pliku konfiguracyjnego.
*/
void Manager::zapisz(std::vector<int> dane) {
	try {
		g1->plansza->zapisz();
	}
	catch (const char* e) {
		std::cout << e;
		exit(0);
	}
	std::ofstream plik("konfig.txt");
	if (plik.is_open()) {
		plik << dane[0] << "\n";
		plik << dane[1] << "\n";
		plik << dane[2] << "\n";
		plik << dane[3] << "\n";
		plik.close();
	}
	else {
		throw "\nProblem z zapisem pliku.\n";
	}
}

/*
	rezultat
	Parametry:
		Brak
	Zwracana wartoœæ:
		Brak
	Opis:
		Funkcja sprawdza wynik gry, porównuj¹c liczbê pionów czarnych i bia³ych na planszy.
		Og³asza zwyciêzcê lub remis.
*/
void Manager::rezultat() {
	int ilosc_c = p1->zlicz_pola(g1->symbol);
	int ilosc_b = p1->zlicz_pola(g2->symbol);
	if (ilosc_c > ilosc_b) {
		std::cout << "\nGracz 1 wygrywa.\n";
	}
	else if (ilosc_c < ilosc_b) {
		std::cout << "\nGracz 2 wygrywa.\n";
	}
	else {
		std::cout << "\nRemis.\n";
	}
}

/*
	gra
	Parametry:
		Brak
	Zwracana wartoœæ:
		Brak
	Opis:
		G³ówna funkcja gry, która kontroluje przebieg gry, na przemian wykonuj¹c ruchy graczy.
		Obs³uguje równie¿ zapisywanie stanu gry oraz zakoñczenie gry.
*/
void Manager::gra() {
	int powtorz = 0;
	do {
		auto dane = ustawienia();
		int kolej = dane[3];
		int tryb = dane[2];
		std::system("cls");
		p1->wypisz_plansze();
		do {
			if (kolej) {
				std::cout << "ruch gracz1";
				g1->ruch();
			}
			else {
				std::cout << "ruch gracz2";
				g2->ruch();
			}
			Sleep(100);
			std::system("cls");
			p1->wypisz_plansze();
			if (_kbhit()) {
				char key = _getch();
				if (key == 'z' || key == 'Z') {
					zapisz(dane);
					std::cout << "Gra zapisana!\n";
				}
			}
			if (tryb) {
				Sleep(1000);
			}
			else {
				Sleep(100);
			}

			kolej = (kolej) ? 0 : 1;
		} while (!p1->czy_koniec());
		rezultat();
		std::cout << "\nCzy chcesz zagrac? Nie(0) - Tak(1)\t";
		std::cin >> powtorz;
	} while (powtorz);
	delete g1;
	delete g2;
	delete p1;
}

/*
	zasady
	Parametry:
		Brak
	Zwracana wartoœæ:
		Brak
	Opis:
		Funkcja wyœwietla zasady gry. Oczekuje na naciœniêcie klawisza przez u¿ytkownika, aby przejœæ dalej.
*/
void Manager::zasady() {
	std::string tekst = R"(
Wszystko rozpoczyna sie od stanu, w ktorym na planszy sa juz ustawione cztery piony.
Sa to dwa piony czarne i dwa biale. Pierwszy ruch wykonuje rozgrywajacy piony czarne.

Piony przeciwnika zdobywa sie, otaczajac je w jednej linii.
Zdobyte piony zmieniaja kolor i przynaleznosc. 
Na przyklad jesli gracz rozgrywajacy piony czarne spostrzeze linie pionow bialych, 
	na ktorej jednym koncu stoi pion czarny, moze dostawic swoj pion takze na drugim koncu linii. 
Wszystkie otoczone biale piony zmienia kolor na czarny (dotyczy to wszystkich linii prostych: poziomych, pionowych i ukosnych).

Jedyne dozwolone ruchy polegaja na otaczaniu i zdobywaniu pionow przeciwnika. 
W kazdym ruchu nalezy zdobyc co najmniej jeden pion przeciwnika.

Jesli gracz nie moze wykonczyc zadnego dozwolonego ruchu, traci kolejke i wykonuje go drugi gracz.
	)";

	bool pomin = false;
	for (int i = 0; i < tekst.size(); ++i) {
		if (_kbhit()) {
			pomin = true;
		}
		std::cout << tekst[i];
		if (!pomin) {
			Sleep(1);
		}
	}
}

/*
	start_img
	Parametry:
		Brak
	Zwracana wartoœæ:
		Brak
	Opis:
		Funkcja wyœwietla pocz¹tkowy obrazek tekstowy.
*/
void Manager::start_img() {
	std::string tekst = R"(
-                                                                                                   
-       .=*#%@@@@@%:=##%%@@@@@@@-#%%@@%.#%%%@%%%%@@@@@@#.=*#%@@@@@%-  *@@@@@*.=  :%@@%%#*=          
-         :@@@@@@@@@* #@@@@%::-#-.@@@@* =@@@..@@@@@*::-%. -@@@@@@@@@#@@@@@@@+@@:   =@@@.            
-         +@@+:@@@@@# +@@@@%@@#  .+@@@@.@@@. .@@@@@%@@=   -@@*.@@@@@%=@@@@@@%=:.   +@@@+            
-        .%@@@@@@@@*  -@@@@%*%% .  #@@@-@@=   -@@@@##%+ -.*@@@@@@@@#.  .-*@@@@@@%. *@@@%            
-        :@@@=%@@#:   .@@@@-:..**  :@@@@@+    .@@@@:...#= @@@**@@#:. .#=.:#@@@@@@: %@@@@:           
-       .+@@@# -@@@@*=%@@@@@@@@@+  .%@@@@.  .+%@@@@@@@@@.=@@@%.:@@@@*.++@@@@@@@%: .@@@@@@#          
-         ......-..    ..........  ........    .......... ......-...  .. .....   ......             
)";
	std::cout << tekst;
}

/*
	start
	Parametry:
		Brak
	Zwracana wartoœæ:
		Brak
	Opis:
		Inicjalizuje pocz¹tek gry, wyœwietlaj¹c obrazek, zasady gry, a nastêpnie rozpoczyna grê.
*/
void Manager::start() {
	start_img();
	zasady();
	gra();
}