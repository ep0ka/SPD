#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

void permut(int n, int A[], const int wlk, vector<int>& kolej)
{
	if(n == 1)
	{
		for(int j=0; j<wlk; j++)
		{
			cout << A[j];
			kolej.push_back(A[j]);
		}
		return;
	}
	else
	{
		permut(n-1,A,wlk,kolej);
		for(int i=0; i < n-1; i++)
		{
			if(n%2 == 0) swap(A[i],A[n-1]);
			else swap(A[0],A[n-1]);	
			permut(n-1,A,wlk,kolej);
		}		
	}

}

int main()
{
	int wlk = 3;
	int tab[]={1,2,3};
	vector<int> kolej;
	permut(wlk,tab,wlk,kolej);
}
