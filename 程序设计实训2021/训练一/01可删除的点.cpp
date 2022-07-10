#include <iostream>
using namespace std;
int main()
{
	int n;
	cin >> n;
	int arr[100000];
	for (int i = 0; i < n; i++)
	{
		int x;
		cin >> arr[i];
		cin >> x;
	}
	int z = 0;
	int f = 0;
	for (int i = 0; i < n; i++)
	{
		if (arr[i] < 0)
		{
			f+=1;
		}
		else
		{
			z += 1;
		}
	}
	if (z >= n-1||f>=n-1)      //k考虑给出的点已经都在y轴一侧的情况符合题意
	{
		cout << "Yes";
	}
	else cout << "No";

	return 0;
}

