#include "Gracz.h"
Gracz::Gracz(int id, int kapital, string karty[2], int stawka, bool dealer, string status) : id(id), kapital(kapital), stawka(stawka), dealer(dealer), status(status) {
    this->karty[0] = karty[0];
    this->karty[1] = karty[1];
}
int Gracz::Podbij_stawke() {
    return 0;
}
void Gracz::Pasuj() {}
void Gracz::Check() {}