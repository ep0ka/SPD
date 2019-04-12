#include<math.h>
#include<iostream>
#include<algorithm>
#include<fstream>
#include<vector>
#include<chrono>
#include<stdlib.h>
#include<time.h>
#include<random>
#include <ctime>
#include <unistd.h>

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

//Deklaracje funkcji:
std::vector<int> NEH(std::vector<Maszyna> maszyny);
////////////////////////////////////////////////////

void print_vec(std::vector<int> vec,int a)
{
	printf("\n");
	for(int i=0; i<vec.size(); i++)
	{
		std::cout<<vec[i]+a << ", ";
	}
}

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
			 //std::cout << A[j];
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
////////////////////////////////////////////////////////////////////////////////////////
int CMAX(std::vector<Maszyna>& maszyny,int il_zad, int il_masz, int kolej[])
{
	int x=0;
//	for(x; x<kolej.size(); x++)
//	{
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
	
	// std::cout << "Kolejnosc: "; 
	// for(int z=0;z<il_zad;z++)
	// {
		// std::cout << kolej[x+z]+1; 
	// }
	return maszyny[il_masz-1]._Zadania[kolejnosc[il_zad-1]]._Koniec;
	// x += il_zad-1;
//	}
}
////////////////////////////////////////////////////////////////////////////////////////
// int CMAX(std::vector<Maszyna> maszyny,int il_zad, int il_masz, int kolejnosc[])
// {
// 	int kol_masz=0,kol_zad=0;
// 	for(int i=0; i<il_zad; i++)
// 	{
// 		maszyny[0]._Zadania[kolejnosc[i]]._Koniec += maszyny[0]._Zadania[kolejnosc[i]]._Wartosc;
// 	}

// 	++kol_masz;
// 	++kol_zad;

// 	for(int j=0; j<il_masz-1; j++)
// 	{
// 		maszyny[kol_masz]._Zadania[kolejnosc[kol_zad-1]]._Koniec = maszyny[kol_masz-1]._Zadania[kolejnosc[kol_zad-1]]._Koniec+maszyny[kol_masz]._Zadania[kolejnosc[kol_zad-1]]._Wartosc;
// 		for(int k=0; k<il_zad-1;k++)
// 		{
// 			if(maszyny[kol_masz-1]._Zadania[kolejnosc[k+1]]._Koniec <= maszyny[kol_masz]._Zadania[kolejnosc[k]]._Koniec)
// 			{
// 				maszyny[kol_masz]._Zadania[kolejnosc[k+1]]._Koniec = maszyny[kol_masz]._Zadania[kolejnosc[k]]._Koniec+maszyny[kol_masz]._Zadania[kolejnosc[k+1]]._Wartosc;
// 			}
// 			else maszyny[kol_masz]._Zadania[kolejnosc[k+1]]._Koniec = maszyny[kol_masz-1]._Zadania[kolejnosc[k+1]]._Koniec+maszyny[kol_masz]._Zadania[kolejnosc[k+1]]._Wartosc;
// 		}
// 		++kol_masz;
// 	}
	
// 	return maszyny[il_masz-1]._Zadania[kolejnosc[il_zad-1]]._Koniec;
// }

int Zarzadzanie_CMAX(std::vector<int> kolej, std::vector<Maszyna> maszyny, const int il_zad, const int il_masz)
{
	
	//auto start = std::chrono::high_resolution_clock::now();
	int x=0,cmax=0,min_cmax=999999;
	std::vector<int> min_kolej;
	for(x; x<kolej.size(); x++)
	{
		int kolejnosc[il_zad],kol_zad=0,kol_masz=0;
		int cmax=0, tmp=0;

		for(int y=0;y<il_zad;y++)
		{
			kolejnosc[y]=kolej[x+y];
		}

		cmax = CMAX(maszyny, il_zad, il_masz, kolejnosc);	
		
		if(cmax < min_cmax)
		{
			min_kolej.clear();
			min_cmax = cmax;
			for(int i=0; i<il_zad; i++)
			{
				min_kolej.push_back(kolej[x+i]+1);	
			}
		}
/*
		std::cout << "Kolejnosc: "; 

		for(int z=0;z<il_zad;z++)
		{
			std::cout << kolej[x+z]+1; 
		}
		std::cout << " Cmax: " << cmax << std::endl;
*/	

		x += il_zad-1;
	}

	//auto finish = std::chrono::high_resolution_clock::now();
	//std::chrono::duration<double> elapsed = finish - start;
	//std::cout << "Czas Johnson: " << elapsed.count() << "s\n";
	/*std::cout << "Kolejnosc optymalna: "; 
	print_vec(min_kolej,0);	
	std::cout << " Minimalny Cmax: " << min_cmax << std::endl;
	*/return min_cmax;
}

