#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;




int main()
{
	int n,count;
	while (1)
	{
		cin >> n;
		if (n == 0) break;
		count = 0;
		while (n != 1)
		{
			if (n % 2 == 0) n = n / 2;
			else n = (3 * n + 1) / 2;
			count++;
		}
		cout << count << endl;
	}
	return 0;
}