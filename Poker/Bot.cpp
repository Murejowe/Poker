#include "Bot.h"
Bot::Bot(int id, int kapital, string karty[2], int stawka, bool dealer, string status, int poziom_trudnosci) : Gracz(id, kapital, karty, stawka, dealer, status), poziom_trudnosci(poziom_trudnosci) {}
int Bot::Podbij_stawke(int max_stawka) {
	stawka = 20;
	kapital -=20;
	return 20;
}
int Bot::Pasuj() {
	status = "pass";
	return 0;
}
int Bot::Check() {
	status = "check";
	return 0;
}
int Bot::Ruch_Bota(int max_stawka) {
	if (max_stawka == 0) {
		return Podbij_stawke(max_stawka);
		
	}
	else {
		return Check();
	}
}