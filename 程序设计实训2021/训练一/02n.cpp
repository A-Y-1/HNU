#include <iostream>
#include <math.h>
#include <string>
using namespace std;

int check(int num,int n)
{
	string a = to_string(num);
	string b = to_string(n);
	int pos = a.find(b);
	if (pos == string::npos)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
int main()
{
	int m, n;
	cin>>m;
	cin >> n;
	for (int i = 1; i < m+1; i++)
	{
		if (i%n == 0 || check(i, n) == 1)
		{
			cout << i << " ";
		}
	}
	system("pause");
	return 0;
}
