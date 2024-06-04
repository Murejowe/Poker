#include "Czlowiek.h"
Czlowiek::Czlowiek(int id, int kapital, string karty[2], int stawka, bool dealer, string status) : Gracz(id, kapital, karty, stawka, dealer, status) {}
int Czlowiek::Podbij_stawke(int max_stawka){
	int input;
	cout << "Twoje saldo wynosi: " << kapital << endl << "Jak� kwot� chcesz postawi�?" << endl;
	cin >> input;
	while (input > kapital) {
		cout << "Nie masz tyle na koncie! " << endl << "Jak� kwot� chcesz postawi�?" << endl;
		cin >> input;
	}
	while (input < max_stawka) {
		cout << "Nie mo�esz podbi� stawki o t� warto��!  " << endl << "Jak� kwot� chcesz postawi�?" << endl;
		cin >> input;
	}
	if (input == kapital) {
		status = "all in";
		cout << "All in!" << endl;
	}
	stawka = input;
	kapital -= input;
	return input;
}
int Czlowiek::Check(int max_stawka) {
	if (max_stawka > stawka) {
		if (max_stawka - stawka >= kapital) {
			stawka += kapital;
			kapital = 0;
			status = "all in";
			return stawka;
		}
		else {
			kapital -= max_stawka - stawka;
			stawka = max_stawka;
			status = "check";
			return stawka;
		}
	}
	else {
		status = "check";
		return stawka;
	}
}
int Czlowiek::Ruch_Czlowieka(int max_stawka) {
	cout << "Jaki ruch chcesz wykona�?" << endl << "1) Podbij stawk�" << endl << "2) Spasuj" << endl << "3) Check" << endl;
	int input;
	cin >> input;
	while (sprawdzam(input) == 0) {
		cout << "Wprowadzono niepoprawn� warto��! " << endl << "Jaki ruch chcesz wykona�?" << endl;
		cin >> input;
	}
	if (input == 1) {
		return Podbij_stawke(max_stawka);
	}
	if (input == 2) {
		return Pasuj();
	}
	if (input == 3) {
		if (max_stawka == 0) {
			cout << "Musisz postawi� wej�ci�wk�! " << endl;
			return Ruch_Czlowieka(max_stawka);
		}
		else {
			return Check(max_stawka);
		}
	}
}