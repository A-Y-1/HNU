#include<iostream>
#include<stdio.h>
#include<string>
#include<algorithm>
using namespace std;

//结构体，选手信息
struct racer 
{
	string name="null";
	int points=0;
	int pw[10] = {0,0,0,0,0,0,0,0,0,0};
};

//排序规则
bool comp1(racer a, racer b)
{
	if (a.points == b.points)
	{
		for (int i = 0; i < 10; i++)
		{
			if (a.pw[i] > b.pw[i])
			{
				return true;
			}
			else if (a.pw[i] < b.pw[i])
			{
				return false;
			}
		}
		return false;       //循环结束必须保证有返回值
	}
	else if (a.points != b.points) return a.points > b.points;
}
bool comp2(racer a,racer b)
{
	if (a.pw[0] > b.pw[0]) return true;
	else if (a.pw[0] == b.pw[0])
	{
		if (a.points > b.points) return true;
		else if (a.points < b.points) return false;
		else 
		{
			for (int i = 1; i < 10; i++)
			{
				if (a.pw[i] > b.pw[i]) return true;
				else if (a.pw[i] < b.pw[i]) return false;
			}
		}
		return false;
	}
	else return false;

}


int  main()
{
	int t, n;
	int	points1=0;
	int points[] = { 25,18,15,12,10,8,6,4,2,1 };
	string name;
	cin >> t;
	racer rinfo[100];
	for (int i = 0; i < t; i++)
	{
		cin >> n;
		for (int j = 0; j < n; j++)
		{
			cin >> name;
			if (j < 10) points1 = points[j];
			for (int k = 0; k < 100; k++)
			{
				if (rinfo[k].name == "null")
				{
					rinfo[k].name = name;
					rinfo[k].pw[j] += 1;
					rinfo[k].points = points1;
					break;
				}
				else if (rinfo[k].name != "null" && rinfo[k].name == name)
				{
					rinfo[k].pw[j] += 1;
					rinfo[k].points += points1;
					break;
				}
				else if (rinfo[k].name != "null" && rinfo[k].name != name) continue;
			}		
		}
		
	
	}
	sort(rinfo, rinfo + 100, comp1);
	cout << rinfo[0].name<<endl;
	sort(rinfo, rinfo + 100, comp2);
	cout << rinfo[0].name << endl;

	system("pause");
	return 0;
}