#include<iostream>
#include<stdio.h>
#include<string>
#include<algorithm>
#include<stack>
using namespace std;

int main()
{
	int n;
	cin >> n;
	string x, y;
	int a[6] = {0,0,0,0,0,0};
	int	b[6] = {0,0,0,0,0,0};//数组内0胜1平2负3锤4剪5布
	for (int i = 0; i < n; i++)
	{
		cin >> x >> y;
		if (x == "C"&&y == "J")
		{
			a[0] += 1;
			b[2] += 1;
			a[3] += 1;
		}
		else if (x == "B"&&y == "J")
		{
			a[2] += 1;
			b[0] += 1;
			b[4] += 1;
		}
		else if (x == "J"&&y == "B")
		{
			a[0] += 1;
			b[2] += 1;
			a[4] += 1;
		}
		else if (x == "C"&&y == "B")
		{
			a[2] += 1;
			b[0] += 1;
			b[5] += 1;
		}
		else if (x == "J"&&y == "C")
		{
			a[2] += 1;
			b[0] += 1;
			b[3] += 1;
		}
		else if (x == "B"&&y == "C")
		{
			a[0] += 1;
			b[2] += 1;
			a[5] += 1;
		}
		else if (x == y)
		{
			a[1] += 1;
			b[1] += 1;
		}
	}
	if (a[3] > a[4] && a[3] > a[5]) x = "C";
	else if (a[4] > a[5] && a[4] > a[3]) x = "J";
	else if (a[5] > a[4] && a[5] > a[3]) x = "B";
	else if (a[5] == a[4] && a[5] > a[3]) x = "B";
	else if (a[3] == a[4] && a[4] > a[5]) x = "C";
	else if (a[5] == a[3] && a[5] > a[4]) x = "B";
	else if (a[5] == a[3] && a[5] == a[4]) x = "B";
	if (b[3] > b[4] && b[3] > b[5]) y = "C";
	else if (b[4] > b[5] && b[4] > b[3]) y = "J";
	else if (b[5] > b[4] && b[5] > b[3]) y = "B";
	else if (b[5] == b[4] && b[5] > b[3]) y = "B";
	else if (b[3] == b[4] && b[4] > b[5]) y = "C";
	else if (b[5] == b[3] && b[5] > b[4]) y = "B";
	else if (b[5] == b[3] && b[5] == b[4]) y = "B";
	cout << a[0] << " " << a[1] << " " << a[2] << endl;
	cout << b[0] << " " << b[1] << " " << b[2] << endl;
	cout << x <<  " " << y << endl;

	system("pause");
	return 0;
}