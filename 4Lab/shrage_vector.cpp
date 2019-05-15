#include<iostream>
#include<algorithm>
#include<fstream>
#include<vector>
#include<chrono>

struct Zadanie{
	int _nr_zad = -1;
	int _r = -1;
	int _p = -1;
	int _q = -1;
};

void Wczytywanie(std::vector<Zadanie> &Zadania, std::ifstream& infile)
{
	int zad_aktualne, nr_masz=0, tmp=0, il_zad=-1;
	infile >> il_zad;
	// infile >> zad_aktualne; //Linijka przez format wczytywanych danych, dwie kolumny w pierwszym wersie
	for(int i=0; i<il_zad; i++)
	{
		Zadania.push_back(Zadanie());
		Zadania[i]._nr_zad = i;
		for(int j=0; j<3;j++)
		{
			switch(j % 3)
			{
				case 0:
				infile >> Zadania[i]._r;
				break;
				case 1: 
				infile >> Zadania[i]._p;
				break;
				case 2: 
				infile >> Zadania[i]._q;
				break;
				default:
				break;
			}
		}

	}
}

// void Wpisanie_N()


int cmax(const std::vector<Zadanie> &Zadania)
{
	int q = Zadania[Zadania.size() - 1]._q;
	int r = Zadania[1]._r;
	int p = 0;
	for (int i = 0; i < Zadania.size(); ++i)
	{
		p += Zadania[i]._p;
	}
	return q + r + p;
}


void Wypisz(const std::vector<Zadanie> &Zadania)
{
	// printf("%i\n", (int)Zadania.size());
	for (int i = 0; i < Zadania.size(); ++i)
	{
		printf("%i %i %i\n", Zadania[i]._r, Zadania[i]._p, Zadania[i]._q);
	}
	printf("\n");
}

void sort_N(std::vector<Zadanie> &Wynik, std::vector<Zadanie> &Dane_z_pliku)//int r, int p, int q, int nr_zad)
{
	Zadanie tmp;
	int iterator = -1;
	
	while(Dane_z_pliku.size() != 0)
	{
		tmp._r = 0;
		for(int i = 0; i<Dane_z_pliku.size(); i++)
		{
			if (Dane_z_pliku[i]._r >= tmp._r)
			{
				tmp = Dane_z_pliku[i];
				iterator = i;
			}
		}
	Dane_z_pliku[iterator] = Dane_z_pliku[Dane_z_pliku.size()-1];
	Dane_z_pliku.pop_back();
	Wynik.push_back(tmp);
	}
}

/*void sort_G(std::vector<Zadanie> &G)
{
	std::vector<Zadanie> tmp = G;
	Zadanie min;
	int iterator = -1, it_G = 0;

	while(tmp.size() != 0)
	{
		min._q = 999999;
		for(int i = 0; i<tmp.size(); i++)
		{
			if (tmp[i]._q <= min._q)
			{
				min = tmp[i];
				iterator = i;
			}
		}
	tmp[iterator] = tmp[tmp.size()-1];
	tmp.pop_back();
	G[it_G]=min;
	it_G++;
	}
	Wypisz(G);
}*/

void sort_G(std::vector<Zadanie> &G)
{
	Zadanie max;
	max._q = -1;
	int iterator = -1;

	// Wypisz(G);

	for(int i = 0; i<G.size(); i++)
	{
		if (G[i]._q >= max._q)
		{
			max = G[i];
			iterator = i;
		}
	}	
	G[iterator] = G[G.size()-1];
	G[G.size()-1] = max;

	// Wypisz(G);
}

void insert_G(std::vector<Zadanie> &G, std::vector<Zadanie> &N)
{
	G.push_back(N[N.size()-1]);
	N.pop_back();
}

void insert_PI(std::vector<Zadanie> &PI, std::vector<Zadanie> &G)
{
	PI.push_back(G[G.size()-1]);
	G.pop_back();
}

std::vector<Zadanie> Shrage(std::vector<Zadanie> N, std::vector<Zadanie> G)
{
	std::vector<Zadanie> pi;
	Zadanie tmp;
	int t=0,Cmax=0;

	while(G.size() != 0 || N.size() != 0)
	{
		while(N.size() != 0 && N[N.size()-1]._r <= t)
		{
			insert_G(G,N);
			// std::cout<<"Wypisanie G:\n"<<std::endl;
			// Wypisz(G);
			// sort_G(G);
		}

		if(G.size() == 0) 
		{
			t = N[N.size()-1]._r;

		}
		else
		{
			sort_G(G);
			insert_PI(pi,G);

			t += pi[pi.size()-1]._p;
			Cmax = std::max(Cmax,t+pi[pi.size()-1]._q);
		}

	}
	std::cout << "Cmax: " << Cmax << "\n";	
	// Wypisz(pi);
	return pi;
}

std::vector<Zadanie> prmtShrage(std::vector<Zadanie> N, std::vector<Zadanie> G)
{
	std::vector<Zadanie> pi;
	Zadanie tmp, l;
	l._q = 9999999;
	int t=0,Cmax=0;

	while(G.size() != 0 || N.size() != 0)
	{
		while(N.size() != 0 && N[N.size()-1]._r <= t)
		{
			insert_G(G,N);
			// tmp = N[N.size()-1];
			// N.pop_back();
			// G.push_back(tmp);
			if(G[G.size()-1]._q > l._q)
			{
				l._p = t-G[G.size()-1]._r;
				t = G[G.size()-1]._r;
				if(l._p > 0)
				{
					G.push_back(l);
					sort_G(G);
				}
			}	
		}

		if(G.size() == 0) 
		{
			t = N[N.size()-1]._r;
			// std::cout << "ECHO ECHO " << t << std::endl;
			// continue;
		}
		else
		{
			// Wypisz(G);
			sort_G(G);
			l = G[G.size()-1];
			insert_PI(pi,G);
			t += pi[pi.size()-1]._p;
			Cmax = std::max(Cmax,t+pi[pi.size()-1]._q);
		}

	}
	std::cout << "Cmax: " << Cmax << "\n";	
	// Wypisz(pi);
	return pi;
}




int main()
{
	std::vector<Zadanie> tmp;
	std::vector<Zadanie> N;
	std::vector<Zadanie> G;
	std::ifstream infile("instancje/in50.txt");
	std::chrono::duration<double> elapsed;
	auto start = std::chrono::high_resolution_clock::now();
	auto finish = std::chrono::high_resolution_clock::now();


	Wczytywanie(tmp, infile);
	sort_N(N,tmp);
	// for (int i = 0; i < 10; ++i)
	// {
	start = std::chrono::high_resolution_clock::now();
	Shrage(N,G);
	finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    std::cout /*<< "Czas: "*/ << elapsed.count() << "\n";
	// }

	std::cout << std::endl << std::endl;

	// for (int i = 0; i < 10; ++i)
	// {
    start = std::chrono::high_resolution_clock::now();
	prmtShrage(N,G);
	finish = std::chrono::high_resolution_clock::now();
	elapsed = finish - start;
    std::cout /*<< "Czas: "*/ << elapsed.count() << "\n";
	// }
	return -1;
}
