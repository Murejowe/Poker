#pragma once
#include <iostream>
#include <map>
#include <cmath>
#include <chrono>
#include <random>
#include <algorithm>
#include "Gracz.h"
using namespace std;

class Bot :
    public Gracz
{
    
public:
    // Konstruktor klasy Bot
    Bot(int id, int kapital, string karty[2], int stawka, bool dealer, string status, int poziom_trudnosci);

private:
    // Poziom trudnoœci bota
    // Okreœla, jakie decyzje podejmowaæ bêdzie bot
    int poziom_trudnosci;

    // Metoda do podbijania stawki przez bota
    // Okreœla, jak¹ stawkê podbiæ w zale¿noœci od poziomu trudnoœci i aktualnego stanu gry
    int Podbij_stawke(int max_stawka) override;

    // Metoda do sprawdzania przez bota
    // Okreœla, czy bot podejmuje decyzjê o sprawdzeniu karty lub nie
    int Check(int max_stawka) override;

    // Metoda do wykonania ruchu przez bota
    // Okreœla, jaki ruch wykona bot w zale¿noœci od poziomu trudnoœci i aktualnego stanu gry
    int Ruch_Bota(int max_stawka, vector<string> aktualny_stol) override;

    // Funkcja obliczaj¹ca punkty za ci¹g kart
    int Straightpoints(vector<string> karty);

    // Funkcja obliczaj¹ca punkty za kolor kart
    int Flushpoints(vector<string> karty);

    // Funkcja obliczaj¹ca punkty za pary kart
    int Pairs(vector<string> karty);

    // Funkcja losuj¹ca liczbê miêdzy min a max z danym seedem
    int losujLiczbe(int min, int max, unsigned int seed);

    // Mapa przechowuj¹ca wartoœci kart (np. 2: 2, 3: 3, itp.)
    map<string, int> cardRankValues = {
        {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5},
        {"6", 6}, {"7", 7}, {"8", 8}, {"9", 9},
        {"10", 10}, {"Walet", 11}, {"Dama", 12}, {"Król", 13}, {"As", 14}
    };
};
