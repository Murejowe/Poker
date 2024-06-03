#include "Gra.h"

Gra::Gra() {
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
        cout << "Podaj poziom trudności bota nr." << i + 1 << " (1-3): " << endl;
        cin >> temp;
        while (sprawdzam(temp) == 0) {
            cout << "Wprowadzono niepoprawną wartość! " << endl << "Podaj poziom trudności bota nr." << i + 1 << " (1-3): " << endl;
            cin >> temp;
        }
        list.push_back(temp);
    }
    for (const auto& element : list) {
        cout << element << endl;
    }
    int kapital;
    cout << "Podaj kapitał początkowy każdego gracza (min. 100): " << endl;
    cin >> kapital;
    while (kapital < 100) {
        cout << "Wprowadzono niepoprawną wartość! " << endl << "Podaj kapitał początkowy każdego gracza (min. 100): " << endl;
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
    for (auto& gracz : gracze) {
        cout << gracz->karty[0] << " " << gracz->karty[1] << endl;
    }
    for (int i = 0; i < 5; i++) {
        cout << stol[i] << endl;
    }
    RozpocznijRunde();
}
void Gra::RozpocznijRunde(){
    tempGracze.clear();
    pula = 0;
    for (auto& gracz : gracze) {
        if (gracz->kapital > 0) {
            tempGracze.push_back(gracz);
        }
    }
    /*for (auto& gracz : tempGracze) {
        cout << gracz->karty[0] << " " << gracz->karty[1] << endl;
    }*/
    cout << tempGracze.size() << endl;
    int DealerIndex = SetDealer(numer_rundy);
    RozdajKarty(gracze);
    for (auto& gracz : gracze) {
        // Combine player's cards with community cards (stol)
        vector<string> allCards;
        allCards.push_back(gracz->karty[0]);
        allCards.push_back(gracz->karty[1]);
        allCards.insert(allCards.end(), stol, stol + 5);
        for (auto& karta : allCards) {
            cout << karta << " ";
        }
        cout << endl;
        // Evaluate the poker hand
        PokerHandRank rank = EvaluatePokerHand(allCards);
        cout << "kombinacja gracza o id: " << gracz->id << " jest równa: " << nazwy_kombinacji[rank] << endl;
    }
    for (auto& gracz : tempGracze) {
        gracz->status = "active";
    }
    max_stawka = 0;
    //for (int i = 0; i < 4; i++) {
    //    if (tempGracze.size() == 1) {
    //        cout << "Gratulacje! Wygrałeś" << endl;
    //        return;
    //    }
    //    for (auto& gracz : tempGracze) {
    //        if (gracz->status != "all in") {
    //            gracz->status = "active";
    //        }
    //    }
    //    while (SprawdzajStatus()) {
    //        /*for (auto& gracz : tempGracze) {
    //            gracz->status = "active";
    //        }*/
    //        for (int j = 0; j <= tempGracze.size(); j++) {
    //            int id_gracza = (DealerIndex + j) % tempGracze.size();
    //            if (id_gracza == 0) {
    //                if (tempGracze[id_gracza]->status == "all in") {
    //                    continue;
    //                }
    //                else {
    //                    tempGracze[id_gracza]->status = "active";
    //                    int poprzednia_stawka = tempGracze[id_gracza]->stawka;
    //                    int tempStawka = tempGracze[id_gracza]->Ruch_Czlowieka(max_stawka);
    //                    if (tempStawka > max_stawka) {
    //                        max_stawka = tempStawka;
    //                    }
    //                    pula += tempStawka - poprzednia_stawka;
    //                }  
    //            }
    //            else{
    //                if (tempGracze[id_gracza]->status == "all in") {
    //                    continue;
    //                }
    //                else {
    //                    tempGracze[id_gracza]->status = "active";
    //                    int poprzednia_stawka = tempGracze[id_gracza]->stawka;
    //                    int tempStawka = tempGracze[id_gracza]->Ruch_Bota(max_stawka);
    //                    if (tempStawka > max_stawka) {
    //                        max_stawka = tempStawka;
    //                    }
    //                    pula += tempStawka - poprzednia_stawka;
    //                }
    //            }
    //        }
    //    }
    //    if (i == 0) {
    //        cout << "Karty na stole to: " << stol[0] << ", " << stol[1] << ", " << stol[2] << endl;
    //    }
    //    if (i == 1) {
    //        cout << "Karty na stole to: " << stol[0] << ", " << stol[1] << ", " << stol[2] << ", " << stol[3] << endl;
    //    }
    //    if (i == 2) {
    //        cout << "Karty na stole to: " << stol[0] << ", " << stol[1] << ", " << stol[2] << ", " << stol[3] << ", " << stol[4] << endl;
    //    }
    //    if (i == 3) {
    //        WinnerFinder();
    //        numer_rundy++;
    //        RozpocznijRunde();
    //    }
    //}
};

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
    return DealerIndex;
}

bool Gra::SprawdzajStatus(){
    int temp = 0;
    for (auto& gracz : tempGracze) {
        if (gracz->status == "check" || gracz->status == "pass" || gracz->status == "all in") {
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
    gracze[0]->kapital += pula;
    for (auto& gracz : gracze) {
        gracz->stawka = 0;
    }
}

bool Gra::IsFlush(const vector<string>& cards) {
    // Odczytaj kolor pierwszej karty
    string firstCard = cards[0];
    string suit = firstCard.substr(firstCard.find(' ') + 1);

    // Sprawdź, czy wszystkie pozostałe karty mają ten sam kolor
    for (int i = 1; i < cards.size(); ++i) {
        string currentCard = cards[i];
        string currentSuit = currentCard.substr(currentCard.find(' ') + 1);
        if (currentSuit != suit) {
            return false;
        }
    }
    return true;
}

bool Gra::IsStraight(const vector<string>& cards) {
    // Konwertuj wartości kart na liczby
    vector<int> cardValues;
    for (const auto& card : cards) {
        string value = card.substr(0, card.find(' '));
        if (cardRankValues.find(value) != cardRankValues.end()) {
            cardValues.push_back(cardRankValues[value]);
        }
    }

    // Posortuj karty
    sort(cardValues.begin(), cardValues.end());

    // Sprawdź, czy karty tworzą ciąg wartości
    for (int i = 1; i < cardValues.size(); ++i) {
        if (cardValues[i] != cardValues[i - 1] + 1) {
            return false;
        }
    }
    return true;
}

Gra::PokerHandRank Gra::EvaluatePokerHand(const vector<string>& cards) {
    // Sprawdź, czy wszystkie karty mają ten sam kolor
    bool flush = IsFlush(cards);

    // Sprawdź, czy karty tworzą strita
    bool straight = IsStraight(cards);

    // Wartości kart
    vector<int> cardValues;
    for (const auto& card : cards) {
        string value = card.substr(0, card.find(' '));
        if (cardRankValues.find(value) != cardRankValues.end()) {
            cardValues.push_back(cardRankValues[value]);
        }
    }

    // Posortuj wartości kart
    sort(cardValues.begin(), cardValues.end());

    // Sprawdź, czy występują pary, trójki itp.
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

    // Określ wynik na podstawie kombinacji kart
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