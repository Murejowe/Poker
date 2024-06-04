#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Gracz
{
public:
    int id; // Unikalne ID gracza
    int kapital; // Kwota jak� mozna przeznaczy� do zak�ad�w
    string karty[2]; // Karty w r�ce
    int stawka; // Aktualny zak�ad
    bool dealer; // 1- Gracz jest dealerem 0- Gracz nie jest dealerem
    string status; // Dodatkowy parametr wykorzystywany do obs�ugi rozgrywki
    Gracz(int id, int kapital, string karty[2], int stawka, bool dealer, string status); // Konstruktor obiektu Gracza
    virtual int Podbij_stawke(int max_stawka); // Wirtualna metoda podbijania stawki
    int Pasuj();
    virtual int Check(int max_stawka);
    virtual int Ruch_Czlowieka(int max_stawka);
    virtual int Ruch_Bota(int max_stawka, vector<string> aktualny_stol);
};

