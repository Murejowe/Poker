#pragma once
#include <iostream>
using namespace std;

class Gracz
{
public:
    int id;
    int kapital;
    string karty[2];
    int stawka;
    bool dealer;
    string status;
    Gracz(int id, int kapital, string karty[2], int stawka, bool dealer, string status);
    virtual int Podbij_stawke(int max_stawka);
    virtual int Pasuj();
    virtual int Check(int max_stawka);
    virtual int Ruch_Czlowieka(int max_stawka);
    virtual int Ruch_Bota(int max_stawka);
};

