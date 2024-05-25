#include <iostream>
#include <vector>
using namespace std;

class Gracz {
	public:
		int id;
		int kapital;
		string karty;
		int stawka;
		bool dealer;
		string status;
		Gracz(int id, int kapital, string karty, int stawka, bool dealer, string status) {
			this->id = id;
			this->kapital = kapital;
			this->karty = karty;
			this->stawka = stawka;
			this->dealer = dealer;
			this->status = status;
		}
};

class Czlowiek : public Gracz{
	public:
		Czlowiek(int id, int kapital, string karty, int stawka, bool dealer, string status) : Gracz(id, kapital, karty, stawka, dealer, status) {}
};

class Bot : public Gracz{
	private:
		int  poziom_trudnosci;
	public:
		Bot(int id, int kapital, string karty, int stawka, bool dealer, string status, int poziom_trudnosci) : Gracz(id, kapital, karty, stawka, dealer, status), poziom_trudnosci(poziom_trudnosci){}
};
class Gra{
	protected:
		string talia[52] = {
		"As Karo", "2 Karo", "3 Karo", "4 Karo", "5 Karo", "6 Karo", "7 Karo", "8 Karo", "9 Karo", "10 Karo", "Walet Karo", "Dama Karo", "Król Karo",
		"As Kier", "2 Kier", "3 Kier", "4 Kier", "5 Kier", "6 Kier", "7 Kier", "8 Kier", "9 Kier", "10 Kier", "Walet Kier", "Dama Kier", "Król Kier",
		"As Trefl", "2 Trefl", "3 Trefl", "4 Trefl", "5 Trefl", "6 Trefl", "7 Trefl", "8 Trefl", "9 Trefl", "10 Trefl", "Walet Trefl", "Dama Trefl", "Król Trefl",
		"As Pik", "2 Pik", "3 Pik", "4 Pik", "5 Pik", "6 Pik", "7 Pik", "8 Pik", "9 Pik", "10 Pik", "Walet Pik", "Dama Pik", "Król Pik"
		};
	public:
		string stol;
		int pula;
		void RozdajKarty();
		void TworzGraczy();
		int SetDealer();
		void RozpocznijRunde();
		void OdkryjStol();
		void WinnerFinder();
	private:
		int liczba_graczy;
};

int sprawdzam(int x) {
	if (x < 1 || x > 3) {
		return 0;
	}
	else {
		return 1;
	}
}

int main()
{
	cout << "Witaj w grze Poker!" << endl << "Wybierz opcję: " << endl << "1) Rozpocznij partię" << endl << "2) Wyjdź z gry" << endl;
	int tytul_input = 0;
	cin >> tytul_input;
	if (tytul_input == 1) {
		int liczba_graczy;
		cout << "Podaj liczbę graczy (1-3): " << endl;
		cin >> liczba_graczy;
		while(sprawdzam(liczba_graczy)==0){
			cout << "Wprowadzono niepoprawną wartość! " << endl << "Podaj liczbę graczy (1-3): " << endl;
			cin >> liczba_graczy;
		}
		int temp;
		vector<int> list;
		for (int i = 0; i < liczba_graczy; i++) {
			cout << "Podaj poziom trudności bota nr." << i+1 << " (1-3): " << endl;
			cin >> temp;
			while (sprawdzam(temp) == 0) {
				cout << "Wprowadzono niepoprawną wartość! " << endl << "Podaj poziom trudności bota nr." << i+1 << " (1-3): " << endl;
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

	}
	else if(tytul_input == 2){
		return 0;
	}
	else {
		cout << "Wprowadzono niepoprawną wartość!" << endl;
		main();
	}

}
