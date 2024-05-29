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
};

