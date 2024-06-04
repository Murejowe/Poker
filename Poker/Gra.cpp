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
    RozpocznijRunde();
}
void Gra::RozpocznijRunde(){
    aktualny_stol.clear();
    tempGracze.clear();
    pula = 0;
    for (auto& gracz : gracze) {
        if (gracz->kapital > 0) {
            tempGracze.push_back(gracz);
        }
    }
    if (tempGracze[0]->id != 0) {
        cout << "Przegrałeś! Game Over!" << endl;
        return;
    }
    if (tempGracze.size() == 1) {
        cout << "Gratulacje! Wygrałeś" << endl;
        return;
    }
    cout << "Runda numer: " << numer_rundy <<endl;
    int DealerIndex = SetDealer(numer_rundy);
    RozdajKarty(tempGracze);
    for (auto& gracz : tempGracze) {
        gracz->status = "active";
    }
    max_stawka = 0;
    for (int i = 0; i < 4; i++) {
        for (auto& gracz : tempGracze) {
            if (gracz->status == "check") {
                gracz->status = "active";
            }
        }
        while (SprawdzajStatus()) {
            for (int j = 0; j <= tempGracze.size(); j++) {
                int id_gracza = (DealerIndex + j) % tempGracze.size();
                if (id_gracza == 0) {
                    cout << "Twoje karty to: " << tempGracze[0]->karty[0] << " " << tempGracze[0]->karty[1] << endl;
                    if (tempGracze[id_gracza]->status == "all in" || tempGracze[id_gracza]->status == "pass") {
                        continue;
                    }
                    else {
                        tempGracze[id_gracza]->status = "active";
                        int poprzednia_stawka = tempGracze[id_gracza]->stawka;
                        int tempStawka = tempGracze[id_gracza]->Ruch_Czlowieka(max_stawka);
                        if (tempStawka > max_stawka) {
                            max_stawka = tempStawka;
                            for (auto& gracz : tempGracze) {
                                if (gracz->status == "check") {
                                    gracz->status = "active";
                                }
                            }
                        }
                        if (tempStawka - poprzednia_stawka >= 0) {
                            pula += tempStawka - poprzednia_stawka;
                        }
                    }  
                }
                else{
                    if (tempGracze[id_gracza]->status == "all in" || tempGracze[id_gracza]->status == "pass") {
                        continue;
                    }
                    else {
                        tempGracze[id_gracza]->status = "active";
                        int poprzednia_stawka = tempGracze[id_gracza]->stawka;
                        int tempStawka = tempGracze[id_gracza]->Ruch_Bota(max_stawka, aktualny_stol);
                        if (tempStawka > max_stawka) {
                            max_stawka = tempStawka;
                            for (auto& gracz : tempGracze) {
                                if (gracz->status == "check") {
                                    gracz->status = "active";
                                }
                            }
                        }
                        if (tempStawka - poprzednia_stawka >= 0) {
                            pula += tempStawka - poprzednia_stawka;
                        }
                    }
                }
            }
        }
        if (i == 0) {
            cout << "Karty na stole to: " << stol[0] << ", " << stol[1] << ", " << stol[2] << endl;
            aktualny_stol.push_back(stol[0]);
            aktualny_stol.push_back(stol[1]);
            aktualny_stol.push_back(stol[2]);
        }
        if (i == 1) {
            cout << "Karty na stole to: " << stol[0] << ", " << stol[1] << ", " << stol[2] << ", " << stol[3] << endl;
            aktualny_stol.push_back(stol[3]);
        }
        if (i == 2) {
            cout << "Karty na stole to: " << stol[0] << ", " << stol[1] << ", " << stol[2] << ", " << stol[3] << ", " << stol[4] << endl;
            aktualny_stol.push_back(stol[4]);
        }
        if (i == 3) {
            WinnerFinder();
            numer_rundy++;
            RozpocznijRunde();
        }
    }
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
    lista_winnerow.clear();
    kandydaci.clear();
    Gracz* winner = nullptr;
    PokerHandRank winnerRank = HIGH_CARD;
    for (auto& gracz : gracze) {
        if (gracz->status == "pass") {
            continue;
        }
        vector<string> allCards;
        allCards.push_back(gracz->karty[0]);
        allCards.push_back(gracz->karty[1]);
        allCards.insert(allCards.end(), stol, stol + 5);
        cout << endl;
        for (auto& karta : allCards) {
            cout << karta << " ";
        }
        cout << endl;
        PokerHandRank rank = EvaluatePokerHand(allCards);
        cout << "kombinacja gracza o id: " << gracz->id << " jest równa: " << nazwy_kombinacji[rank] << endl;
        if (rank > winnerRank) {
            kandydaci.clear();
            kandydaci.push_back(gracz);
            winnerRank = rank;
        }
        else if (rank == winnerRank) {
            kandydaci.push_back(gracz);
        }
    }
    if (kandydaci.size() == 1) {
        winner = kandydaci[0];
        if (winner != nullptr) {
            cout << "Zwyciezca rundy to gracz o indexie: " << winner->id << endl;
            cout << "Zwycięzka kombinacja: " << nazwy_kombinacji[winnerRank] << endl;
            lista_winnerow.push_back(winner);
        }
    }
    else {
        lista_winnerow = DrawResolver(kandydaci);
        if (lista_winnerow.size() == 1) {
            winner = lista_winnerow[0];
            cout << "Zwyciezca rundy to gracz o indexie: " << winner->id << endl;
            cout << "Zwycięzka kombinacja: " << nazwy_kombinacji[winnerRank] << endl;
        }
        else {
            cout << "Remis! Zwyciężają gracze o indexach: ";
            for (auto& x : lista_winnerow) {
                cout << x->id << " ";
            }
            cout << endl;
            cout << "Zwycięzka kombinacja: " << nazwy_kombinacji[winnerRank] << endl;
        }
    }
    div_t wygrana = div(pula, lista_winnerow.size());
    for (auto& gracz : gracze) {
        gracz->stawka = 0;
    }
    for (auto& zwyciezcy : lista_winnerow) {
        zwyciezcy->kapital += wygrana.quot;
    }
    cout << "Koniec rundy nr: " << numer_rundy << endl;
}

