#include<iostream>
#include<map>
#include<algorithm>
using namespace std;

struct stu{
	int month,day,turn;
	string id;
};

bool comp(stu a,stu b)
{
	if(a.month==b.month)
	{
		if(a.day==b.day) return a.turn<b.turn;
		else return a.day<b.day;
	}
	else return a.month<b.month;
	
	
}


int main()
{
	int n;
	cin>>n;
	stu info[n];
	for(int i=0;i<n;i++)
	{
		cin>>info[i].id>>info[i].month>>info[i].day;
		info[i].turn = i;
	}
	sort(info,info+n,comp);
	
	for(int i=0;i<n;i++)
	{
		//cout<<"info£º"<<info[i].month<<" "<<info[i].day<<" "<<info[i].id<<endl;
		//if(i==0&&info[i].month==info[i+1].month&&info[i].day==info[i+1].day) cout<<info[i].month<<" "<<info[i].day<<" "<<info[i].id<<" ";
		//if(i==n-1&&info[i].month==info[i-1].month&&info[i].day==info[i-1].day) cout<<info[i].month<<" "<<info[i].day<<" "<<info[i].id<<endl;
		if((info[i].month==info[i-1].month&&info[i].day==info[i-1].day)&&(info[i].month!=info[i+1].month||info[i].day!=info[i+1].day)) cout<<info[i].id<<endl;
		else if((info[i].month==info[i-1].month&&info[i].day==info[i-1].day)&&(info[i].month==info[i+1].month&&info[i].day==info[i+1].day)) cout<<info[i].id<<" ";
		else if((info[i].month!=info[i-1].month||info[i].day!=info[i-1].day)&&(info[i].month==info[i+1].month&&info[i].day==info[i+1].day)) cout<<info[i].month<<" "<<info[i].day<<" "<<info[i].id<<" ";
		else cout<<info[i].month<<" "<<info[i].day<<" "<<info[i].id<<endl;
	}
	return 0;
}
