#include <iostream>
#include <vector>
#include "Gracz.h"
#include "Czlowiek.h"
#include "Bot.h"
#include "Gra.h"
using namespace std;


int main() {
    try {
        cout << "Witaj w grze Poker!" << endl << "Wybierz opcję: " << endl << "1) Rozpocznij partię" << endl << "2) Wyjdź z gry" << endl;
        int tytul_input = 0;
        cin >> tytul_input;
        Gra gra;
        if (tytul_input == 1) {
            int liczba_graczy;
            cout << "Podaj liczbę graczy (1-3): " << endl;
            cin >> liczba_graczy;
            while (gra.sprawdzam(liczba_graczy) == 0) {
                cout << "Wprowadzono niepoprawną wartość! " << endl << "Podaj liczbę graczy (1-3): " << endl;
                cin >> liczba_graczy;
            }
            gra.TworzGraczy(liczba_graczy);
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