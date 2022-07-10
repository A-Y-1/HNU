#include<iostream>
#include<stack>
#include<string>
using namespace std;
int main() {
	int n,len;
	stack <string> temp;
	int t1, t2,s;
	cin >> n;
	string a, b, c ;
	for (int i = 0; i < n; i++)
	{
		cin>>a>>b;
		len = a.length();
		t1 = 0, t2 = 0;
		for (int j = 0; j < len; j++)
		{
			t1 = t1 * 26 + a[j] - 'a';
		}
		len = b.length();
		for (int j = 0; j < len; j++)
		{
			t2 = t2 * 26 + b[j] - 'a';
		}
		s = t1 + t2;
		while (s / 26 != 0)
		{
			c = s % 26 + 'a';
			temp.push(c);
			s = s / 26;
		}
		c = s + 'a';
		temp.push(c);
		while (!temp.empty())
		{
			cout << temp.top();
			temp.pop();
		}
		cout << endl;
	}
	return 0;
}
