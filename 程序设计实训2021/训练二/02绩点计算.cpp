#include<math.h>
#include<iostream>
#include<algorithm>
#include<stdio.h>
using namespace std;




int main()
{
	int n,sum;
	float temp;
	sum = 0;
	cin >> n;
	int a[100];
	float result=0;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
		sum = sum + a[i];
	}
	for (int j = 0; j < n; j++)
	{
		cin >> temp;
		if (temp >= 90) temp = 4.0;
		else if (temp >= 85) temp = 3.7;
		else if (temp >= 82) temp = 3.3;
		else if (temp >= 78) temp = 3.0;
		else if (temp >= 75) temp = 2.7;
		else if (temp >= 72) temp = 2.3;
		else if (temp >= 68) temp = 2.0;
		else if (temp >= 64) temp = 1.5;
		else if (temp >= 60) temp = 1.0;
		else  temp =0;
		result += temp * a[j] / sum;
	}
	printf("%.2f", result);
	cout << endl;
	return 0;
}