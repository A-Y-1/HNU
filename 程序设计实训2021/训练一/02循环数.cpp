#include <iostream>
#include <math.h>
#include <string>
#include <sstream>
using namespace std;

int check(string n, string nn)
{
	string a = nn + nn;
	string::size_type b = a.find(n);
	if (b != string::npos)
	{
		return 1;
	}
	else return 0;
}
int main()
{
	string str;
	cin >> str;
	int l = str.length();
	int num = 0;
	for (int i = 0; i < l; i++)
	{
		num = num + (str[i] - '0')*pow(10, l - i - 1);
	}
	int count = 0;
	for (int j = 1; j < l+1; j++)
	{
		int num2 = num * j;;
		string restr = to_string(num2);
		int lnew = 0; 
		lnew = restr.length();
		while(lnew < l)
		{
			restr = "0" + restr;
			lnew++;
		}
		if (check(str, restr) == 1)
		{
			count++; 
		}
		else;
		
	}
	if (count == l) cout << "Yes";
	else cout << "No";
	system("pause");
	return 0;
}
