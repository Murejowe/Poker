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

int sprawdzam(int x);

class Gra
{
	public:
		vector<string> aktualny_stol;
	    int pula;
		void TworzGraczy(int liczba_graczy);
		int numer_rundy = 1;
		int max_stawka = 0;
		Gra();
	private:
		bool SprawdzajStatus();
		void RozdajKarty(vector<Gracz*>& gracze);
		int SetDealer(int numer_rundy);
		void RozpocznijRunde();
		void WinnerFinder();
		void ResetTalia();
		string stol[5];
		const vector<string> initial_talia = {
			"As Karo", "2 Karo", "3 Karo", "4 Karo", "5 Karo", "6 Karo", "7 Karo", "8 Karo", "9 Karo", "10 Karo", "Walet Karo", "Dama Karo", "Król Karo",
			"As Kier", "2 Kier", "3 Kier", "4 Kier", "5 Kier", "6 Kier", "7 Kier", "8 Kier", "9 Kier", "10 Kier", "Walet Kier", "Dama Kier", "Król Kier",
			"As Trefl", "2 Trefl", "3 Trefl", "4 Trefl", "5 Trefl", "6 Trefl", "7 Trefl", "8 Trefl", "9 Trefl", "10 Trefl", "Walet Trefl", "Dama Trefl", "Król Trefl",
			"As Pik", "2 Pik", "3 Pik", "4 Pik", "5 Pik", "6 Pik", "7 Pik", "8 Pik", "9 Pik", "10 Pik", "Walet Pik", "Dama Pik", "Król Pik"
		};
		vector<string> talia;
		vector<Gracz*> gracze;
		vector<Gracz*> tempGracze;
		vector<Gracz*> kandydaci;
		vector<string> allCards;
		vector<Gracz*> lista_winnerów;
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
		vector<string> nazwy_kombinacji = { "Wysoka karta", "Jedna para", "Dwie pary", "Trójka", "Strit", "Kolor", "Ful", "Czwórka", "Poker" };
		map<string, int> cardRankValues = {
		{"2", 2}, {"3", 3}, {"4", 4}, {"5", 5},
		{"6", 6}, {"7", 7}, {"8", 8}, {"9", 9},
		{"10", 10}, {"Walet", 11}, {"Dama", 12}, {"Król", 13}, {"As", 14}
		};

		// Define a function to check if all cards have the same suit
		bool IsFlush(const vector<string>& cards);

		// Define a function to check if cards form a straight
		bool IsStraight(const vector<string>& cards);

		int maxFlush(const vector<string>& cards);

		int maxStraight(const vector<string>& cards);

		// Define a function to evaluate the poker hand
		PokerHandRank EvaluatePokerHand(const vector<string>& cards);
		vector<Gracz*> DrawResolver(vector<Gracz*>& gracze);
};

