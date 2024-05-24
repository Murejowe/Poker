#include <iostream>
using namespace std;
class Gracz {
public:
	int id;
	int kapital;
	string karty;
	int stawka;
//	boolean dealer;
	string status;
	Gracz(int id, int kapital, string karty, int stawka) {
		this->id = id;
		this->kapital = kapital;
		this->karty = karty;
		this->stawka=stawka;
	}
	void Ruch_Czlowieka();
};
class Czlowiek
{
public:
	Czlowiek(int id, int kapital, string karty, int stawka, string status) {
		this->id = id;
		this->kapital = kapital;
		this->karty = karty;
		this->stawka = stawka;
		this->status = status;
	}
};
class Bot {
private:
	int  poziom_trudnosci;
public:
	Bot(int id, int kapital, string karty, int stawka, string status,int poziom_trudnosci)
	this->id = id;
	this->kapital = kapital;
	this->karty = karty;
	this->stawka = stawka;
	this->status = status;
	this->poziom_trudnosci = poziom_trudnosci;
};
class Gra{
protected:
	string talia;
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

int main()
{
	cout << "Witaj w grze Poker!" << endl << "Wybierz opcję: " << endl << "1) Rozpocznij partię" << endl << "2) Wyjdź z gry";
	int tytul_input = 0;
	cin >> tytul_input;
	if (tytul_input == 1) {
		cout << "Tu będą opcje...";
	}
	else {
		return 0;
	}

}


