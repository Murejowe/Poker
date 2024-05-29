#pragma once
#include "Gracz.h"
#include "Gra.h"
using namespace std;

class Czlowiek :
    public Gracz
{
public:
    Czlowiek(int id, int kapital, string karty[2], int stawka, bool dealer, string status);
    int Podbij_stawke() override;
    void Pasuj() override;
    void Check() override;
    void Ruch_Czlowieka();
};