bool Gra::IsFlush(const vector<string>& cards) {
    string kolor[4] = {"Kier","Karo","Trefl", "Pik"};
    for (int j = 0; j < 4; j++) {
        int kolor_licznik = 0;
        for (int i = 0; i < cards.size(); i++) {
            if (cards[i].substr(cards[i].find(' ') + 1) == kolor[j]) {
                kolor_licznik++;
            }
        }
        if (kolor_licznik >= 5) {
            return true;
        }
    }
    return false;
}

bool Gra::IsStraight(const vector<string>& cards) {
    vector<int> cardValues;
    for (const auto& card : cards) {
        string value = card.substr(0, card.find(' '));
        cardValues.push_back(cardRankValues[value]);
    }
    sort(cardValues.begin(), cardValues.end());
    int strit_licznik = 1;
    for (int i = 0; i < cardValues.size()-1; i++){
        if (cardValues[i]+1 == cardValues[i+1]) {
            strit_licznik++;
        }
        if (cardValues[i] == cardValues[i + 1]) {
            continue;
        }
        else {
            strit_licznik = 1;
        }
    }
    if (strit_licznik >= 5) {
        return true;
    }
    else {
        return false;
    }
}

int Gra::maxFlush(const vector<string>& cards) {
    vector<int> cardValues;
    for (const auto& card : cards) {
        string value = card.substr(0, card.find(' '));
        cardValues.push_back(cardRankValues[value]);
    }
    string kolor[4] = { "Kier","Karo","Trefl", "Pik" };
    for (int j = 0; j < 4; j++) {
        int maxFlush = 0;
        int kolor_licznik = 0;
        for (int i = 0; i < cards.size(); i++) {
            if (cards[i].substr(cards[i].find(' ') + 1) == kolor[j]) {
                kolor_licznik++;
                maxFlush = cardValues[i];
            }
        }
        if (kolor_licznik >= 5) {
            return maxFlush;
        }
    }
}

int Gra::maxStraight(const vector<string>& cards) {
    vector<int> cardValues;
    for (const auto& card : cards) {
        string value = card.substr(0, card.find(' '));
        cardValues.push_back(cardRankValues[value]);
    }
    sort(cardValues.begin(), cardValues.end());
    int maxStraight = 0;
    int strit_licznik = 1;
    for (int i = 0; i < cardValues.size() - 1; i++) {
        if (cardValues[i] + 1 == cardValues[i + 1]) {
            maxStraight = cardValues[i + 1];
            strit_licznik++;
        }
        if (cardValues[i] == cardValues[i + 1]) {
            continue;
        }
        else {
            maxStraight = 0;
            strit_licznik = 1;
        }
    }
    return maxStraight;
}

