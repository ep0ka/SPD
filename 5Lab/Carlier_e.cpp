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


/*int cmax(const std::vector<Zadanie> &Zadania)
{
	int q = Zadania[Zadania.size() - 1]._q;
	int r = Zadania[1]._r;
	int p = 0;
	for (int i = 0; i < Zadania.size(); ++i)
	{
		p += Zadania[i]._p;
	}
	return q + r + p;
}*/

int cmax(const std::vector<Zadanie> &Zadania)
{
  int t=0,u=0;

  for (int i=0;i<Zadania.size();i++) 
  { 
  	t=std::max(t,Zadania[i]._r)+Zadania[i]._p;
  	u=std::max(u,t+Zadania[i]._q);
  } 
  return u;
}

int cmax_bez_ost_q(const std::vector<Zadanie> &Zadania, const int size)
{
  int t=0,u=0;

  for (int i=0;i<=size;i++) 
  { 
  	t=std::max(t,Zadania[i]._r) + Zadania[i]._p;
  	u=std::max(u,t/*+Zadania[i]._q*/);
  } 
  return u;
}

int cmax_bez_r_q(const std::vector<Zadanie> &Zadania, int poczatek, const int koniec)
{
	int suma=0;

	for (int i = poczatek; i <= koniec; i++) 
	{
		suma += Zadania[i]._p;
	}
	return suma;
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

std::vector<Zadanie> Shrage(std::vector<Zadanie> TMP)
{
	std::vector<Zadanie> G;
	std::vector<Zadanie> N;
	sort_N(N,TMP);

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
	// std::cout << "Cmax: " << Cmax << "\n";	
	// Wypisz(pi);
	return pi;
}

int prmtShrage(std::vector<Zadanie> TMP)
{
	std::vector<Zadanie> G;
	std::vector<Zadanie> N;
	sort_N(N,TMP);

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
	// std::cout << "Cmax: " << Cmax << "\n";	
	// Wypisz(pi);
	return Cmax;
}
//########################  Carlier  #############################

int znajdz_A(const std::vector<Zadanie> Wekt,int const b) // b - do którego indeksu ma szukać
{
	int Cmax = cmax(Wekt);
	// najmniejsze takie a, czyli trzeba isc od lewej
	for(int a = 0; a <= b; a++)
	{	
		if (Cmax == (Wekt[a]._r + cmax_bez_r_q(Wekt,a,b) + Wekt[b]._q))
		{
			return a;
		}
	}
	return -1;
}

int znajdz_B(const std::vector<Zadanie> Wekt)
{
	for (int i = Wekt.size(); i > 0; --i)
	{
		if(cmax(Wekt) == ( cmax_bez_ost_q(Wekt,i) /*+ Wekt[i]._p*/ + Wekt[i]._q ))
		{
			return i;
		}
	}
	return -1;
}

int znajdz_C(const std::vector<Zadanie> Wekt, const int a, const int b) // a - od którego indeksu ma szukać; b - do którego indeksu ma szukać
{
	int c = -1;
	// najwieksze takie c, czyli trzeba isc od prawej
	for (int i = b; i >= a; i--)
	{
		if (Wekt[i]._q < Wekt[b]._q) 
		{
			c = i;
			break;
		}
	}	
	return c;
}

// Szukanie minimalnego _r w tablicy Wekt, od indeksu "poczatek" do indeksu "koniec"
int minR(const std::vector<Zadanie> Wekt, const int poczatek, const int koniec)
{
	// printf("POCZATEK I KONIEC: %i\t%i",poczatek,koniec);
	int min = 999999999;
	for (int i = poczatek; i <= koniec; i++)
	{
		if(Wekt[i]._r < min)
		{
			min = Wekt[i]._r;
		}
	}
	return min;
}
// Szukanie minimalnego _q w tablicy Wekt, od indeksu "poczatek" do indeksu "koniec"
int minQ(const std::vector<Zadanie> Wekt, const int poczatek, const int koniec)
{
	int min = 999999999;
	for (int i = poczatek; i <= koniec; i++)
	{
		if(Wekt[i]._q < min)
		{
			min = Wekt[i]._q;
		}
	}
	return min;	
}
// Sumowanie _p z tablicy Wekt, od indeksu "poczatek" do indeksu "koniec"
int sumaP(const std::vector<Zadanie> Wekt, const int poczatek, const int koniec)
{
	int suma = 0;
	for (int i = poczatek; i <= koniec; i++)
	{
		suma += Wekt[i]._p;
	}
	return suma;
}

/*int h_od_K(std::vector<Zadanie> Wekt, int pocz, int kon)
{
	int suma = 0;
	for (int i = pocz; i < kon; ++i)
	{
		suma = Wekt[i]._r + Wekt[i]._p + Wekt[i]._q;
	}
	return suma;
}*/

int h_od_K(int a, int b, int c)
{
	return a+b+c;
}


std::vector<Zadanie> Carlier(std::vector<Zadanie> &N)
{
	int LB=-1, UB = 9999999, U = cmax(Shrage(N));
	int A=-1, B=-1, C=-1;
	if (U < UB)
	{
		UB = U;
		N = Shrage(N);
		// printf("TEST");
	}

	B = znajdz_B(N);
	A = znajdz_A(N,B);
	C = znajdz_C(N,A,B);
	if (C == -1)
	{
		// printf("1");
		// return N;
	}
	// printf("WartośćC:%i\n ",C);

//	 K = {c+1, c+2, ... , b}
//	      C+1             B 
//	Zmienne z początkiem "K_" należą do bloku K
//	K_r <- r(K)	;	K_q <- q(K)	;	K_p <- p(K)
	int K_poczatek = C+1, K_koniec = B;
	int K_r = minR(N,K_poczatek,K_koniec), K_q = minQ(N,K_poczatek,K_koniec), K_p = sumaP(N,K_poczatek,K_koniec);
	int K_rc = minR(N,C,K_koniec), K_qc = minQ(N,C,K_koniec), K_pc = sumaP(N,C,K_koniec);
	
	int stare_r = N[C]._r;
	N[C]._r = std::max(N[C]._r, K_r + K_p);

	// printf("POCZATEK CARLIER \t%i\n",K_r);
	LB = prmtShrage(N);
	// LB = std::max(h_od_K(N,K_poczatek,K_koniec),std::max(h_od_K(N,K_poczatek-1,K_koniec),LB));//????
	// LB = std::max(h_od_K(K_r, K_q, K_p),std::max(h_od_K(K_rc, K_qc, K_pc),LB));//????
	// LB = std::max(h_od_K(minR(N,K_poczatek,K_koniec), minQ(N,K_poczatek,K_koniec), sumaP(N,K_poczatek,K_koniec)),std::max(h_od_K(minR(N,K_poczatek-1,K_koniec), minQ(N,K_poczatek-1,K_koniec), sumaP(N,K_poczatek-1,K_koniec)),LB));//????

	if(LB <= UB)
	{
		// printf("2");
		Carlier(N);
		return N;
	}
	N[C]._r = stare_r;

		// printf("TEST");
	int stare_q = N[C]._q;
	N[C]._q = std::max(N[C]._q, K_q + K_p);

	LB = prmtShrage(N);
	// printf("LB TEST:%i\n",LB);
	// LB = std::max(h_od_K(N,K_poczatek,K_koniec),std::max(h_od_K(N,K_poczatek-1,K_koniec),LB));//????
	// LB = std::max(h_od_K(K_r, K_q, K_p),std::max(h_od_K(K_rc, K_qc, K_pc),LB));//????
	// LB = std::max(h_od_K(minR(N,K_poczatek,K_koniec), minQ(N,K_poczatek,K_koniec), sumaP(N,K_poczatek,K_koniec)),std::max(h_od_K(minR(N,K_poczatek-1,K_koniec), minQ(N,K_poczatek-1,K_koniec), sumaP(N,K_poczatek-1,K_koniec)),LB));
	if(LB < UB)
	{
		// printf("3");
		// return N;
		Carlier(N);
	}
	N[C]._q = stare_q;
	return N;
}

//#################################################################


int main()
{
	std::vector<Zadanie> tmp0;
	std::vector<Zadanie> tmp1;
	std::vector<Zadanie> tmp2;
	std::vector<Zadanie> tmp3;
	std::vector<Zadanie> tmp4;
	std::vector<Zadanie> tmp5;
	std::vector<Zadanie> tmp6;
	std::vector<Zadanie> tmp7;
	std::vector<Zadanie> tmp8;
	std::vector<Zadanie> tmp9;
	std::vector<Zadanie> tmp10;
	std::vector<Zadanie> tmp11;
	// std::ifstream infile("makuch_test_inst.txt"); //instancje/in50.txt
	// std::ifstream infile("instancje/data.006"); 
	// std::chrono::duration<double> elapsed;
	// auto start = std::chrono::high_resolution_clock::now();
	// auto finish = std::chrono::high_resolution_clock::now();

	std::ifstream infile1("instancje/in50.txt"); 
	Wczytywanie(tmp1, infile1);
	printf("Carlier:\t%i\t1492\n", cmax(Carlier(tmp1)));

	std::ifstream infile2("instancje/in100.txt"); 
	Wczytywanie(tmp2, infile2);
	printf("Carlier:\t%i\t3070\n", cmax(Carlier(tmp2)));

	std::ifstream infile3("instancje/in200.txt"); 
	Wczytywanie(tmp3, infile3);
	printf("Carlier:\t%i\t6398\n", cmax(Carlier(tmp3)));

	std::ifstream infile0("instancje/data.000"); 
	Wczytywanie(tmp0, infile0);
	printf("Carlier:\t%i\t228\n", cmax(Carlier(tmp0)));

	std::ifstream infile4("instancje/data.001"); 
	Wczytywanie(tmp4, infile4);
	printf("Carlier:\t%i\t3026\n", cmax(Carlier(tmp4)));

	std::ifstream infile5("instancje/data.002"); 
	Wczytywanie(tmp5, infile5);
	printf("Carlier:\t%i\t3665\n", cmax(Carlier(tmp5)));

	std::ifstream infile6("instancje/data.003"); 
	Wczytywanie(tmp6, infile6);
	printf("Carlier:\t%i\t3309\n", cmax(Carlier(tmp6)));

	std::ifstream infile7("instancje/data.004"); 
	Wczytywanie(tmp7, infile7);
	printf("Carlier:\t%i\t3191\n", cmax(Carlier(tmp7)));

	std::ifstream infile8("instancje/data.005"); 
	Wczytywanie(tmp8, infile8);
	printf("Carlier:\t%i\t3618\n", cmax(Carlier(tmp8)));

	std::ifstream infile9("instancje/data.006"); 
	Wczytywanie(tmp9, infile9);
	printf("Carlier:\t%i\t3446\n", cmax(Carlier(tmp9)));

	std::ifstream infile10("instancje/data.007"); 
	Wczytywanie(tmp10, infile10);
	printf("Carlier:\t%i\t3821\n", cmax(Carlier(tmp10)));

	std::ifstream infile11("instancje/data.008"); 
	Wczytywanie(tmp11, infile11);
	printf("Carlier:\t%i\t3634\n", cmax(Carlier(tmp11)));

	// printf("wielkosc:%i\n", (int)tmp.size());
	// printf("cmax_bez:%i\n",cmax_bez_r_q(tmp,1,4));//,2));
	// printf("Indeks B:%i\n", znajdz_B(tmp));
	// printf("Indeks A:%i\n", znajdz_A(tmp, znajdz_B(tmp)));
	// printf("Indeks C:%i\n", znajdz_C(tmp, znajdz_A(tmp,znajdz_B(tmp)), znajdz_B(tmp)));

	// tmp = Shrage(tmp);
	// tmp = prmtShrage(tmp);
	// printf("Carlier:%i\n", cmax(Shrage(tmp)));


	return 1;
}
