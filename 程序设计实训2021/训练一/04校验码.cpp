#include<iostream>
#include<cmath>
using namespace std;
int main() {
	int n; cin >> n;
	int x; string y;
	for (int i = 0; i < n; i++) {
		cin >> x >> y;
		int l = y.length(), t = 0;
		for (int j = 0; j < l; j++) {
			if (y[j] >= '0'&&y[j] <= '9')
				t += y[j] - '0';
			else
				t += y[j] - '0' - 39;
		}
		int yu = t % (x - 1);
		if (yu != 0)
			yu = x - yu - 1;			
		if (yu < 10) {
			cout << yu << endl;
		}
		else {
			char a = yu + 87;
			cout << a << endl;
		}
	}
}
