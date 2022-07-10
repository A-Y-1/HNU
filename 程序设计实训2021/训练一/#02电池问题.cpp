#include <iostream>
#include <math.h>
#include <string>
#include <sstream>
using namespace std;

int main()
{
	int n, p1, p2, p3, t1, t2;
	cin >> n >> p1 >> p2 >> p3 >> t1 >> t2;
	int arr[100][2];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 2; j++) cin >> arr[i][j];
	}
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum = sum + (arr[i][1] - arr[i][0])*p1;
		if (i == n - 1) break;
		else
		{
			int time1 = arr[i + 1][0] - arr[i][1];
			if (time1 < t1) sum = sum + time1 * p1;
			else if (time1 > t1&&time1 <= t1+t2) sum = sum + t1 * p1 + (time1 - t1)*p2;
			else if (time1 >= t1+t2) sum = sum + t1 * p1 + t2 * p2 + (time1 - t2-t1)*p3;
		}
	}
	cout << sum;
	system("pause");
	return 0;
}