void Sortowanie(std::vector<Zadania>& czasy, int il_zad)
{
	for(int i=0; i<il_zad; i++)
		for(int j=1; j<il_zad;j++)
			if(czasy[j-1]._Wartosc>czasy[j]._Wartosc)
				std::swap(czasy[j-1], czasy[j]);
}


//Zwracam kolejnosc zadan od najmniejszego do najwiekszego.
std::vector<int> Sumowanie_Zadan(std::vector<Maszyna> maszyny)
{
	int il_masz = maszyny.size();
	int il_zad = maszyny[0]._Zadania.size();
	std::vector<Zadania> czasy;

	for(int z=0;z<il_zad;z++) czasy.push_back(Zadania());

	for(int i=0; i<il_masz; i++)
	{
	//	std::cout << "Kolejne=============" << std::endl;
		for(int j=0; j<il_zad; j++)
		{
			czasy[j]._Wartosc += maszyny[i]._Zadania[j]._Wartosc;
			czasy[j]._Nr_zadania = j;
	//		std::cout << "Czasy: " << czasy[j]._Wartosc << std::endl;
		}
	}

	Sortowanie(czasy,il_zad);
/*	std::cout << "Posortowane=========" << std::endl;
	for(int j=0;j<il_zad;j++)
	{
		std::cout << "Nr zadania: " << czasy[j]._Nr_zadania  <<"Sort: " << czasy[j]._Wartosc << std::endl;
	}
*/
	std::vector<int> kolej;

	for(int k=0;k<il_zad;k++)
	{
		kolej.push_back(czasy[k]._Nr_zadania);
	}

	return kolej;
}
//////////////////////////////////////////////////////////
//Symulowane Wyżarzanie
//////////////////////////////////////////////////////////
double Random(double a, double b)
{
   // std::mt19937_64 re;
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine re (seed);
	std::uniform_real_distribution<double> dystrybution(a,b);
	// printf("\nRandomowa liczba:%f\n",dystrybution(re)); //wypisywanie dla sprawdzenia czy faktycznie sa randomowe
	return dystrybution(re);
}

void GenRuch(std::vector<int> &a)
{
	// high_resolution_clock::time_point t1 = high_resolution_clock::now();
	srand(std::clock());
	int wybrana=-1, zamieniana=-1;	
	while(wybrana == zamieniana)
	{
		wybrana = rand() % a.size();
		zamieniana = rand() % a.size();
	}
	std::swap(a[wybrana], a[zamieniana]);
}

void Shuffle(std::vector<int> &wektor)
{
	std::random_device rd;
    std::mt19937 g(rd());
 
    std::shuffle(wektor.begin(), wektor.end(), g);
}

void Insert(std::vector<int> &wektor)
{
	srand(std::clock());
	int wybrana=-1, zamieniana=-1;	
	int wartosc;
	
	while(wybrana == zamieniana)
	{
		wybrana = rand() % wektor.size();
		zamieniana = rand() % wektor.size();
	}
	wartosc=wektor[wybrana];
	wektor.erase(wektor.begin()+wybrana);
	wektor.insert(wektor.begin()+zamieniana,wartosc);
	// print_vec(wektor,1);
}

bool Ruch(int const cmax1, int const cmax2, double &T)
{
	double P=-1, u=0.99;
	if(cmax1 > cmax2)
	{
		return true; //Prawdopodobieństwo równe 1, na pewno jest lepszym rozwiązaniem
	}
	else 
	{
		P=exp((cmax1 - cmax2)/T);
		if (P >= Random(0,1))
		{
			T=T*u;//4 Schładzanie
			return true;
		}
		else 
		{
			T=T*u;//4 Schładzanie
			return false;
		}
	}
}

// void PrzepisanieKolejnosci(std::vector<int> &a, std::vector<int> &b)
// {
	// a = b;
