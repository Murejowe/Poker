#pragma once
#include <map>
#include <vector>
#include <iostream>
#include <random>   
#include <chrono> 
#include <algorithm> 
#include "Gracz.h"
#include "Czlowiek.h"
#include "Bot.h"

using namespace std;

int sprawdzam(int x);

class Gra
{
protected:
    vector<string> talia;
    const vector<string> initial_talia = {
        "As Karo", "2 Karo", "3 Karo", "4 Karo", "5 Karo", "6 Karo", "7 Karo", "8 Karo", "9 Karo", "10 Karo", "Walet Karo", "Dama Karo", "Kr�l Karo",
        "As Kier", "2 Kier", "3 Kier", "4 Kier", "5 Kier", "6 Kier", "7 Kier", "8 Kier", "9 Kier", "10 Kier", "Walet Kier", "Dama Kier", "Kr�l Kier",
        "As Trefl", "2 Trefl", "3 Trefl", "4 Trefl", "5 Trefl", "6 Trefl", "7 Trefl", "8 Trefl", "9 Trefl", "10 Trefl", "Walet Trefl", "Dama Trefl", "Kr�l Trefl",
        "As Pik", "2 Pik", "3 Pik", "4 Pik", "5 Pik", "6 Pik", "7 Pik", "8 Pik", "9 Pik", "10 Pik", "Walet Pik", "Dama Pik", "Kr�l Pik"
    };

public:
    string stol[5];
    int pula;
    void RozdajKarty(vector<Gracz*>& gracze);
    int SetDealer(int numer_rundy);
    void RozpocznijRunde();
    void OdkryjStol();
    void WinnerFinder();
    void ResetTalia();
    void TworzGraczy(int liczba_graczy);
    bool SprawdzajStatus();
    int numer_rundy = 1;
    int max_stawka = 0;
    Gra();

private:
    vector<Gracz*> gracze;
    vector<Gracz*> tempGracze;

    // Define ranks for poker hands
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

    // Define a map to convert card ranks to numeric values for comparison
    map<string, int> cardRankValues;

    // Define a function to check if all cards have the same suit
    bool IsFlush(const vector<string>& cards);

    // Define a function to check if cards form a straight
    bool IsStraight(const vector<string>& cards);

    // Define a function to evaluate the poker hand
    PokerHandRank EvaluatePokerHand(const vector<string>& cards);
};


