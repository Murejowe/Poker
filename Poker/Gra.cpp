#include "Gra.h"

Gra::Gra() {
    ResetTalia();
    // Initialize card rank values
    cardRankValues = {
        {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6}, {"7", 7}, {"8", 8}, {"9", 9},
        {"10", 10}, {"Walet", 11}, {"Dama", 12}, {"KrÛl", 13}, {"As", 14}
    };
}

void Gra::ResetTalia() {
    talia = initial_talia;
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(talia.begin(), talia.end(), default_random_engine(seed));
}

void Gra::RozdajKarty(vector<Gracz*>& gracze) {
    ResetTalia();
    for (auto& gracz : gracze) {
        gracz->karty[0] = talia.back(); talia.pop_back();
        gracz->karty[1] = talia.back(); talia.pop_back();
    }
    for (int i = 0; i < 5; i++) {
        stol[i] = talia.back();
        talia.pop_back();
    }
}
void Gra::TworzGraczy(int liczba_graczy) {
    int temp;
    vector<int> list;
    string placeholder[2] = { "", "" };
    for (int i = 0; i < liczba_graczy; i++) {
        cout << "Podaj poziom trudnoúci bota nr." << i + 1 << " (1-3): " << endl;
        cin >> temp;
        while (sprawdzam(temp) == 0) {
            cout << "Wprowadzono niepoprawnπ wartoúÊ! " << endl << "Podaj poziom trudnoúci bota nr." << i + 1 << " (1-3): " << endl;
            cin >> temp;
        }
        list.push_back(temp);
    }
    for (const auto& element : list) {
        cout << element << endl;
    }
    int kapital;
    cout << "Podaj kapita≥ poczπtkowy kaødego gracza (min. 100): " << endl;
    cin >> kapital;
    while (kapital < 100) {
        cout << "Wprowadzono niepoprawnπ wartoúÊ! " << endl << "Podaj kapita≥ poczπtkowy kaødego gracza (min. 100): " << endl;
        cin >> kapital;
    }
    vector<Bot> listabotow;
    Czlowiek czlowiek(0, kapital, placeholder, 0, 0, "");
    gracze.push_back(&czlowiek);
    for (int i = 0; i < liczba_graczy; i++) {
        Bot bot(i + 1, kapital, placeholder, 0, 0, "status", list[i]);
        listabotow.push_back(bot);
    }

    for (auto& bot : listabotow) {
        gracze.push_back(&bot);
    }
    RozdajKarty(gracze);
    cout << "Czlowiek Karty: " << czlowiek.karty[0] << " i " << czlowiek.karty[1] << endl;
    for (const auto& bot : listabotow) {
        cout << "Bot ID: " << bot.id << endl;
        cout << "Kapital: " << bot.kapital << endl;
        cout << "Karty: " << bot.karty[0] << " i " << bot.karty[1] << endl;
        cout << "Stawka: " << bot.stawka << endl;
        cout << "Dealer: " << bot.dealer << endl;
        cout << "Status: " << bot.status << endl;
        cout << "Poziom Trudnosci: " << bot.poziom_trudnosci << endl << endl;
    }
    for (auto& gracz : gracze) {
        cout << gracz->karty[0] << " " << gracz->karty[1] << endl;
    }
    for (int i = 0; i < 5; i++) {
        cout << stol[i] << endl;
    }
    RozpocznijRunde();
}
void Gra::RozpocznijRunde() {
    tempGracze.clear();  // Ensure tempGracze is empty before starting

    for (auto& gracz : gracze) {
        if (gracz->kapital != 0) {
            tempGracze.push_back(gracz);
        }
    }

    cout << "Liczba graczy: " << tempGracze.size() << endl;

    if (tempGracze.size() == 1) {
        cout << "Gratulacje! Wygra≥eú" << endl;
        return;
    }

    int DealerIndex = SetDealer(numer_rundy);

    for (auto& gracz : tempGracze) {
        gracz->status = "active"; 
    }

    for (int i = 0; i < 3; i++) {
        max_stawka = 0;

        while (SprawdzajStatus()) {
            for (int j = 0; j < tempGracze.size(); j++) {
                int id_gracza = (DealerIndex + j) % tempGracze.size();

                if (id_gracza == 0) {
                    int tempStawka = tempGracze[id_gracza]->Ruch_Czlowieka(max_stawka);
                    
                    // Deal new cards after the human player makes their move
                    RozdajKarty(tempGracze);

                    // Display the new cards for the human player
                    cout << "Twoje nowe karty: " << tempGracze[id_gracza]->karty[0] << " i " << tempGracze[id_gracza]->karty[1] << endl;
                    
                    if (tempStawka > max_stawka) {
                        max_stawka = tempStawka;
                    }
                } else {
                    int tempStawka = tempGracze[id_gracza]->Ruch_Bota(max_stawka);
                    if (tempStawka > max_stawka) {
                        max_stawka = tempStawka;
                    }
                }
            }
        }

        if (i == 0) {
            cout << "Karty na stole to: " << stol[0] << ", " << stol[1] << ", " << stol[2] << endl;
        }
        if (i == 1) {
            cout << "Karty na stole to: " << stol[0] << ", " << stol[1] << ", " << stol[2] << ", " << stol[3] << endl;
        }
        if (i == 2) {
            cout << "Karty na stole to: " << stol[0] << ", " << stol[1] << ", " << stol[2] << ", " << stol[3] << ", " << stol[4] << endl;
        }
    }

    WinnerFinder();
}







