#pragma once
#include "Gracz.h"
#include "Gra.h"
using namespace std;

class Czlowiek :
    public Gracz
{
    public:
        // Konstruktor klasy Czlowiek
        Czlowiek(int id, int kapital, string karty[2], int stawka, bool dealer, string status);
    private:
        // Metoda do podbijania stawki przez gracza cz³owieka
        int Podbij_stawke(int max_stawka) override;
        // Metoda do sprawdzania przez gracza cz³owieka
        int Check(int max_stawka) override;
        // Metoda do wykonania ruchu przez gracza cz³owieka
        int Ruch_Czlowieka(int max_stawka) override;
};

