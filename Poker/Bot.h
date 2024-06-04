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
        Bot(int id, int kapital, string karty[2], int stawka, bool dealer, string status, int poziom_trudnosci);
       
    private:
        int poziom_trudnosci;
        int Podbij_stawke(int max_stawka) override;
        int Check(int max_stawka) override;
        int Ruch_Bota(int max_stawka, vector<string> aktualny_stol) override;
        int Straightpoints(vector<string> karty);
        int Flushpoints(vector<string> karty);
        int Pairs(vector<string> karty);
        int losujLiczbe(int min, int max, unsigned int seed);
        map<string, int> cardRankValues = {
            {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5},
            {"6", 6}, {"7", 7}, {"8", 8}, {"9", 9},
            {"10", 10}, {"Walet", 11}, {"Dama", 12}, {"Król", 13}, {"As", 14}
        };
};

