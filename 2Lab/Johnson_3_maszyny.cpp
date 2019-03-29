#include <iostream>
#include <fstream>
#include <vector>
#include<chrono>

struct Zadania{
	int _Nr_zad = -1;
	int _Wartosc = -1;

Zadania(int a, int b) {_Nr_zad = a; _Wartosc = b; }
Zadania(){}
};
Zadania operator + (Zadania &A, Zadania &B)
{
	A._Wartosc = A._Wartosc + B._Wartosc;
	return A;
}

struct Maszyna{
	int _Nr_maszyny = -1;
	std::vector<Zadania> _Zadania;

	Maszyna(int a) { _Nr_maszyny = a;}
};


int Sprawdzanie(std::vector<int> &V, int Szukane,int Liczba_Zadan)
{
	for (int i = 0; i < Liczba_Zadan; ++i)
	{
		// if ( V.size() > i)
		// {		
		if ( V[i] == Szukane )
			return 1;
		// }
	}
	return 0;
}

int Strona_Min(Zadania const &A, Zadania const &B)
{
	if (A._Wartosc <= B._Wartosc)
	{
		return 1;
	}
	else return 2;
}

Zadania Min(Zadania &A, Zadania &B)
{

	if ( A._Wartosc <= B._Wartosc )
	{
		return A;
	}
	else if ( A._Wartosc > B._Wartosc )
	{
		return B;
	}
	else return Zadania(-2,-2);
}
void Wczytywanie(std::vector<Maszyna>& maszyny, std::ifstream& infile, int& il_zad, int& il_masz)
{
	int zad_aktualne,nr_masz=0,tmp=0;
	infile >> il_zad >> il_masz;

	for(int j=0; j<il_masz; j++)
	{
		maszyny.push_back(Maszyna(j+1)); // epoka -> dodałem j+1, bo u mnie jest konstruktor który ustawia NR maszyny
	}
	for(int i=0; i<il_zad*il_masz; i++)
	{
		nr_masz = tmp%il_masz;
		infile >> zad_aktualne;
		++tmp;
		maszyny[nr_masz]._Zadania.push_back(Zadania(maszyny[nr_masz]._Zadania.size()+1,zad_aktualne)); // maszyny[nr_masz]._Zadania.size()+1, musiałem dodać żeby mój algorytm działał
	}
}
//////////////////////////////////////////////////////////////////////////
// MAIN 
//////////////////////////////////////////////////////////////////////////

int main()
{
	int Liczba_Zadan = 5;
	int Liczba_Maszyn = 3;
	
	std::ifstream Plik("data/7rand_gen.txt"); //zmieniłen "infile" na "Plik"
	
	std::vector<Maszyna> Maszyny;
	
	Wczytywanie(Maszyny, Plik, Liczba_Zadan, Liczba_Maszyn);

	auto start = std::chrono::high_resolution_clock::now();
	if ( Maszyny.size() > 2 )
	{
		for (int i = 0; i < Liczba_Zadan; ++i)
		{
			Maszyny[0]._Zadania[i] = Maszyny[0]._Zadania[i] + Maszyny[1]._Zadania[i];
			Maszyny[1]._Zadania[i] = Maszyny[1]._Zadania[i] + Maszyny[2]._Zadania[i];
		}
	}

/*	printf("\n");
	for (int i = 0; i < Liczba_Zadan; ++i)
	{
		printf("%i:%i ",Maszyny[0]._Zadania[i]._Nr_zad,Maszyny[0]._Zadania[i]._Wartosc);
	}
		printf("\n");
	for (int i = 0; i < Liczba_Zadan; ++i)
	{
		printf("%i:%i ",Maszyny[1]._Zadania[i]._Nr_zad, Maszyny[1]._Zadania[i]._Wartosc);
	}
		printf("\n");
*/
///////////////////////////////////////////////////////////////////////////
//Algorytm Johnsona
///////////////////////////////////////////////////////////////////////////

	Zadania tmp1, tmp2;
	int lewo = 0, prawo = Liczba_Zadan-1, strona = -1;
	std::vector<int> Kolejnosc;

for (int i = 0; i < Liczba_Zadan; ++i)
	{
		Kolejnosc.push_back(-1);
	}
for (int j = 0; j < Liczba_Zadan; ++j)
{
	tmp1._Wartosc = 999;
	tmp2._Wartosc = 999;

	for (int i = 0; i < Liczba_Zadan; ++i)
	{

		if ( Sprawdzanie(Kolejnosc, i+1,Liczba_Zadan) != 1 )
		{
			tmp1 = Min(tmp1,Maszyny[0]._Zadania[i]);
			tmp2 = Min(tmp2,Maszyny[1]._Zadania[i]);
		}
	}

	strona = Strona_Min(tmp1,tmp2);
	tmp1 = Min(tmp1,tmp2);
	if ( strona == 1 )
	{
		Kolejnosc[lewo++] = tmp1._Nr_zad;
	}
	if ( strona == 2 )
	{
		Kolejnosc[prawo--] = tmp1._Nr_zad;
	}

}
	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	std::cout << "Czas Johnson: " << elapsed.count() << "s\n";

///////////////////////////////////////////////////////////////////////////
// Wypisywanie wyników
///////////////////////////////////////////////////////////////////////////

	printf("\nProponowana kolejność:\n");
	for (int i = 0; i < Liczba_Zadan; ++i)
	{
		printf("%i ", Kolejnosc[i]);
	}
	printf("\n");

}
