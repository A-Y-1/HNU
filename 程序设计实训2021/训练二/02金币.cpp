#include<iostream>
#include<math.h>
#include<string>
#include<algorithm>
#include<stack>
#include<queue>
using namespace std;


int main()
{
	int a, b;
	int s1, s2;
	while (1)
	{
		cin >> a >> b;
		for (int i = 1; i < a; i++)
		{
			if (a%i == 0) s1 = s1 + i;
		}
		for (int i = 1; i < b; i++)
		{
			if (b%i == 0) s2 = s2 + i;
		}
		if (s1 == b && s2 == a) cout << "Yes" << endl;
		else cout << "No" << endl;
	}
	system("pause");
	return 0;
}