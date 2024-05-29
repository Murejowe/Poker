#include "Czlowiek.h"
Czlowiek::Czlowiek(int id, int kapital, string karty[2], int stawka, bool dealer, string status) : Gracz(id, kapital, karty, stawka, dealer, status) {}
int Czlowiek::Podbij_stawke(){
	int input;
	cout << "Twoje saldo wynosi: " << kapital << endl << "Jak¹ kwotê chcesz postawiæ?" << endl;
	cin >> input;
	while (input > kapital) {
		cout << "Wprowadzono niepoprawn¹ wartoœæ! " << endl << "Jak¹ kwotê chcesz postawiæ?" << endl;
		cin >> input;
	}
	stawka = input;
	kapital =- input;
	return input;
}
void Czlowiek::Pasuj() {
	status == "pass";
}
void Czlowiek::Check() {
	status == "check";
}
void Czlowiek::Ruch_Czlowieka() {
	cout << "Jaki ruch chcesz wykonaæ?" << endl << "1) Podbij stawkê" << endl << "2) Spasuj" << endl << "3) Check" << endl;
	int input;
	cin >> input;
	while (sprawdzam(input) == 0) {
		cout << "Wprowadzono niepoprawn¹ wartoœæ! " << endl << "Jaki ruch chcesz wykonaæ?" << endl;
		cin >> input;
	}
	if (input == 1) {
		Podbij_stawke();
	}
	if (input == 2) {
		Pasuj();
	}
	if (input == 3) {
		Check();
	}
}