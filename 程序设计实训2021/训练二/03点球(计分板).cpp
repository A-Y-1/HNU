#include<string>
#include<iostream>
#include<algorithm>
#include<math.h>
using namespace std;

int main()
{
	string info;
	float t=2;
	int pos,ascore=0,bscore=0;
	int counta=0,countb=0;
	int x;
	int n;              // 总罚球数,进球情况				//存放两队进球情况
	while(1)
	{
		cin>>n;
		int a[10]={};
		int b[10]={};
		ascore=0,bscore=0;
		getchar();
		counta=0,countb=0;
		if (n==0) break;
		for (int i =0;i<n;i++)
		{
			getline(cin,info);
			pos=info.find("no good");
			if (pos==string::npos) x=1;
			else if (pos!=string::npos) x=0;
			if (i%2==0) a[counta]=x,counta++;
			else b[countb]=x,countb++;
		}
		for (int i =1;i<ceil((n/t))+1;i++) cout<<i<<" ";
		cout<<"Score"<<endl;
		for (int i=0;i<ceil(n/t);i++)
		{
			if (a[i]==1) cout<<"O"<<" ",ascore++;
			else cout<<"X"<<" ";
		}
		cout<<ascore<<endl;
		for (int i=0;i<n/2;i++)
		{
			if (b[i]==1) cout<<"O"<<" ",bscore++;
			else cout<<"X"<<" ";
		}
		if (n%2==0) cout<<bscore<<endl;
		else cout<<'-'<<" "<<bscore<<endl;
	}
	return 0;
}