// }
void SymWyz(std::vector<Maszyna> maszyny)
{
	//1 Inicjalizacja
	// std::vector<int> oryginal = Sumowanie_Zadan(maszyny); //Losowa kolejnosc
	std::vector<int> oryginal = NEH(maszyny); //Kolejnosc z NEH 
	// print_vec(oryginal,1);	
	std::vector<int> sasiad = oryginal;
	std::vector<int> tmp = oryginal;
	double T0=6, T=T0;
	int Cmax_Org=-1, Cmax_Sa=-1, Cmax_tmp=-1, iteracje=0;
	
	for (int i = 0; i < 400; ++i)
	{
		Cmax_tmp = Zarzadzanie_CMAX(tmp,maszyny,tmp.size(),maszyny.size());
		if(Cmax_tmp>Cmax_Org)
		{
			tmp = oryginal;
		}
		Cmax_Org=-1; Cmax_Sa=-1;// iteracje=0;
		T=T0; //Początkowa temperatura
		
		while (T>5)//5 Kryterium stopu
		{
			//2 Generowanie ruchu
			//////////////////////////////////////////////////////////////
			// GenRuch(sasiad); //Swap                                 ///
			// Shuffle(sasiad); //Shuffle    /* Wybór sąsiada */       ///
			Insert(sasiad); //Insert                                   ///
			//////////////////////////////////////////////////////////////
			Cmax_Org = Zarzadzanie_CMAX(oryginal,maszyny,oryginal.size(),maszyny.size()); //Wyliczanie cmax dla oryginalnej kolejnosci
			Cmax_Sa = Zarzadzanie_CMAX(sasiad,maszyny,oryginal.size(),maszyny.size()); //Wyliczanie cmax dla sąsiedniej kolejnosci
			//3 Wykonanie lub nie wykonanie ruchu
			if(Ruch(Cmax_Org,Cmax_Sa,T))
			{
				oryginal = sasiad;
				// print_vec(oryginal,1); //Wypisywanie kolejnosci
			}
			else
			{
				sasiad = oryginal;
			}
			++iteracje;
		}
	}


	// print_vec(tmp,1); //Wypisywanie kolejnosci
	printf("Cmax: %i, Liczba_iteracji: %i ",Zarzadzanie_CMAX(tmp,maszyny,tmp.size(),maszyny.size()), iteracje); //wyświetlanie cmax

	// float rand = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	// printf("\n %f \n",Random(0.5,1));
	// print_vec(sasiad,1);
	// printf("Cmax: %i ",Zarzadzanie_CMAX(sasiad,maszyny,oryginal.size(),maszyny.size()));
}

//////////////////////////////////////////////////////////
//NEH
//////////////////////////////////////////////////////////
std::vector<int> NEH(std::vector<Maszyna> maszyny)
{
	std::vector<int> posort = Sumowanie_Zadan(maszyny);
	// print_vec(posort,1);
	std::vector<int> tmp;
	int min_cmax = 999999,war,flaga=0,min_war=0;
	std::vector<int> min_kolej;

	int dlg = posort.size();

	for(int i=0; i<dlg; i++)
	{
		tmp.push_back(posort.back());
		posort.pop_back();
		if(tmp.size() > 1)
		{
			for(int j=0; j<tmp.size();j++)
			{
 				war = Zarzadzanie_CMAX(tmp,maszyny,i+1,maszyny.size());
				if(min_cmax > war)
			       	{
					flaga=1;
					min_cmax = war;
					min_war=war;
					min_kolej.erase(min_kolej.begin(),min_kolej.end());
					min_kolej.assign(tmp.begin(),tmp.end());
				}
				if(j == tmp.size()-1) break;
				std::swap(tmp[tmp.size()-j-2],tmp[tmp.size()-j-1]);
			}
			if(flaga == 1)
			{
				tmp.erase(tmp.begin(),tmp.end());
				tmp.assign(min_kolej.begin(),min_kolej.end());	
				flaga=0;
				min_cmax=999999;
			}
		}
	}
	// std::cout << "Kolejnosc: ";
	// print_vec(min_kolej,1);
	// std::cout<<std::endl<<"Min CMAX: " << min_war << std::endl;
	return min_kolej;
}

