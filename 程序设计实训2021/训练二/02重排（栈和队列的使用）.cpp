#include<iostream>
#include<stdio.h>
#include<string>
#include<algorithm>
#include<stack>
#include<queue>
using namespace std;

int main()
{
	int n;
	int count=1;
	string temp;
	queue<string> a;
	stack <string> b;
	while (1)
	{
		cin >> n;
		if (n == 0) break;
		
		for (int i = 0; i < n; i++)
		{
			cin >> temp;
			if (i % 2 == 0) a.push(temp);
			else if (i % 2 != 0) b.push(temp);
		}
		temp = to_string(count);
		cout << "set-" << temp << endl;
		while (!a.empty())
		{
			cout << a.front() << endl;
			a.pop();
		}
		while (!b.empty())
		{
			cout << b.top() << endl;
			b.pop();
		}
		count++;
	}
	system("pause");
	return 0;
}