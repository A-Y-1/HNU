#include<iostream>
#include<string>
#include<map>
#include<algorithm>
using namespace std;

//����ṹ��
struct info{
	string title="null";
	int time,turn;
};
//��������Ϣ����
bool comp(info a,info b)
{
 	if (a.time==b.time) 
 	{
		if(a.turn==b.turn) return false;
		else return a.turn<b.turn; 	
	}
	else return a.time>b.time;
}

int check(string a,string b)  	//stringb�� ����stringa 
{
	string x[20],y[20];
	int lenx=a.length();
	int leny=b.length();
	int k=0,a1=0,b1=0;
	int dcsa=0,dcsb=0;
	for (int i=0;i<lenx;i++)
	{
		if (a[i]<97&&a[i]!=' ') a[i]=a[i]+32;
		if (a[i]==' ')
		{
			x[a1]=a.substr(k,i-k);
			a1++;
			k=i+1;
			dcsa++;
		}
		else if (i==lenx-1) {x[a1]=a.substr(k,i-k+1);dcsa++;}
		
	}
	k=0;
	for (int i=0;i<leny;i++)
	{
		
		if (b[i]<97&&b[i]!=' ') b[i]=b[i]+32;
		if (b[i]==' ')
		{
			y[b1]=b.substr(k,i-k);
			b1++;
			k=i+1;
			dcsb++;
			
		}
		else if (i==leny-1){ y[b1]=b.substr(k,i-k+1);dcsb++;}
		
	}
	int flag=0;
	for (int i=0;i<dcsa;i++)
	{
		flag=0;           	//a�ﻹ�е���δZHAOWAN
		for (int j=0;j<dcsb;j++)
		{
			if (x[i]==y[j]) flag=1;
		}
		if (flag==0)
		{
			
			return 0;
		}
	}
	return 1;
	
}


 
int main()
{
	int n,m,inornot,count=0;                      //n����Ϣ��m����Ҫ��Ѱ
 	string temp;
 	
 	while(1)
 	{
 		cin>>n;				//�����n=0����ֹ�����ж�n��while��cin>>n���жϵ�����Ч����
		if (n==0) break;
 		info ku[1000]={};
	 	for(int i=0;i<n;i++)  	  //cin֮��ȡ��һ��get��Ҫȥ���س���get֮��cin����Ҫ
	 	{
	 		getchar();
		 	getline(cin,temp);
		 	ku[i].title=temp;
		 	cin>>ku[i].time;
		 	ku[i].turn=i;
		 	
		}
		sort(ku,ku+n,comp);
		cin>>m;
		getchar();
		for (int i=0;i<m;i++)
		{
			
			getline(cin,temp);
			count=0;
			for (int j =0;j<n;j++)
			{
				//cout<<"���ҵ���"<<temp<<" "<<"�ȶԵ���"<<endl;
				inornot=check(temp,ku[j].title);
				if (inornot==1) 
				{
					count++;
					cout <<ku[j].title<<endl;
				}
			}
			cout<<"***"<<endl;
		}
		cout<<"---"<<endl;
	}
 	system("pause");
 	return 0;
}
