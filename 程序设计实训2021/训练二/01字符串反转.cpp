#include<iostream>
#include<stdio.h>
#include<string>
#include<algorithm>
#include<stack>
using namespace std;

int main()
{
	string a;
	int len, k;
	stack <string> b;
	
	while (getline(cin, a))  //while形式判断输入流有效
	{
		
		len = a.length();
		k = 0;
		for (int i = 0; i < len; i++)
		{
			if (a[i] == ' ')
			{
				b.push(a.substr(k, i - k));
				k = i + 1;
			}
			else if (i == len - 1) b.push(a.substr(k, i - k + 1));
			else continue;
		}
		while (!b.empty())
		{
			cout << b.top() << " ";
			b.pop();
		}

		cout << endl;
	}
	system("pause");
	return 0;
}