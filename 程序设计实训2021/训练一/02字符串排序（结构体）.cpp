#include <iostream>
#include <string>
#include<algorithm>

using namespace std;

struct zf
{
	string str;
	int wxd ;
	int turn;
};

bool comp(zf a,zf b)
{
	if (a.wxd < b.wxd) return true;
	else if (a.wxd == b.wxd)
	{
		if (a.turn < b.turn) return true;
		else return false;
	}
	else return false;
}

int main()
{
	int n, m;
	char c;
	cin >> n >> m;
	zf a[m];
	for (int i = 0; i < m; i++)
	{
		cin >> a[i].str;
		a[i].wxd = 0;
		a[i].turn = i;
	}
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			c = a[i].str[j];
			for (int k = j + 1; k < n; k++)
			{
				if (c> a[i].str[k]) a[i].wxd++;
			}
		}
	}
	sort(a, a + m, comp);
	for (int i = 0; i < m; i++) cout << a[i].str << endl;
	return 0;
}