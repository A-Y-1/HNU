#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
struct ath
{
	int score;
	int turn;
	int paiming;
};
bool comp1(ath a,ath b)
{
	if(a.score==b.score) return false;
	else return a.score>b.score;
}
bool comp2(ath a,ath b)
{
	if(a.turn==b.turn) return false;
	else return a.turn <b.turn;
}

int main()
{
	int n;
	cin>>n;
	ath info[n];
	for(int i=0;i<n;i++)
	{
		cin>>info[i].score;
		info[i].turn=i;
	}
	sort(info,info+n,comp1);
	int count=0;
	for(int i=0;i<n;i++)
	{
		if (info[i].score==info[i-1].score&&i!=0) info[i].paiming=info[i-1].paiming;
		else {info[i].paiming=count+1;count++;}
	}
	sort(info,info+n,comp2);
	for(int i=0;i<n;i++)
	{
		cout<<info[i].paiming<<" ";
	}
	cout<<endl;
	system("pause");
	return 0;
}
