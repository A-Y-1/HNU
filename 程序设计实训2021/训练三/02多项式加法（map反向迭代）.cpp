#include<iostream>
#include<math.h>
#include<string>
#include<map>
#include<algorithm>
using namespace std;



int main()
{
	int tmi,tx;
	map<int,int> re;
	while(1)
	{
		cin>>tmi>>tx;
		if(tmi==0&&tx==0) break;
		if(re.count(tmi)==0)re[tmi]=0;
		re[tmi]+=tx	;
	}
	while(1)
	{
		cin>>tmi>>tx;
		if(tmi==0&&tx==0) break;
		if(re.count(tmi)==0)re[tmi]=0;
		re[tmi]+=tx	;
	}
	map<int,int>::reverse_iterator it;
	for(it=re.rbegin();it!=re.rend();it++)		//map�������
	{
		if(it->second==0) continue;				//����ϵ��Ϊ0�����
		cout<<it->first<<" "<<it->second<<endl; 
	}

	
	return 0;
}