std::vector<int> mod4_NEH(std::vector<Maszyna> maszyny, std::vector<int> posort, int& imp_cmax)
{
        std::vector<int> tmp;
        int min_cmax = 999999,war,flaga=0,min_war=0;
        std::vector<int> min_kolej;

        int dlg = posort.size();

        for(int i=0; i<dlg; i++)
        {
                tmp.push_back(posort.back());
                posort.pop_back();
                if(tmp.size() > 1)
                {
                        for(int j=0; j<tmp.size();j++)
                        {
                                war = Zarzadzanie_CMAX(tmp,maszyny,i+1,maszyny.size());
                                if(min_cmax > war)
                                {
                                        flaga=1;
                                        min_cmax = war;
                                        min_war=war;
                                        min_kolej.erase(min_kolej.begin(),min_kolej.end());
                                        min_kolej.assign(tmp.begin(),tmp.end());
                                }
                                if(j == tmp.size()-1) break;
                                std::swap(tmp[tmp.size()-j-2],tmp[tmp.size()-j-1]);
                        }
                        if(flaga == 1)
                        {
                                tmp.erase(tmp.begin(),tmp.end());
                                tmp.assign(min_kolej.begin(),min_kolej.end());
                                flaga=0;
                                min_cmax=999999;
                        }
                }
        }
        /*std::cout << "Kolejnosc: ";
        print_vec(min_kolej,1);
        std::cout<<std::endl<<"Min CMAX: " << min_war << std::endl;
	*/imp_cmax = min_war;
	return min_kolej;
}

void Zarzadzanie_mod4_NEH(std::vector<Maszyna> maszyny)
{
	std::vector<int> posort = Sumowanie_Zadan(maszyny);
	std::vector<int> min;
	int wlk=posort.size();
	
	int min_cmax=999999,tmp=0;	
	posort.pop_back();

	for(int i=0;i<wlk;i++)
	{
		std::vector<int> min_kolej = mod4_NEH(maszyny, posort, tmp);
		if(min_cmax>tmp)
		{
			min.erase(min.begin(),min.end());
			min.assign(min_kolej.begin(),min_kolej.end());
			min_cmax = tmp;	
		}
		if(i==wlk-1) break;
		std::swap(posort[wlk-2-i],posort[wlk-1]);
	}
	std::cout << "Kolejnosc mod4_NEH: ";
	print_vec(min,1);
	std::cout << " CMAX: " << min_cmax << std::endl;

}

int main()
{
	std::vector<int> wartosci_plik;
	std::vector<Maszyna> maszyny;
	//std::ifstream infile("data/1rand_gen.txt");
	std::ifstream infile("ta010.txt");
	int il_zad, il_masz,wybor;
	std::vector<int> kolej;
	
	Wczytywanie(maszyny,infile, il_zad, il_masz);
	int tab[il_zad];
	
	for(int i=0; i<il_zad; i++)
	{
		tab[i] = i;			
	}

	std::cout << "1.Permutacje\n2.NEH\n3.mod4_NEH\n4.Symulowane wyżarzanie\n5.NEH+SymWyz" << std::endl;
	std::cin >> wybor;
	if(wybor == 1)
	{
		auto start = std::chrono::high_resolution_clock::now();
		permut(il_zad,tab,il_zad,kolej);
		Zarzadzanie_CMAX(kolej, maszyny, il_zad, il_masz);
		auto finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = finish - start;
		std::cout << "Czas Permutacje: " << elapsed.count() << "s\n";
	}
	else if(wybor == 2)
	{
		auto start = std::chrono::high_resolution_clock::now();
		// print_vec(NEH(maszyny),1);
		NEH(maszyny);
		auto finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = finish - start;
		// std::cout << "Cmax NEH: " << Zarzadzanie_CMAX(NEH(maszyny),maszyny,10,3)<<std::endl;
		std::cout << "Czas NEH: " << elapsed.count() << "s\n";
	}
	else if(wybor == 3)
	{
		auto start = std::chrono::high_resolution_clock::now();
		Zarzadzanie_mod4_NEH(maszyny);
		auto finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = finish - start;
		std::cout << "Czas mod4_NEH: " << elapsed.count() << "s\n";
	}
		else if(wybor == 4)
	{
		for (int i = 0; i < 100; ++i)
		{
		
			auto start = std::chrono::high_resolution_clock::now();
			SymWyz(maszyny);
			auto finish = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> elapsed = finish - start;
			std::cout << "Czas: " << elapsed.count() << "s\n";
		
		}
		}
		else if(wybor == 5)
	{
		printf("\nWyżarzanie:");
		auto start = std::chrono::high_resolution_clock::now();
		SymWyz(maszyny);
		auto finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = finish - start;
		std::cout << "Czas: " << elapsed.count() << "s\n";

		
		printf("\nNEH:");
		start = std::chrono::high_resolution_clock::now();
		// print_vec(NEH(maszyny),1);
		finish = std::chrono::high_resolution_clock::now();
		elapsed = finish - start;
		// std::cout << "Cmax NEH: " << Zarzadzanie_CMAX(NEH(maszyny),maszyny,10,3);
		std::cout << " Czas: " << elapsed.count() << "s\n";

	}
	else std::cout<<"Zly znak" << std::endl;
}
