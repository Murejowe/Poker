#include "Gra.h"

Gra::Gra() {
    ResetTalia();
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
        cout << "Podaj poziom trudnoœci bota nr." << i + 1 << " (1-3): " << endl;
        cin >> temp;
        while (sprawdzam(temp) == 0) {
            cout << "Wprowadzono niepoprawn¹ wartoœæ! " << endl << "Podaj poziom trudnoœci bota nr." << i + 1 << " (1-3): " << endl;
            cin >> temp;
        }
        list.push_back(temp);
    }
    for (const auto& element : list) {
        cout << element << endl;
    }
    int kapital;
    cout << "Podaj kapita³ pocz¹tkowy ka¿dego gracza (min. 100): " << endl;
    cin >> kapital;
    while (kapital < 100) {
        cout << "Wprowadzono niepoprawn¹ wartoœæ! " << endl << "Podaj kapita³ pocz¹tkowy ka¿dego gracza (min. 100): " << endl;
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
        cout << "Gratulacje! Wygra³eœ" << endl;
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
    Gracz* zwyciezca = nullptr;
    int max_kapital = -1;

    for (auto& gracz : gracze) {
        if (gracz->kapital > max_kapital) {
            max_kapital = gracz->kapital;
            zwyciezca = gracz;
        }
        gracz->stawka = 0; // Reset each player's stake
    }

    if (zwyciezca != nullptr) {
        if (zwyciezca->id == 0) {
            cout << "Zwyciezca rundy to: Czlowiek" << endl;
        }
        else {
            cout << "Zwyciezca rundy to: Bot ID: " << zwyciezca->id << endl;
        }
        cout << "Kapital zwyciezcy: " << zwyciezca->kapital << endl;
    }
}

