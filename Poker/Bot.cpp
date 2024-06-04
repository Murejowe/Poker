#include "Bot.h"
Bot::Bot(int id, int kapital, string karty[2], int stawka, bool dealer, string status, int poziom_trudnosci) : Gracz(id, kapital, karty, stawka, dealer, status), poziom_trudnosci(poziom_trudnosci) {}
int Bot::Podbij_stawke(int max_stawka) {
	stawka += ceil((kapital*0.2) * poziom_trudnosci);
	kapital -= stawka;
	if (kapital == 0) {
		status = "all in";
	}
	cout << "Bot " << id <<" Podbija stawkÍ do: " << stawka << endl;
	return stawka;
}
int Bot::Check(int max_stawka) {
	if (max_stawka > stawka) {
		if (max_stawka - stawka >= kapital) {
			stawka += kapital;
			kapital = 0;
			status = "all in";
			cout << "Bot " << id << " Check All in!" << endl;
			return stawka;
		}
		else {
			kapital -= max_stawka - stawka;
			stawka = max_stawka;
			cout << "Bot " << id <<" Check" << endl;
			status = "check";
			return stawka;
		}
	}
	else {
		cout << "Bot " << id <<" Check" << endl;
		status = "check";
		return stawka;
	}
}
int Bot::Ruch_Bota(int max_stawka, vector<string> aktualny_stol) {
	if (aktualny_stol.size() == 0) {
		if (max_stawka == 0) {
			return Podbij_stawke(max_stawka);
		}
		else {
			return Check(max_stawka);
		}
	}
	else {
		vector<string> allCards;
		allCards.clear();
		allCards.push_back(karty[0]);
		allCards.push_back(karty[1]);
		for (auto& stol : aktualny_stol) {
			allCards.push_back(stol);
		}
		int StraightAggresion = Straightpoints(allCards);
		int FlushAggresion = Flushpoints(allCards);
		int PairsAggresion = Pairs(allCards);
		if ((FlushAggresion >= aktualny_stol.size()-2 && FlushAggresion > 2) || (StraightAggresion >= aktualny_stol.size() - 2 && StraightAggresion > 2)) {
			int bigger;
			if (FlushAggresion >= StraightAggresion) {
				bigger = FlushAggresion;
			}
			else {
				bigger = StraightAggresion;
			}
			unsigned seed = chrono::system_clock::now().time_since_epoch().count() + bigger;
			int losowa = losujLiczbe(1, 10, seed);
			if (losowa < bigger) {
				Check(max_stawka);
			}
			else {
				if (ceil((kapital * 0.2) * poziom_trudnosci) >= kapital) {
					stawka = kapital;
					kapital -= stawka;
					status = "all in";
					cout << "Bot " << id << " Check All in!" << endl;
					return stawka;
				}
				if (max_stawka == ceil((kapital * 0.2) * poziom_trudnosci)) {
					Check(max_stawka);
				}
				else {
					stawka += ceil((kapital * 0.2) * poziom_trudnosci);
					kapital -= stawka;
					status = "check";
					cout << "Bot " << id << " Podbija stawkÍ do: " << stawka << endl;
					return stawka;
				}
			}
		}
		else if (PairsAggresion > 0) {
			unsigned seed = chrono::system_clock::now().time_since_epoch().count()+PairsAggresion;
			int losowa = losujLiczbe(1, 10, seed);
			if (losowa > PairsAggresion) {
				Check(max_stawka);
			}
			else {
				if (ceil((kapital * 0.2) * poziom_trudnosci) >= kapital) {
					stawka = kapital;
					kapital -= stawka;
					status = "all in";
					cout << "Bot " << id << " Check All in!" << endl;
					return stawka;
				}
				if (max_stawka == ceil((kapital * 0.2) * poziom_trudnosci)) {
					Check(max_stawka);
				}
				else {
					stawka += ceil((kapital * 0.2) * poziom_trudnosci);
					kapital -= stawka;
					status = "check";
					cout << "Bot " << id << " Podbija stawkÍ do: " << stawka << endl;
					return stawka;
				}
			}
		}
		else {
			unsigned seed = chrono::system_clock::now().time_since_epoch().count();
			int losowa = losujLiczbe(1, 10, seed);
			if (losowa > 5) {
				Pasuj();
			}
			else{
				Check(max_stawka);
			}
		}
	}
}

int Bot::Straightpoints(vector<string> karty) {
	vector<int> cardValues;
	for (const auto& card : karty) {
		string value = card.substr(0, card.find(' '));
		cardValues.push_back(cardRankValues[value]);
	}

	sort(cardValues.begin(), cardValues.end());

	int strit_licznik = 1;
	int max_licznik = 1;
	for (int i = 0; i < cardValues.size() - 1; i++) {
		if (cardValues[i] + 1 == cardValues[i + 1]) {
			strit_licznik++;
		}
		if (cardValues[i] == cardValues[i + 1]) {
			continue;
		}
		else {
			if (strit_licznik > max_licznik) {
				max_licznik = strit_licznik;
			}
			strit_licznik = 1;
		}
	}
	return max_licznik;
}
int Bot::Flushpoints(vector<string> karty) {
	string kolor[4] = { "Kier","Karo","Trefl", "Pik" };
	int max_licznik = 1;
	// Sprawdü, czy wszystkie pozosta≥e karty majπ ten sam kolor
	for (int j = 0; j < 4; j++) {
		int kolor_licznik = 0;
		for (int i = 0; i < karty.size(); i++) {
			if (karty[i].substr(karty[i].find(' ') + 1) == kolor[j]) {
				kolor_licznik++;
			}
		}
		if (kolor_licznik > max_licznik) {
			max_licznik = kolor_licznik;
		}
		
	}
	return max_licznik;
}
int Bot::Pairs(vector<string> karty) {
	vector<int> cardValues;
	for (const auto& card : karty) {
		string value = card.substr(0, card.find(' '));
		if (cardRankValues.find(value) != cardRankValues.end()) {
			cardValues.push_back(cardRankValues[value]);
		}
	}

	sort(cardValues.begin(), cardValues.end());

	map<int, int> valueCount;
	for (int value : cardValues) {
		valueCount[value]++;
	}

	int pairCount = 0;
	int threeOfAKind = 0;
	int fourOfAKind = 0;

	for (const auto& pair : valueCount) {
		if (pair.second == 2) {
			pairCount++;
		}
		else if (pair.second == 3) {
			threeOfAKind++;
		}
		else if (pair.second == 4) {
			fourOfAKind++;
		}
	}
	if (pairCount == 1 && threeOfAKind == 0 && fourOfAKind == 0) {
		return 1;
	}
	if (pairCount == 2 && threeOfAKind == 0 && fourOfAKind == 0) {
		return 3;
	}
	if (pairCount == 0 && threeOfAKind == 1 && fourOfAKind == 0) {
		return 5;
	}
	if (pairCount == 1 && threeOfAKind == 1 && fourOfAKind == 0) {
		return 7;
	}
	if (pairCount == 0 && threeOfAKind == 0 && fourOfAKind == 1) {
		return 9;
	}
}

int Bot::losujLiczbe(int min, int max, unsigned int seed) {
	mt19937 gen(seed);
	uniform_int_distribution<> distr(min, max);
	return distr(gen);
}