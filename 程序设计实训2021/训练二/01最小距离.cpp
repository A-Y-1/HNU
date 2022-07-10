#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;

struct number {
	int num = 0;
	int dis = 0;

};

bool comp(number a,number b)
{
	if (a.dis < b.dis) return true;
	else if (a.dis == b.dis)
	{
		if (a.num < b.num) return true;
		else return false;
	}
	else return false;
}

int main()
{
	int n;
	number a[1000];
	int b[1000];
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i].num;
		b[i] = a[i].num;
	}
	int max, min;
	sort(b, b + n);
	max = b[n-1];
	min = b[0];
	for (int i = 0; i < n; i++)
	{
		a[i].dis = abs(abs(a[i].num - max) - abs(a[i].num - min));
	}
	sort(a, a + n, comp);
	cout << a[0].num;

	return 0;
}