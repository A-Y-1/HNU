#include<iostream>
#include<stdio.h>
#include<string>
#include <algorithm>
using namespace std;

struct team {
	string name = "0";   //��һ����ʼ������������ж��Ƿ��Ѿ���������
	int purescore;
	int points;
};

bool comp(team x, team y)
{
	if (x.points > y.points) return true;
	else if (x.points == y.points)
	{
		if (x.purescore > y.purescore) return true;
		else if (x.purescore == y.purescore) return false;		//�������ʱ�����ȱ��뷵��false
		else return false;
	}
	else if (x.points < y.points) return false;
}
int main()
{
	int T; cin >> T;
	for (int k = 0; k < T; k++) {
		team x[12], y[12], z[4];
		for (int i = 0; i < 12; i++) {
			int a = 0, b = 0; string c;
			cin >> x[i].name >> a >> c >> b >> y[i].name;
			if (a > b) {
				x[i].points = 3; x[i].purescore = a - b; y[i].purescore = b - a; y[i].points = 0;
			}
			if (a == b) {
				x[i].points = 1; y[i].points = 1; x[i].purescore = 0; y[i].purescore = 0;
			}
			if (a < b) {
				y[i].points = 3; y[i].purescore = b - a; x[i].purescore = a - b; x[i].points = 0;
			}//ÿһ�Ҫ���룬����ΪĬ��ֵ
		}
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 4; j++) {
				if (z[j].name == "0") {
					z[j].name = x[i].name;
					z[j].points = x[i].points;
					z[j].purescore = x[i].purescore;
					break;
				}
				else if (z[j].name != "0"&&z[j].name == x[i].name) {
					z[j].points += x[i].points;
					z[j].purescore += x[i].purescore;
					break;
				}
				else if (z[j].name != "0"&&z[j].name != x[i].name) {
					continue;
				}
			}
		}
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 4; j++) {
				if (z[j].name == "0") {
					z[j].name = y[i].name;
					z[j].points = y[i].points;
					z[j].purescore = y[i].purescore;
					break;
				}
				else if (z[j].name != "0"&&z[j].name == y[i].name) {
					z[j].points += y[i].points;
					z[j].purescore += y[i].purescore;
					break;
				}
				else if (z[j].name != "0"&&z[j].name != y[i].name) {
					continue;
				}


			}
		}
		sort(z, z + 4, comp);
		cout << z[0].name << " " << z[1].name << endl;
	}
	system("pause");
	return 0;
}