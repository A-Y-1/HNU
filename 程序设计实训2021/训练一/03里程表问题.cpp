#include<iostream>
#include<string>
#include<sstream>
using namespace std;
int main() {
	int n, i, j, l;
	stringstream ss;
	cin >> n;
	string s;
	string a[100000];
	int b[100000];
	for (i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (i = 0; i < n; i++) {
		s = a[i];
		l = s.length();
		for (j = 0; j < l; j++) {
			switch (s[j]) {//因为3,8会跳过，算出实际8进制应该显示的数 
			case '4':
				s[j] = '3';
				break;
			case '5':
				s[j] = '4';
				break;
			case '6':
				s[j] = '5';
				break;
			case '7':
				s[j] = '6';
				break;
			case '9':
				s[j] = '7';
				break;
			}
		}
		ss.clear();//stringstream用之前先清空 
		ss << oct << s;//八进制转10进制 
		ss >> b[i];
		cout << b[i] << endl;


	}

	return 0;
}
