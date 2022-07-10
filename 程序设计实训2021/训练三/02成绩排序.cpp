#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

struct info{
	string name;
	string num;
	int score;
};

bool comp(info a,info b)
{
	if (a.score==b.score) return false;
	else return a.score<b.score;
}

int main()
{
	int n,score;
	cin>>n;
	string name,num;
	info b[n];
	for (int i=0;i<n;i++)
	{
		cin>>name>>num>>score;
		b[i].name=name;
		b[i].num=num;
		b[i].score=score;
	}
	sort(b,b+n,comp);
	cout<<b[n-1].name<<" "<<b[n-1].num<<endl;
	cout<<b[0].name<<" "<<b[0].num<<endl;
	return 0;
}
