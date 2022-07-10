#include<map>
#include<iostream>
#include<string>
using namespace std;

string name,use;//存放分开的咒语和功能

void split(string a)	//分词
{
	int len=a.length();
	for(int i=0;i<len;i++)
	{
		if(a[i]==']') 
		{
			name=a.substr(0,i+1);
			use=a.substr(i+2,len-i-2);
		}
	}
}

int main()
{
	string temp;
	int n;
	map<string,string> book1,book2;
	while(1)
	{
		getline(cin,temp);
		if(temp=="@END@") break;
		split(temp);
		book1[name]=use;
		book2[use]=name;
	}
	cin>>n;
	getchar();
	for(int i=0;i<n;i++)
	{
		getline(cin,temp);
		if(book1.count(temp)==0&&book2.count(temp)==0) cout<<"what?"<<endl;
		else if(book1.count(temp)!=0) cout<<book1[temp]<<endl;
		else cout<<book2[temp]<<endl;
	}
	return 0;
}
