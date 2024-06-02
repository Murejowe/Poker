#pragma once
#include <iostream>
#include "Gracz.h"
using namespace std;

class Bot :
    public Gracz
{
    public:
    int poziom_trudnosci;
    Bot(int id, int kapital, string karty[2], int stawka, bool dealer, string status, int poziom_trudnosci);
    int Podbij_stawke(int max_stawka) override;
    int Pasuj() override;
    int Check(int max_stawka) override;
    int Ruch_Bota(int max_stawka) override;
};

