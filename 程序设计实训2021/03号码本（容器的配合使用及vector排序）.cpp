#include<iostream>
#include<string>
#include<map>
#include<set>
#include<vector>
#include<algorithm>
using namespace std;
//定义输出时的排序规则
bool comp(string a,string b)
{
	if (a.length()==b.length()) return a<b;     //长度小在前
	else return a.length()<b.length();          
}

int main()
{
	int n,num;
	string name,number;
	map<string,set<string> > book;
	//电话本，map存放信息，号码存入set直接去重
	cin>>n;
	for (int i=0;i<n;i++)
	{
		cin>>name>>num;
		for (int j=0;j<num;j++)
		{
			cin>>number;
			book[name].insert(number);
		}
	}
	//信息读入完成
	map<string,set<string> >::iterator it;//开始迭代输出
	cout<<book.size()<<endl;
	for(it=book.begin();it!=book.end();it++)
	{
		string number1,number2;
		cout<<it->first<<" ";
		set<string>::iterator it1,it2;
		vector<string>temp;
		for (it1=it->second.begin();it1!=it->second.end();it1++)
		{
			number1=*it1;
			bool flag=false;
			for(it2=it->second.begin();it2!=it->second.end();it2++)
			{
				number2=*it2;
				if (number2.length()>number1.length()&&number2.substr(number2.length()-number1.length(),number1.length())==number1)
				{
					flag=true;
					break;
				}
			}
			if (flag==false) temp.push_back(number1);
		}
		sort(temp.begin(),temp.end(),comp);
		cout<<temp.size()<<" ";
		for (unsigned int k=0;k<temp.size();k++) cout<<temp[k]<<" ";
		cout<<endl;
	}
	return 0;
}
