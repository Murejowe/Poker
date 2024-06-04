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

// Funkcja wspomagaj¹ca wprowadzanie poprawnych danych
int sprawdzam(int x);

class Gra
{
public:
    // Wektor przechowuj¹cy odkryte karty na stole
    vector<string> aktualny_stol;

    // Pula pieniêdzy do wygrania
    int pula;

    // Funkcja tworz¹ca graczy
    void TworzGraczy(int liczba_graczy);

    // Numer rundy
    int numer_rundy = 1;

    // Maksymalna stawka na rundê
    int max_stawka = 0;

    // Konstruktor klasy gry
    Gra();

private:
    // Funkcja sprawdzaj¹ca statusy graczy
    bool SprawdzajStatus();

    // Funkcja rozdaj¹c¹ karty graczom i sto³owi
    void RozdajKarty(vector<Gracz*>& gracze);

    // Funkcja ustawiaj¹ca dealera na rundê
    int SetDealer(int numer_rundy);

    // Funkcja rozpoczynaj¹ca now¹ rundê
    void RozpocznijRunde();

    // Funkcja znalezienia zwyciêzców
    void WinnerFinder();

    // Funkcja resetuj¹ca talie
    void ResetTalia();

    // Tablica przechowuj¹ca wszystkie karty na stole
    string stol[5];

    // pocz¹tkowa talia kart (wstêpnie przypisane)
    const vector<string> initial_talia = {
        "As Karo", "2 Karo", "3 Karo", "4 Karo", "5 Karo", "6 Karo", "7 Karo", "8 Karo", "9 Karo", "10 Karo", "Walet Karo", "Dama Karo", "Krl Karo",
        "As Kier", "2 Kier", "3 Kier", "4 Kier", "5 Kier", "6 Kier", "7 Kier", "8 Kier", "9 Kier", "10 Kier", "Walet Kier", "Dama Kier", "Krl Kier",
        "As Trefl", "2 Trefl", "3 Trefl", "4 Trefl", "5 Trefl", "6 Trefl", "7 Trefl", "8 Trefl", "9 Trefl", "10 Trefl", "Walet Trefl", "Dama Trefl", "Krl Trefl",
        "As Pik", "2 Pik", "3 Pik", "4 Pik", "5 Pik", "6 Pik", "7 Pik", "8 Pik", "9 Pik", "10 Pik", "Walet Pik", "Dama Pik", "Krl Pik"
    };

    // Wektor przechowuj¹cy potasowan¹ taliê
    vector<string> talia;

    // Wektor przechowuj¹cy graczy
    vector<Gracz*> gracze;

    // Wektor tymczasowy przechowuj¹cy graczy podczas operacji gry
    vector<Gracz*> tempGracze;

    // Wektor przechowuj¹cy graczy, którzy mog¹ by zwyciêzcami
    vector<Gracz*> kandydaci;

    // Wektor przechowuj¹cy karty z rêki gracza i karty na stole
    vector<string> allCards;

    // Wektor przechowuj¹cy zwyciêzców gry
    vector<Gracz*> lista_winnerow;

    // Enum dla rankingów r¹k w pokerze (np. HIGH_CARD, STRAIGHT_FLUSH)
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

    // Wektor przechowuj¹cy nazwy kombinacji r¹k w pokerze (np. Wysoka karta, Ful, itp.)
    vector<string> nazwy_kombinacji = { "Wysoka karta", "Jedna para", "Dwie pary", "Trójka", "Strit", "Kolor", "Ful", "Czwórka", "Poker" };

    // Mapa przechowuj¹ca wartoœci kart (np. As: 14, Walet: 11, itp.)
    map<string, int> cardRankValues = {
        {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5},
        {"6", 6}, {"7", 7}, {"8", 8}, {"9", 9},
        {"10", 10}, {"Walet", 11}, {"Dama", 12}, {"Król", 13}, {"As", 14}
    };

    // Funkcja sprawdzaj¹ca, czy gracz ma kombinacjê Kolor (prawda, jeœli tak)
    bool IsFlush(const vector<string>& cards);

    // Funkcja sprawdzaj¹ca, czy gracz ma kombinacje Strit (prawda, jeœli tworz¹)
    bool IsStraight(const vector<string>& cards);

    // Funkcja znajduj¹ca maksymalny flush w zestawie kart
    int maxFlush(const vector<string>& cards);

    // Funkcja znajduj¹ca maksymalny straight w zestawie kart
    int maxStraight(const vector<string>& cards);

    // Funkcja oceniaj¹ca rêkê w pokerze (zwraca enum value PokerHandRank)
    PokerHandRank EvaluatePokerHand(const vector<string>& cards);

    // Funkcja rozwi¹zywaj¹ca remisy (kiedy dwóch graczy ma tê sam¹ rêkê)
    vector<Gracz*> DrawResolver(vector<Gracz*>& gracze);
};
