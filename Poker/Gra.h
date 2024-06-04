#pragma once
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <random>   
#include <chrono> 
#include <algorithm> 
#include "Gracz.h"
#include "Czlowiek.h"
#include "Bot.h"
using namespace std;

// Funkcja sprawdzaj�ca, czy gracz wygra�
int sprawdzam(int x);

class Gra
{
public:
    // Wektor przechowuj�cy karty na stole
    // Ka�da karta jest reprezentowana jako string (np. "As Karo")
    vector<string> aktualny_stol;

    // Stawka pieni�dzy
    int pula;

    // Funkcja tworz�ca graczy
    void TworzGraczy(int liczba_graczy);

    // Numer rundy
    int numer_rundy = 1;

    // Maksymalna stawka na rund�
    int max_stawka = 0;

    // Konstruktor klasy gry
    Gra();

private:
    // Funkcja sprawdzaj�ca, czy gra si� sko�czy�a
    bool SprawdzajStatus();

    // Funkcja rozdaj�c� karty graczom
    void RozdajKarty(vector<Gracz*>& gracze);

    // Funkcja ustawiaj�ca dealera na rund�
    int SetDealer(int numer_rundy);

    // Funkcja rozpoczynaj�ca now� rund�
    void RozpocznijRunde();

    // Funkcja znalezienia zwyci�zc�w
    void WinnerFinder();

    // Funkcja resetuj�ca talie
    void ResetTalia();

    // Tablica 2D przechowuj�ca karty na stole
    string stol[5];

    // pocz�tkowa talia kart (wst�pnie przypisane)
    const vector<string> initial_talia = {
        "As Karo", "2 Karo", "3 Karo", "4 Karo", "5 Karo", "6 Karo", "7 Karo", "8 Karo", "9 Karo", "10 Karo", "Walet Karo", "Dama Karo", "Krl Karo",
        "As Kier", "2 Kier", "3 Kier", "4 Kier", "5 Kier", "6 Kier", "7 Kier", "8 Kier", "9 Kier", "10 Kier", "Walet Kier", "Dama Kier", "Krl Kier",
        "As Trefl", "2 Trefl", "3 Trefl", "4 Trefl", "5 Trefl", "6 Trefl", "7 Trefl", "8 Trefl", "9 Trefl", "10 Trefl", "Walet Trefl", "Dama Trefl", "Krl Trefl",
        "As Pik", "2 Pik", "3 Pik", "4 Pik", "5 Pik", "6 Pik", "7 Pik", "8 Pik", "9 Pik", "10 Pik", "Walet Pik", "Dama Pik", "Krl Pik"
    };

    // Wektor przechowuj�cy bie��c� tali� kart
    vector<string> talia;

    // Wektor przechowuj�cy graczy
    vector<Gracz*> gracze;

    // Wektor tymczasowy przechowuj�cy graczy podczas operacji gry
    vector<Gracz*> tempGracze;

    // Wektor przechowuj�cy graczy, kt�rzy wygrali gr�
    vector<Gracz*> kandydaci;

    // Wektor przechowuj�cy wszystkie karty w grze
    vector<string> allCards;

    // Wektor przechowuj�cy zwyci�zc�w gry
    vector<Gracz*> lista_winnerw;

    // Enum dla ranking�w r�k w pokerze (np. HIGH_CARD, STRAIGHT_FLUSH)
    enum PokerHandRank {
        HIGH_CARD,
        ONE_PAIR,
        TWO_PAIR,
        THREE_OF_A_KIND,
        STRAIGHT,
        FLUSH,
        FULL_HOUSE,
        FOUR_OF_A_KIND,
        STRAIGHT_FLUSH
    };

    // Wektor przechowuj�cy nazwy kombinacji r�k w pokerze (np. Wysoka karta, Ful, itp.)
    vector<string> nazwy_kombinacji = { "Wysoka karta", "Jedna para", "Dwie pary", "Tr�jka", "Strit", "Kolor", "Ful", "Czw�rka", "Poker" };

    // Mapa przechowuj�ca warto�ci kart (np. As: 14, Walet: 11, itp.)
    map<string, int> cardRankValues = {
        {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5},
        {"6", 6}, {"7", 7}, {"8", 8}, {"9", 9},
        {"10", 10}, {"Walet", 11}, {"Dama", 12}, {"Kr�l", 13}, {"As", 14}
    };

    // Funkcja sprawdzaj�ca, czy wszystkie karty maj� t� sam� barw� (prawda, je�li tak)
    bool IsFlush(const vector<string>& cards);

    // Funkcja sprawdzaj�ca, czy karty tworz� ci�g (prawda, je�li tworz�)
    bool IsStraight(const vector<string>& cards);

    // Funkcja znajduj�ca maksymalny flush w zestawie kart
    int maxFlush(const vector<string>& cards);

    // Funkcja znajduj�ca maksymalny straight w zestawie kart
    int maxStraight(const vector<string>& cards);

    // Funkcja oceniaj�ca r�k� w pokerze (zwraca enum value PokerHandRank)
    PokerHandRank EvaluatePokerHand(const vector<string>& cards);

    // Funkcja rozwi�zywaj�ca narysowania (kiedy dw�ch graczy ma t� sam� r�k�)
    vector<Gracz*> DrawResolver(vector<Gracz*>& gracze);
};
