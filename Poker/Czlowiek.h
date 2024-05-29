#pragma once
#include "Gracz.h"
using namespace std;

class Czlowiek :
    public Gracz
{
public:
    Czlowiek(int id, int kapital, string karty[2], int stawka, bool dealer, string status);
};

