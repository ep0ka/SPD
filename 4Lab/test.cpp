#include<iostream>
#include<algorithm>
#include<fstream>
#include<vector>
#include<cmath>
#include<chrono>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>
#include<ctime>

struct Zadanie{
	int _r = -1;
	int _p = -1;
	int _q = -1;
	int _nr_zad = -1;
	Zadanie *_wsk;
};

class Queue{

	private:
		Zadanie *head;
	public:
		Queue() { head = nullptr; }
		~Queue() { delete head; }
		void insert_N(int r, int p, int q, int nr_zad)
		{
			//r jest priorytetem
			Zadanie *tmp, *prio;
			tmp = new Zadanie;
			tmp->_p = p;
			tmp->_r = r;
			tmp->_q = q;
			tmp->_nr_zad = nr_zad;
			if( head == nullptr || r < head->_r)
			{
				tmp->_wsk = head;
				head = tmp;
			}
			else
			{
				prio = head;
				while(prio->_wsk != nullptr && prio->_wsk->_r <= r)
				{	
					prio = prio->_wsk;
				}
				tmp->_wsk = prio->_wsk;
				prio->_wsk = tmp;
			}
		}

		void insert_G(Zadanie *zad)
		{
			//q jest priorytetem
			int q = zad->_q;
			Zadanie *tmp, *prio;
			tmp = new Zadanie;
			tmp->_p = zad->_p;
			tmp->_r = zad->_r;
			tmp->_q = zad->_q;
			tmp->_nr_zad = zad->_nr_zad;
			if( head == nullptr || q > head->_q)
			{
				tmp->_wsk = head;
				head = tmp;
			}
			else
			{
				prio = head;
				while(prio->_wsk != nullptr && prio->_wsk->_q >= q)
				{	
					prio = prio->_wsk;
				}
				tmp->_wsk = prio->_wsk;
				prio->_wsk = tmp;
			}
		}


		void del_front()
		{
			//std::cout << "Delete_front\n";
			Zadanie *tmp;
			if(head == nullptr) std::cout << "Lista jest pusta\n";
			else
			{
				tmp = head;
				//std::cout << "Usunieto element " << head->_nr_zad << "\n";
				head = head->_wsk;
				delete tmp;
			}
		}

		void show()
		{
			Zadanie *tmp;
			tmp = head;
			if(head == nullptr) std::cout << "Lista jest pusta\n";
			else
			{
				std::cout<<"Queue: ";
				while(tmp != nullptr)
				{
					std::cout<<tmp->_nr_zad<<" ";
					tmp = tmp->_wsk;
				}
				std::cout<<"\n";
			}
		}

		bool no_empty()
	       	{
			if(head == nullptr) return false;
			else return true;
		}

		Zadanie *get_head() {return head;}

};

void print_vec(std::vector<Zadanie> vec,int a)
{
        printf("\n");
        for(unsigned int i=0; i<vec.size(); i++)
        {
                std::cout<<vec[i]._nr_zad+a << ", ";
        }
}


void Wczytywanie_nieuporzadkowane(Queue &que, std::ifstream& infile)
{
	int il_zad=-1,r=-1,p=-1,q=-1;
	infile >> il_zad;
	for(int i=1; i<=il_zad; i++)
	{
		infile >> r >> p >> q;
	  	que.insert_N(r,p,q,i);		
	}
}


void dodaj_zad(Zadanie* wsk_zad,std::vector<Zadanie> &pi)
{
	Zadanie zad;

	zad._r = wsk_zad->_r;
	zad._p = wsk_zad->_p;
	zad._q = wsk_zad->_q;
	zad._nr_zad = wsk_zad->_nr_zad;
	pi.push_back(zad);
}

std::vector<Zadanie> Shrage(Queue que_N, Queue que_G)
{
	std::vector<Zadanie> pi;
	int t=0,Cmax=0;

	while(que_G.no_empty() || que_N.no_empty())
	{
		while(que_N.no_empty() && que_N.get_head()->_r <= t)
		{
			que_G.insert_G(que_N.get_head());
			que_N.del_front();
			/*std::cout << "\nStart\n";
			que_N.show();
			que_G.show();
			std::cout << "Stop\n\n";
			*/
		}

		if(que_G.no_empty() == false) 
		{
			t = que_N.get_head()->_r;
			continue;
		}
		dodaj_zad(que_G.get_head(),pi);
		t += que_G.get_head()->_p;
		Cmax = std::max(Cmax,t+que_G.get_head()->_q);
		que_G.del_front();
	}
	std::cout << "Cmax: " << Cmax << "\n";	
	return pi;
}


Zadanie* insert_l(Zadanie *g)
{
	Zadanie *l;
	l = new Zadanie;

	l->_p = g->_p;
	l->_r = g->_r;
	l->_q = g->_q;
	l->_nr_zad = g->_nr_zad;

	return l;
}

std::vector<Zadanie> prmtShrage(Queue que_N, Queue &que_G)
{
	std::vector<Zadanie> pi;
	int t=0,Cmax=0;
	Zadanie *l = new Zadanie;
	l->_q = 9999999;


	while(que_G.no_empty() || que_N.no_empty())
	{
		while(que_N.no_empty() && que_N.get_head()->_r <= t)
		{
			que_G.insert_G(que_N.get_head());
			que_N.del_front();
			/*std::cout << "\nStart\n";
			que_N.show();
			que_G.show();
			std::cout << "Stop\n\n";
			*/

			if(que_G.get_head()->_q > l->_q)
			{
				l->_p = t-que_G.get_head()->_r;
				
				t = que_G.get_head()->_r;
				if(l->_p > 0) 
				{	
					que_G.insert_G(l);
				}
			}
		}

		if(que_G.no_empty() == false) 
		{
			t = que_N.get_head()->_r;
			continue;
		}
		l = insert_l(que_G.get_head());
		t += que_G.get_head()->_p;
		Cmax = std::max(Cmax,t+que_G.get_head()->_q);
		que_G.del_front();
	}
	std::cout << "Cmax: " << Cmax << "\n";	
	return pi;
}

int main()
{
	std::ifstream infile("in50.txt");

	Queue que_N, que_G;

	Wczytywanie_nieuporzadkowane(que_N, infile);

	//que_N.show();

        auto start = std::chrono::high_resolution_clock::now();
	//print_vec(Shrage(que_N,que_G),0);
	// prmtShrage(que_N,que_G);
	Shrage(que_N,que_G);
	auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = finish - start;
        std::cout << "Czas: " << elapsed.count() << "s\n";
	return -1;
}
