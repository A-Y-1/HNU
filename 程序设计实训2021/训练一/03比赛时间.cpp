#include<iostream>
#include<stdio.h>
#include<string>
using namespace std;
int main()
{
	int n;
	string day[] = { "monday","tuesday","wednesday","thursday","friday","saturday", "sunday" };
	cin >> n;
	int min, max;
	int d1 = 0;
	int d2 = 0;
	for (int i = 0; i < n; i++)
	{
		
		string a, b;
		cin >> a >> b;
		cin >> min >> max;
		for (int j = 0; j < 7; j++)
		{
			if (a == day[j])
				d1 = j + 1;
		}
		for (int j = 0; j < 7; j++)
		{
			if (b == day[j])
				d2 = j + 1;
		}
		int x, y;
		if (d1 < d2) d1=d1 + 7;
		x = d2 - d1 + 1;
		while (x < min) x += 7;  //x是一周的情况，+7到达时间范围再判断
		y = x + 7;
		if ((x >= min && x <= max) && (y >= min && y <= max))
		{
			cout << "many" << endl;

		}
		else if (x >= min && x <= max && y > max)//
		{
			cout << x << endl;
		}
		else if (x < min || x > max)
		{
			cout << "impossible" << endl;
		}
	}

	system("pause");
	return 0;
}