#include "Bot.h"
Bot::Bot(int id, int kapital, string karty[2], int stawka, bool dealer, string status, int poziom_trudnosci) : Gracz(id, kapital, karty, stawka, dealer, status), poziom_trudnosci(poziom_trudnosci) {}
int Bot::Podbij_stawke(int max_stawka) {
	stawka += 20;
	kapital -= 20;
	if (kapital == 0) {
		status = "all in";
	}
	return 20;
}
int Bot::Pasuj() {
	status = "pass";
	return 0;
}
int Bot::Check(int max_stawka) {
	if (max_stawka > stawka) {
		if (max_stawka - stawka >= kapital) {
			stawka += kapital;
			kapital = 0;
			status = "all in";
			cout << "Bot Check All in!" << endl;
			return stawka;
		}
		else {
			kapital -= max_stawka - stawka;
			stawka = max_stawka;
			cout << "Bot Check" << endl;
			status = "check";
			return stawka;
		}
	}
	else {
		cout << "Bot Check" << endl;
		status = "check";
		return stawka;
	}
}
int Bot::Ruch_Bota(int max_stawka) {
	if (max_stawka == 0) {
		cout << "Bot Podbija stawkê" << endl;
		return Podbij_stawke(max_stawka);
	}
	else {
		return Check(max_stawka);
	}
}