Gra::PokerHandRank Gra::EvaluatePokerHand(const vector<string>& cards) {
    bool flush = IsFlush(cards);
    bool straight = IsStraight(cards);
    vector<int> cardValues;
    for (const auto& card : cards) {
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

vector<Gracz*> Gra::DrawResolver(vector<Gracz*>& gracze){
    vector<Gracz*> winner;
    vector<int> max_karty;
    PokerHandRank DrawRank = HIGH_CARD;
    for (auto& gracz : gracze) {
        vector<string> allCards;
        allCards.push_back(gracz->karty[0]);
        allCards.push_back(gracz->karty[1]);
        allCards.insert(allCards.end(), stol, stol + 5);
        PokerHandRank rank = EvaluatePokerHand(allCards);
        DrawRank = rank;
    }
    vector <vector<string>> kandydaci_karty;
    vector <vector<int>> kandydaci_karty_int;
    for (auto& kandydat : gracze) {
        vector<string> allCards;
        allCards.push_back(kandydat->karty[0]);
        allCards.push_back(kandydat->karty[1]);
        allCards.insert(allCards.end(), stol, stol + 5);
        kandydaci_karty.push_back(allCards);
    }
    for (auto& kandydat : kandydaci_karty) {
        vector<int> allCards_int;
        allCards_int.clear();
        for (auto& karta : kandydat) {
            string value = karta.substr(0, karta.find(' '));
            allCards_int.push_back(cardRankValues[value]);
        }
        kandydaci_karty_int.push_back(allCards_int);
    }
    for (auto& kandydat : kandydaci_karty_int) {
        sort(kandydat.begin(), kandydat.end(), greater<int>());
    }
    if (DrawRank == STRAIGHT || DrawRank == STRAIGHT_FLUSH || DrawRank == FLUSH || DrawRank == HIGH_CARD) {
        if (DrawRank == STRAIGHT) {
            for (auto& kandydat : kandydaci_karty) {
                max_karty.push_back(maxStraight(kandydat));
            }
            auto max_it = max_element(max_karty.begin(), max_karty.end());
            int max_value = *max_it;
            int count_max = count(max_karty.begin(), max_karty.end(), max_value);
            if (count_max == 1) {
                int licznik = 0;
                for (auto& karta : max_karty) {
                    if (karta == max_value) {
                        winner.push_back(gracze[licznik]);
                        return winner;
                    }
                    else {
                        licznik++;
                    }
                }         
            }
        }
        if (DrawRank == STRAIGHT_FLUSH || DrawRank == FLUSH) {
            for (auto& kandydat : kandydaci_karty) {
                max_karty.push_back(maxFlush(kandydat));
            }
            auto max_it = max_element(max_karty.begin(), max_karty.end());
            int max_value = *max_it;
            int count_max = count(max_karty.begin(), max_karty.end(), max_value);
            if (count_max == 1) {
                int licznik = 0;
                for (auto& karta : max_karty) {
                    if (karta == max_value) {
                        winner.push_back(gracze[licznik]);
                        return winner;
                    }
                    else {
                        licznik++;
                    }
                }
            }
        }
        for (auto& kandydat : kandydaci_karty_int) {
            max_karty.push_back(kandydat[0]);
        }
        auto max_it = max_element(max_karty.begin(), max_karty.end());
        int max_value = *max_it;
        int count_max = count(max_karty.begin(), max_karty.end(), max_value);
        if (count_max == 1) {
            int licznik = 0;
            for (auto& karta : max_karty) {
                if (karta == max_value) {
                    break;
                }
                else {
                    licznik++;
                }
            }
            winner.push_back(gracze[licznik]);
            return winner;
        }
        else {
            int licznik = 0;
            for (auto& karta : max_karty) {
                if (karta == max_value) {
                    winner.push_back(gracze[licznik]);
                    licznik++;
                }
                else {
                    licznik++;
                }
            }
            return winner;
        }
    }
    if (DrawRank == ONE_PAIR || DrawRank == TWO_PAIR || DrawRank == THREE_OF_A_KIND || DrawRank == FULL_HOUSE || DrawRank == FOUR_OF_A_KIND) {
        vector<int> sumy_oczek;
        for (auto& kandydat : kandydaci_karty_int) {
            int liczba_oczek = 0;
            map<int, int> valueCount;
            for (int value : kandydat) {
                valueCount[value]++;
            }
            for (const auto& pair : valueCount) {
                if (pair.second == 2 || pair.second == 3 || pair.second == 4) {
                    liczba_oczek += pair.first;
                }
            }
            sumy_oczek.push_back(liczba_oczek);
        }
        auto max_it = max_element(sumy_oczek.begin(), sumy_oczek.end());
        int max_value = *max_it;
        int count_max = count(sumy_oczek.begin(), sumy_oczek.end(), max_value);
        if (count_max == 1) {
            int licznik = 0;
            for (auto& karta : sumy_oczek) {
                if (karta == max_value) {                  
                    break;
                }
                else {
                    licznik++;
                }
            }
            winner.push_back(gracze[licznik]);
            return winner;
        }
        else {
            int licznik = 0;
            for (auto& karta : sumy_oczek) {
                if (karta == max_value) {
                    winner.push_back(gracze[licznik]);
                    licznik++;
                }
                else {
                    licznik++;
                }
            }
            return winner;
        }
    }
}