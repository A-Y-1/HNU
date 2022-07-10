#include <iostream>
#include <math.h>
#include <string>
#include <stdio.h>
using namespace std;

int main()
{
	while (1)
	{
		float x1 = 0, y1 = 0, x2 = 0, y2 = 0, x3 = 0, y3 = 0;
		cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
		if (x1 == 0 && y1 == 0 && x2 == 0 && y2 == 0 && x3 == 0 && y3 == 0) break;
		float s = 0;
		s = (0.5)*(x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2));
		s = fabs(s);
		printf("%.6f", s);
		cout << endl;
	}
	system("pause");
	return 0;
}
