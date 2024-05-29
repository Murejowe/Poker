#include "Bot.h"
Bot::Bot(int id, int kapital, string karty[2], int stawka, bool dealer, string status, int poziom_trudnosci) : Gracz(id, kapital, karty, stawka, dealer, status), poziom_trudnosci(poziom_trudnosci) {}
int Bot::Podbij_stawke() {
	return 0;
}
void Bot::Pasuj() {

}
void Bot::Check() {

}
void Bot::Ruch_Bota(int poziom_trudnosci) {

}