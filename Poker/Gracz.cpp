#include "Gracz.h"
Gracz::Gracz(int id, int kapital, string karty[2], int stawka, bool dealer, string status) : id(id), kapital(kapital), stawka(stawka), dealer(dealer), status(status) {
    this->karty[0] = karty[0];
    this->karty[1] = karty[1];
}
int Gracz::Podbij_stawke(int max_stawka) {
    return 0;
}
int Gracz::Pasuj() {
    return 0;
}
int Gracz::Check(int max_stawka) {
    return 0;
}
int Gracz::Ruch_Czlowieka(int max_stawka) {
    return 0;
}
int Gracz::Ruch_Bota(int max_stawka) {
    return 0;
}