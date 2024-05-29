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
};

