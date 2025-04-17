#include "pch.h"
#include "CppUnitTest.h"

#include "../Plansza.h"
#include "../Komputer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(KONSTRUKTOR_PLANSZA) {
			try {
				Plansza p1(1);
				Assert::Fail();
			}
			catch (std::invalid_argument& e){
				Assert::IsTrue(true);
			}
			try {
				Plansza p2(6);
				Assert::Fail();
			}
			catch (std::invalid_argument& e) {
				Assert::IsTrue(true);
			}
			try {
				Plansza p5(11);
				Assert::Fail();
			}
			catch (std::invalid_argument& e) {
				Assert::IsTrue(true);
			}
			Plansza p3(8);
			Plansza p4(12);
			Assert::IsTrue(p3.dostan_rozmiar() == 8);
			Assert::IsTrue(p4.dostan_rozmiar() == 12);
			Assert::IsTrue(p3.dostan_pole(0, 0) == Plansza::Stan::PUSTE);
			Assert::IsTrue(p3.dostan_pole(4, 4) == Plansza::Stan::CZARNE);
			Assert::IsTrue(p3.dostan_pole(3, 3) == Plansza::Stan::CZARNE);
			Assert::IsTrue(p3.dostan_pole(3, 4) == Plansza::Stan::BIALE);
			Assert::IsTrue(p3.dostan_pole(4, 3) == Plansza::Stan::BIALE);
		}

		TEST_METHOD(SPRAWDZ_POLE) {
			Plansza p(8);
			Assert::IsTrue(p.sprawdz_pole(0, 0));
			Assert::IsTrue(p.sprawdz_pole(7, 0));
			Assert::IsTrue(p.sprawdz_pole(0, 7));
			Assert::IsFalse(p.sprawdz_pole(0, 8));
			Assert::IsFalse(p.sprawdz_pole(8, 0));
			Assert::IsFalse(p.sprawdz_pole(8, 8));
			Assert::IsFalse(p.sprawdz_pole(-1, 0));
			Assert::IsFalse(p.sprawdz_pole(-1, -1));
			Assert::IsFalse(p.sprawdz_pole(0, -1));
			Assert::IsFalse(p.sprawdz_pole(8, -1));
			Assert::IsFalse(p.sprawdz_pole(-1, 8));
		}

		TEST_METHOD(USTAW_POLE) {
			Plansza p(8);
			Plansza::Stan c = Plansza::Stan::CZARNE;
			Plansza::Stan b = Plansza::Stan::BIALE;
			p.ustaw_pole(0, 0, c);
			Assert::IsTrue(p.dostan_pole(0, 0) == c);
			p.ustaw_pole(0, 0, b);
			Assert::IsTrue(p.dostan_pole(0, 0) == b);
			for (int i = 0; i < p.dostan_rozmiar(); i++) {
				for (int j = 0; j < p.dostan_rozmiar(); j++) {
					p.ustaw_pole(i, j, c);
					Assert::IsTrue(p.dostan_pole(i, j) == c);
				}
			}
		}

		TEST_METHOD(ZLICZ_POLA) {
			Plansza p(8);
			Plansza::Stan c = Plansza::Stan::CZARNE;
			Plansza::Stan b = Plansza::Stan::BIALE;
			p.ustaw_pole(0, 0, c);
			Assert::IsTrue(p.zlicz_pola(c) == 3);
			Assert::IsTrue(p.zlicz_pola(b) == 2);
			for (int i = 0; i < p.dostan_rozmiar(); i++) {
				for (int j = 0; j < p.dostan_rozmiar(); j++) {
					p.ustaw_pole(i, j, c);
					Assert::IsTrue(p.dostan_pole(i, j) == c);
				}
			}
			Assert::IsTrue(p.zlicz_pola(c) == 64);
		}

		TEST_METHOD(SPRAWDZ_RUCH) {
			Plansza p(8);
			Plansza::Stan czarny = Plansza::Stan::CZARNE;
			Plansza::Stan bialy = Plansza::Stan::BIALE;
			Plansza::Stan pusty = Plansza::Stan::PUSTE;

			Assert::IsTrue(p.sprawdz_ruch(4, 2, czarny));

			p.ustaw_pole(1, 1, czarny);
			p.ustaw_pole(2, 2, czarny);
			p.ustaw_pole(1, 2, bialy);
			p.ustaw_pole(2, 1, bialy);
			Assert::IsFalse(p.sprawdz_ruch(0, 0, czarny));

			p.ustaw_pole(0, 0, czarny);
			Assert::IsFalse(p.sprawdz_ruch(0, 0, czarny));

			Assert::IsFalse(p.sprawdz_ruch(8, 8, czarny));
		}

		TEST_METHOD(WYKONAJ_RUCH)
		{
			Plansza p(8);
			Plansza::Stan czarny = Plansza::Stan::CZARNE;
			Plansza::Stan bialy = Plansza::Stan::BIALE;

			p.ustaw_pole(0, 0, czarny);
			p.ustaw_pole(0, 1, bialy);
			p.ustaw_pole(0, 2, bialy);
			p.ustaw_pole(0, 3, bialy);

			p.wykonaj_ruch(0, 4, czarny);

			Assert::IsTrue(p.dostan_pole(0, 1) == czarny);
			Assert::IsTrue(p.dostan_pole(0, 2) == czarny);
			Assert::IsTrue(p.dostan_pole(0, 3) == czarny);

			p.ustaw_pole(1, 1, bialy);
			p.ustaw_pole(2, 2, bialy);
			p.ustaw_pole(3, 3, bialy);
			p.wykonaj_ruch(4, 4, czarny);
			Assert::IsTrue(p.dostan_pole(1, 1) == czarny);
			Assert::IsTrue(p.dostan_pole(2, 2) == czarny);
			Assert::IsTrue(p.dostan_pole(3, 3) == czarny);

			p.ustaw_pole(1, 1, czarny);
			p.ustaw_pole(2, 2, czarny);
			p.ustaw_pole(3, 3, czarny);
			p.ustaw_pole(4, 4, bialy);
			p.ustaw_pole(0, 1, czarny);
			p.ustaw_pole(0, 2, czarny);
			p.ustaw_pole(0, 3, czarny);
			p.ustaw_pole(0, 4, bialy);
			p.wykonaj_ruch(0, 0, bialy);
			for (int i = 0; i < 4; i++) {
				Assert::IsTrue(p.dostan_pole(i, i) == bialy);
				Assert::IsTrue(p.dostan_pole(0, i) == bialy);
			}
		}

		TEST_METHOD(MOZLIWE_RUCHY) {
			Plansza p1(8);
			std::vector<std::pair<int, int>> czarne_ruchy = p1.mozliwe_ruchy(Plansza::Stan::CZARNE);
			Assert::IsTrue(czarne_ruchy.size() == 4);
			std::vector<std::pair<int, int>> biale_ruchy = p1.mozliwe_ruchy(Plansza::Stan::BIALE);
			Assert::IsTrue(biale_ruchy.size() == 4);

			Plansza p3(8);
			p3.ustaw_pole(3, 3, Plansza::Stan::PUSTE);
			p3.ustaw_pole(4, 4, Plansza::Stan::PUSTE);
			p3.ustaw_pole(3, 4, Plansza::Stan::PUSTE);
			p3.ustaw_pole(4, 3, Plansza::Stan::PUSTE);
			p3.ustaw_pole(0, 0, Plansza::Stan::CZARNE);
			p3.ustaw_pole(0, 1, Plansza::Stan::CZARNE);

			std::vector<std::pair<int, int>> czarne_ruchy_p3 = p3.mozliwe_ruchy(Plansza::Stan::CZARNE);
			Assert::IsTrue(czarne_ruchy_p3.size() == 0);
		}

		TEST_METHOD(CZY_KONIEC)
		{
			Plansza p1(8);
			p1.ustaw_pole(3, 3, Plansza::Stan::CZARNE);
			p1.ustaw_pole(3, 4, Plansza::Stan::BIALE);
			p1.ustaw_pole(4, 3, Plansza::Stan::BIALE);
			p1.ustaw_pole(4, 4, Plansza::Stan::CZARNE);

			Assert::IsFalse(p1.czy_koniec());

			Plansza p3(8);
			p3.ustaw_pole(0, 0, Plansza::Stan::CZARNE);
			p3.ustaw_pole(0, 1, Plansza::Stan::BIALE);
			p3.ustaw_pole(1, 0, Plansza::Stan::BIALE);
			p3.ustaw_pole(1, 1, Plansza::Stan::CZARNE);
			p3.ustaw_pole(3, 3, Plansza::Stan::BIALE);

			Assert::IsFalse(p3.czy_koniec());

			Plansza p4(8);
			p4.ustaw_pole(3, 3, Plansza::Stan::CZARNE);
			p4.ustaw_pole(3, 4, Plansza::Stan::BIALE);
			p4.ustaw_pole(4, 3, Plansza::Stan::BIALE);
			p4.ustaw_pole(4, 4, Plansza::Stan::CZARNE);
			p4.ustaw_pole(2, 2, Plansza::Stan::BIALE);

			Assert::IsFalse(p4.czy_koniec());

			Plansza p5(8);
			p5.ustaw_pole(3, 3, Plansza::Stan::PUSTE);
			p5.ustaw_pole(4, 3, Plansza::Stan::PUSTE);
			p5.ustaw_pole(3, 4, Plansza::Stan::PUSTE);
			p5.ustaw_pole(4, 4, Plansza::Stan::PUSTE);
			p5.ustaw_pole(0, 0, Plansza::Stan::CZARNE);

			Assert::IsTrue(p5.czy_koniec());
		}

		TEST_METHOD(RUCH_KOMPUTER) {
			Plansza p1(8);
			Komputer k1(Plansza::Stan::CZARNE, &p1);
			p1.ustaw_pole(3, 3, Plansza::Stan::PUSTE);
			p1.ustaw_pole(3, 4, Plansza::Stan::PUSTE);
			p1.ustaw_pole(4, 3, Plansza::Stan::PUSTE);
			p1.ustaw_pole(4, 4, Plansza::Stan::PUSTE);
			p1.ustaw_pole(0, 0, Plansza::Stan::CZARNE);
			p1.ustaw_pole(1, 0, Plansza::Stan::BIALE);
			k1.ruch();
			Assert::IsTrue(p1.dostan_pole(2, 0) == Plansza::Stan::CZARNE);

			Plansza p2(8);
			Komputer k2(Plansza::Stan::CZARNE, &p2);
			k2.ruch();
			Assert::IsTrue(p2.zlicz_pola(Plansza::Stan::CZARNE) == 4);

			Plansza p3(8);
			Komputer k3(Plansza::Stan::CZARNE, &p3);
			p3.ustaw_pole(3, 3, Plansza::Stan::PUSTE);
			p3.ustaw_pole(3, 4, Plansza::Stan::PUSTE);
			p3.ustaw_pole(4, 3, Plansza::Stan::PUSTE);
			p3.ustaw_pole(4, 4, Plansza::Stan::PUSTE);
			k3.ruch();
			Assert::IsTrue(p3.zlicz_pola(Plansza::Stan::CZARNE) == 0);
		}

	};
}
