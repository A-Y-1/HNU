#include<iostream>
#include<map>
using namespace std;

int main()
{
	int quan[]={7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2};
	map<int,char> code={{0,'1'},{1,'0'},{2,'X'},{3,'9'},{4,'8'},{5,'7'},{6,'6'},{7,'5'},{8,'4'},{9,'3'},{10,'2'}};
	string id,code0;
	int sum,Y;
	while(1)
	{
		sum=0;
		cin>>id;
		if(id=="-1")break;
		for(int i=0;i<17;i++)
		{
			sum+=(id[i]-'0')*quan[i];
		}
		Y=sum%11;
		code0=code[Y];
		if(code0==id.substr(17,1)) cout<<1<<endl;
		else cout<<0<<endl;
		
	}
	return 0;
}
