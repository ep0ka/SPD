#include<iostream>
#include<algorithm>
#include<fstream>
#include<vector>

class Zadania
{
	public:
	int _Nr_zadania;
	int _Wartosc;
	int _Koniec;
	Zadania(){_Nr_zadania = 0; _Wartosc = 0; _Koniec=0;};
	Zadania(int war){_Wartosc = war;};
};

class Maszyna
{
	public:
	int _Nr_maszyny;
	Maszyna(){_Nr_maszyny = 0;}
	std::vector<Zadania> _Zadania;
};

void Wczytywanie(std::vector<Maszyna>& maszyny, std::ifstream& infile, int& il_zad, int& il_masz)
{
	int zad_aktualne,nr_masz=0,tmp=0;
	infile >> il_zad >> il_masz;
	
	for(int j=0; j<il_masz; j++)
	{
		maszyny.push_back(Maszyna());	
	}
	for(int i=0; i<il_zad*il_masz; i++)
	{
		nr_masz = tmp%il_masz;
		infile >> zad_aktualne;
		++tmp;
		maszyny[nr_masz]._Zadania.push_back(Zadania(zad_aktualne));
	}
}
void permut(int n, int A[], const int wlk, std::vector<int>& kolej)
{
         if(n == 1)
         {
                 for(int j=0; j<wlk; j++)
                 {
                         //cout << A[j];
                         kolej.push_back(A[j]);
                 }
                 return;
         }
         else
         {
                 permut(n-1,A,wlk,kolej);
                 for(int i=0; i < n-1; i++)
                 {
                         if(n%2 == 0) std::swap(A[i],A[n-1]);
                         else std::swap(A[0],A[n-1]); 
                         permut(n-1,A,wlk,kolej);
                 }               
         }
}

void CMAX(std::vector<Maszyna>& maszyny,int il_zad, int il_masz, std::vector<int> kolej)
{
	int x=0;
	for(x; x<kolej.size(); x++)
	{
	//std::cout << "X: " << x << std::endl;
	int kolejnosc[il_zad],kol_zad=0,kol_masz=0;
	int cmax=0, tmp=0;

	for(int y=0;y<il_zad;y++)
	{
		kolejnosc[y]=kolej[x+y];
	}
	
	//zapis konca wszystkich zadan maszyny 1

	for(int i=0; i<il_zad; i++)
	{
		cmax += maszyny[0]._Zadania[kolejnosc[i]]._Wartosc;
		maszyny[0]._Zadania[kolejnosc[i]]._Koniec = cmax;
	//	std::cout << "W: " << maszyny[0]._Zadania[kolejnosc[i]]._Koniec << std::endl;
	}

	++kol_masz;
	++kol_zad;

	for(int j=0; j<il_masz-1; j++)
	{
		maszyny[kol_masz]._Zadania[kolejnosc[kol_zad-1]]._Koniec = maszyny[kol_masz-1]._Zadania[kolejnosc[kol_zad-1]]._Koniec+maszyny[kol_masz]._Zadania[kolejnosc[kol_zad-1]]._Wartosc;
		for(int k=0; k<il_zad-1;k++)
		{
			if(maszyny[kol_masz-1]._Zadania[kolejnosc[k+1]]._Koniec <= maszyny[kol_masz]._Zadania[kolejnosc[k]]._Koniec)
			{
				maszyny[kol_masz]._Zadania[kolejnosc[k+1]]._Koniec = maszyny[kol_masz]._Zadania[kolejnosc[k]]._Koniec+maszyny[kol_masz]._Zadania[kolejnosc[k+1]]._Wartosc;
			}
			else maszyny[kol_masz]._Zadania[kolejnosc[k+1]]._Koniec = maszyny[kol_masz-1]._Zadania[kolejnosc[k+1]]._Koniec+maszyny[kol_masz]._Zadania[kolejnosc[k+1]]._Wartosc;
		}
		++kol_masz;
	}
	
	std::cout << "Kolejnosc: "; 
	for(int z=0;z<il_zad;z++)
	{
		std::cout << kolej[x+z]+1; 
	}
	std::cout << " Cmax: " <<  maszyny[il_masz-1]._Zadania[kolejnosc[il_zad-1]]._Koniec<< std::endl;
	x += il_zad-1;
	}
}

int main()
{
	std::vector<int> wartosci_plik;
	std::vector<Maszyna> maszyny;
	std::ifstream infile("rand_gen.txt");
	int il_zad, il_masz;
	std::vector<int> kolej;
	


	Wczytywanie(maszyny,infile, il_zad, il_masz);
	int tab[il_zad];
	
	for(int i=0; i<il_zad; i++)
	{
		tab[i] = i;			
	}
	permut(il_zad,tab,il_zad,kolej);
	
	CMAX(maszyny, il_zad, il_masz,kolej);

	/*for(int i=0; i<il_masz; i++)
	{
		for(int j=0; j<il_zad; j++)
		{
			std::cout << "Maszyna: " << i << " wartosc: " << maszyny[i]._Zadania[j]._Koniec << std::endl;
		}
	}*/
}
