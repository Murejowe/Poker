#include <iostream>
#include <vector>
#include <algorithm> // For std::shuffle
#include <random>    // For std::default_random_engine
#include <chrono>    // For std::chrono::system_clock

using namespace std;

class Gracz {
public:
    int id;
    int kapital;
    string karty[2];
    int stawka;
    bool dealer;
    string status;
    Gracz(int id, int kapital, string karty[2], int stawka, bool dealer, string status) : id(id), kapital(kapital), stawka(stawka), dealer(dealer), status(status) {
        this->karty[0] = karty[0];
        this->karty[1] = karty[1];
    }
};

class Czlowiek : public Gracz {
public:
    Czlowiek(int id, int kapital, string karty[2], int stawka, bool dealer, string status) : Gracz(id, kapital, karty, stawka, dealer, status) {}
};

class Bot : public Gracz {
public:
    int poziom_trudnosci;
    Bot(int id, int kapital, string karty[2], int stawka, bool dealer, string status, int poziom_trudnosci) : Gracz(id, kapital, karty, stawka, dealer, status), poziom_trudnosci(poziom_trudnosci) {}
};

class Gra {
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
    Gra() {
        ResetTalia();
    }
    void RozdajKarty(vector<Gracz*>& gracze, Gra* gra);
    void TworzGraczy();
    int SetDealer();
    void RozpocznijRunde();
    void OdkryjStol();
    void WinnerFinder();
    void ResetTalia();
private:
    int liczba_graczy;
};

void Gra::ResetTalia() {
    talia = initial_talia;
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(talia.begin(), talia.end(), default_random_engine(seed));
}

void Gra::RozdajKarty(vector<Gracz*>& gracze, Gra* gra) {
    if (talia.size() < gracze.size() * 2) {
        cout << "Not enough cards in the deck to deal!" << endl;
        return;
    }

    for (auto& gracz : gracze) {
        gracz->karty[0] = talia.back(); talia.pop_back();
        gracz->karty[1] = talia.back(); talia.pop_back();
    }
    for (int i = 0; i < 5; i++) {
        gra -> stol[i] = talia.back();
        talia.pop_back();
    }
}

int sprawdzam(int x) {
    return (x < 1 || x > 3) ? 0 : 1;
}

int main() {
    try {
        cout << "Witaj w grze Poker!" << endl << "Wybierz opcję: " << endl << "1) Rozpocznij partię" << endl << "2) Wyjdź z gry" << endl;
        string placeholder[2] = { "", "" };
        int tytul_input = 0;
        cin >> tytul_input;
        if (tytul_input == 1) {
            int liczba_graczy;
            cout << "Podaj liczbę graczy (1-3): " << endl;
            cin >> liczba_graczy;
            while (sprawdzam(liczba_graczy) == 0) {
                cout << "Wprowadzono niepoprawną wartość! " << endl << "Podaj liczbę graczy (1-3): " << endl;
                cin >> liczba_graczy;
            }
            int temp;
            vector<int> list;
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
            vector<Gracz*> gracze;
            gracze.push_back(&czlowiek);
            for (int i = 0; i < liczba_graczy; i++) {
                Bot bot(i + 1, kapital, placeholder, 0, 0, "status", list[i]);
                listabotow.push_back(bot);
            }

            for (auto& bot : listabotow) {
                gracze.push_back(&bot);
            }

            Gra gra;
            gra.ResetTalia();
            gra.RozdajKarty(gracze, &gra);
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
                cout << gra.stol[i] << endl;
            }
        }
        else if (tytul_input == 2) {
            return 0;
        }
        else {
            cout << "Wprowadzono niepoprawną wartość!" << endl;
            main();
        }
    }
    catch (const exception& e) {
        cout << "An error occurred: " << e.what() << endl;
    }
    catch (...) {
        cout << "An unknown error occurred." << endl;
    }
    return 0;
}