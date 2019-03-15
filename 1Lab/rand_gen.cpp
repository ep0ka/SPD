#include<iostream>
#include<fstream>
#include<cstdlib>
#include<ctime>

using namespace std;

int main()
{
	srand((unsigned)time(0));

	int il_masz=3,il_zad=10;
	ofstream file;
	file.open("rand_gen.txt");

	file << il_zad << " " << il_masz << endl;
	
	for(int i=0; i<il_zad; i++)
	{
		for(int j=0; j<il_masz; j++)
		{
			file << rand()%10+1 << " ";
		}
		file << endl;
	}

}
