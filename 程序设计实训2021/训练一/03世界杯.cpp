#include<iostream>
#include<stdio.h>
#include<string>
#include<algorithm>
using namespace std;

//结构体，队伍和参赛信息
struct team 
{
	string name="null";
	int points=0;
	int purescore=0;
	int score=0;
};

//排序规则
bool comp(team a, team b)
{
	if (a.points == b.points)
	{
		if (a.purescore == b.purescore)
		{
			if (a.score == b.score || a.score<b.score) return false;
			else if (a.score > b.score) return true;
		}
		else if (a.purescore > b.purescore) return true;
		else return false;
	}
	else if (a.points > b.points) return true;
	else return false;
}
bool comp1(team a,team b)
{
	if (a.name < b.name) return true;
	else return false;
}


int  main()
{
	int n,a,b;
	string info,info1;
	cin >> n;
	team x[50], y[50], z[50];
	for (int i = 0; i < n; i++)
	{
		cin >> z[i].name;
	}
	for (int i = 0; i < n*(n - 1) / 2; i++)
	{
		cin >> info >> info1;
		int len = info.length();
		for (int j = 0;j < len; j++)
		{
			if (info[j] != '-') continue;
			else
			{
				x[i].name = info.substr(0, j); y[i].name = info.substr(j + 1, len - j - 1);
			}
		}
		a = info1[0] - '0';
		b = info1[2] - '0';
		x[i].score = a;
		y[i].score = b;
		x[i].purescore = a - b;
		y[i].purescore = b - a;
		if (a > b) x[i].points = 3;
		else if (a < b) y[i].points = 3;
		else { x[i].points = 1; y[i].points = 1; }
		
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n*(n - 1)/2; j++)
		{
			if (z[i].name == x[j].name)
			{
				z[i].points += x[j].points;
				z[i].purescore += x[j].purescore;
				z[i].score += x[j].score;
			}
			if (z[i].name == y[j].name)
			{
				z[i].points += y[j].points;
				z[i].purescore += y[j].purescore;
				z[i].score += y[j].score;
			}
		}
		
	}
	sort(z, z + n, comp);
	sort(z, z + (n / 2), comp1);
	for (int i = 0; i < n / 2; i++) cout << z[i].name << endl;
	system("pause");
	return 0;
}