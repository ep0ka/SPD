#include <iostream>
#include <fstream>
#include <string>

int main () 
{
	srand(time(NULL));
	int il_zad = -1;
	std::string nazwa_pliku;
	printf("Podaj liczbę zadań: ");
	std::cin >> il_zad;
	printf("Podaj nazwę pliku: ");
	std::cin >> nazwa_pliku;

	// ofstream myfile;
	std::ofstream plik(nazwa_pliku.c_str(), std::ios::out | std::ios::trunc);
	// myfile.open ("example.txt");
	// myfile << "Writing this to a file.\n";
	// myfile.close();
	plik << il_zad << " " << "3" << std::endl;
	for (int i = 0; i < il_zad; ++i)
	{
		plik << rand()%2000 << " " << rand()%2000 << " " << rand()%2000 << std::endl;

	}
	return 0;
}