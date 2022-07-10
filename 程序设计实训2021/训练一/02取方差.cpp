#include <iostream>
#include <math.h>
using namespace std;

float ave(int arr[], float n)
{
	float a = 0;
	float sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum = sum + arr[i];
	}
	a = sum / n;
	return a;
}


int main()
{
	while (1)
	{
		float n = 0;
		int arr[10000];
		cin >> n;
		if (n == 0)
		{
			break;
		}
		for (int i = 0; i < n; i++)
		{
			cin >> arr[i];
		}
		float a = ave(arr, n);//aÎª¾ùÖµ
		float sum = 0;
		for (int i = 0; i < n; i++)
		{
			sum = sum + (arr[i] - a)*(arr[i] - a);
		}
		float result = sum / n;
		cout << floor(result) << endl;
	}
	system("pause");
	return 0;
}