#include <iostream>
#include <stdio.h>
using namespace std;


int main()
{	
	while (1)
	{
		int n;
		int zs = 0;
		cin >> n;
		if (n == 0)
		{
			break;
		}
		int arr[10000];
		for (int i = 0; i < n; i++)
		{
			cin >> arr[i];
		}
		int s = 0;
		zs = 0;
		for (int i = 0; i < n; i++)
		{
			int k = arr[i];
			int count = 0;
			for (int j = 0; j < n; j++)
			{ 
				if (k == arr[j])
				{
					count+=1;
				}
				else;
			}
			if (count > s )
			{
				s = count;
				zs = arr[i];
			}
			if (s > (n / 2))
			{
				break;
			}
		}
		cout << zs<<endl;
	}
	return 0;
}