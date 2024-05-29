#include "Gra.h"

Gra::Gra() {
    ResetTalia();
}

int Gra::sprawdzam(int x) {
    return (x < 1 || x > 3) ? 0 : 1;
};
void Gra::ResetTalia() {
    talia = initial_talia;
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(talia.begin(), talia.end(), default_random_engine(seed));
}
void Gra::RozdajKarty(vector<Gracz*>& gracze) {
    if (talia.size() < gracze.size() * 2) {
        cout << "Not enough cards in the deck to deal!" << endl;
        return;
    }

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
        cout << "Podaj poziom trudno�ci bota nr." << i + 1 << " (1-3): " << endl;
        cin >> temp;
        while (sprawdzam(temp) == 0) {
            cout << "Wprowadzono niepoprawn� warto��! " << endl << "Podaj poziom trudno�ci bota nr." << i + 1 << " (1-3): " << endl;
            cin >> temp;
        }
        list.push_back(temp);
    }
    for (const auto& element : list) {
        cout << element << endl;
    }
    int kapital;
    cout << "Podaj kapita� pocz�tkowy ka�dego gracza (min. 100): " << endl;
    cin >> kapital;
    while (kapital < 100) {
        cout << "Wprowadzono niepoprawn� warto��! " << endl << "Podaj kapita� pocz�tkowy ka�dego gracza (min. 100): " << endl;
        cin >> kapital;
    }
    vector<Bot> listabotow;
    Czlowiek czlowiek(0, kapital, placeholder, 0, 0, "");
    vector<Gracz*> gracze;
    gracze.push_back(&czlowiek);
    for (int i = 0; i < liczba_graczy; i++) {
        Bot bot(i + 1, kapital, placeholder, 0, 0, "status", list[i]);
        listabotow.push_back(bot);
    }

    for (auto& bot : listabotow) {
        gracze.push_back(&bot);
    }
    ResetTalia();
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
    for (int i = 0; i < 5; i++) {
        cout << stol[i] << endl;
    }
}