int Gra::SetDealer(int y) {
    int DealerIndex = (y - 1) % (tempGracze.size());
    for (auto& gracz : tempGracze) {
        if (gracz->id == DealerIndex) {
            gracz->dealer = 1;
        }
        else {
            gracz->dealer = 0;
        }
    }
    numer_rundy =+ 1;
    return DealerIndex;
}

bool Gra::SprawdzajStatus(){
    int temp = 0;
    for (auto& gracz : tempGracze) {
        if (gracz->status == "check" || gracz->status == "pass") {
            temp++;
        }
    }
    if (temp == tempGracze.size()) {
        return false;
    }
    else {
        return true;
    }
}

void Gra::WinnerFinder() {
    Gracz* winner = nullptr;
    PokerHandRank winnerRank = HIGH_CARD;

    for (auto& gracz : gracze) {
        // Combine player's cards with community cards (stol)
        vector<string> allCards;
        allCards.push_back(gracz->karty[0]);
        allCards.push_back(gracz->karty[1]);
        allCards.insert(allCards.end(), stol, stol + 5);

        // Evaluate the poker hand
        PokerHandRank rank = EvaluatePokerHand(allCards);

        // Update the winner if the current player's hand outranks the previous winner
        if (rank > winnerRank) {
            winner = gracz;
            winnerRank = rank;
        }
    }

    // Print the winner
    if (winner != nullptr) {
        cout << "Zwyciezca rundy to: " << winner->id << endl;
        cout << "Ranking pokerowy: " << winnerRank << endl;
    }
}
bool Gra::IsFlush(const vector<string>& cards) {
    char suit = cards[0][cards[0].find_last_of(' ') + 1]; // Odczytaj kolor pierwszej karty

    // Sprawdü, czy wszystkie pozosta≥e karty majπ ten sam kolor
    for (int i = 1; i < cards.size(); ++i) {
        if (cards[i][cards[i].find_last_of(' ') + 1] != suit) {
            return false;
        }
    }
    return true;
}

bool Gra::IsStraight(const vector<string>& cards) {
    // Konwertuj wartoúci kart na liczby
    vector<int> cardValues;
    for (const auto& card : cards) {
        string value = card.substr(0, card.find(' '));
        if (cardRankValues.find(value) != cardRankValues.end()) {
            cardValues.push_back(cardRankValues[value]);
        }
    }

    // Posortuj karty
    sort(cardValues.begin(), cardValues.end());

    // Sprawdü, czy karty tworzπ ciπg wartoúci
    for (int i = 1; i < cardValues.size(); ++i) {
        if (cardValues[i] != cardValues[i - 1] + 1) {
            return false;
        }
    }
    return true;
}

Gra::PokerHandRank Gra::EvaluatePokerHand(const vector<string>& cards) {
    // Sprawdü, czy wszystkie karty majπ ten sam kolor
    bool flush = IsFlush(cards);

    // Sprawdü, czy karty tworzπ strita
    bool straight = IsStraight(cards);

    // Wartoúci kart
    vector<int> cardValues;
    for (const auto& card : cards) {
        string value = card.substr(0, card.find(' '));
        if (cardRankValues.find(value) != cardRankValues.end()) {
            cardValues.push_back(cardRankValues[value]);
        }
    }

    // Posortuj wartoúci kart
    sort(cardValues.begin(), cardValues.end());

    // Sprawdü, czy wystÍpujπ pary, trÛjki itp.
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

    // Okreúl wynik na podstawie kombinacji kart
    if (straight && flush) {
        return STRAIGHT_FLUSH;
    }
    else if (fourOfAKind > 0) {
        return FOUR_OF_A_KIND;
    }
    else if (threeOfAKind > 0 && pairCount > 0) {
        return FULL_HOUSE;
    }
    else if (flush) {
        return FLUSH;
    }
    else if (straight) {
        return STRAIGHT;
    }
    else if (threeOfAKind > 0) {
        return THREE_OF_A_KIND;
    }
    else if (pairCount >= 2) {
        return TWO_PAIR;
    }
    else if (pairCount == 1) {
        return ONE_PAIR;
    }
    else {
        return HIGH_CARD;
    }
}



