#pragma once
#include <vector>
#include <iostream>
#include <random>   
#include <chrono> 
#include <algorithm> 
#include "Gracz.h"
#include "Czlowiek.h"
#include "Bot.h"
using namespace std;

class Gra
{
	protected:
	    vector<string> talia;
	    const vector<string> initial_talia = {
	        "As Karo", "2 Karo", "3 Karo", "4 Karo", "5 Karo", "6 Karo", "7 Karo", "8 Karo", "9 Karo", "10 Karo", "Walet Karo", "Dama Karo", "Król Karo",
	        "As Kier", "2 Kier", "3 Kier", "4 Kier", "5 Kier", "6 Kier", "7 Kier", "8 Kier", "9 Kier", "10 Kier", "Walet Kier", "Dama Kier", "Król Kier",
	        "As Trefl", "2 Trefl", "3 Trefl", "4 Trefl", "5 Trefl", "6 Trefl", "7 Trefl", "8 Trefl", "9 Trefl", "10 Trefl", "Walet Trefl", "Dama Trefl", "Król Trefl",
	        "As Pik", "2 Pik", "3 Pik", "4 Pik", "5 Pik", "6 Pik", "7 Pik", "8 Pik", "9 Pik", "10 Pik", "Walet Pik", "Dama Pik", "Król Pik"
	    };
	public:
	    string stol[5];
	    int pula;
	    void RozdajKarty(vector<Gracz*>& gracze);
	    int SetDealer();
	    void RozpocznijRunde();
	    void OdkryjStol();
	    void WinnerFinder();
	    void ResetTalia();
		void TworzGraczy(int liczba_graczy);
		int sprawdzam(int x);
		Gra();
	private:
};

