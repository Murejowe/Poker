#pragma once
#include "Gracz.h"
#include "Gra.h"
using namespace std;

class Czlowiek :
    public Gracz
{
public:
    Czlowiek(int id, int kapital, string karty[2], int stawka, bool dealer, string status);
    int Podbij_stawke(int max_stawka) override;
    int Pasuj() override;
    int Check() override;
    int Ruch_Czlowieka(int max_stawka) override;
};

