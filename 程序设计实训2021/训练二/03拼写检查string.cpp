#include<iostream>
#include<string>
using namespace std;

int check(string a,string b)   //确认a是否与b相似
{
	string x[]={"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};
	string temp;
	int lena;
	int lenb;
	lena=a.length();
	lenb=b.length();
	if (lena==lenb&&a==b)return 2;
	else if (lena==lenb&&a!=b)
	{
		for (int i=0;i<lena;i++)
		{
			for (int j=0;j<26;j++)
			{
				temp=a;
				temp.replace(i,1,x[j]);   //字符串元素替换
				if (temp==b) return 1;
			}
		}
		return 0;
	}
	else if(lena==lenb+1)
	{
		for (int i=0;i<lena;i++)
		{
			temp=a;
			temp.erase(i,1);             //字符串删除特定元素
			if (temp==b) return 1;
		}
	}
	else if(lena==lenb-1)
	{
		for (int i=0;i<lena+1;i++)		//插入时要取到比长度大，即插入末尾
		{
			for(int j=0;j<26;j++)
			{
				temp=a;
				temp.insert(i,x[j]);	//字符串插入元素
				if (temp==b) return 1;
			}
		}
	}
	return 0;
}


int main()
{
	string dict[1000],result[1000];
	int i=0,re=0,flag=0,count;
	string temp;
	while (1)
	{
		cin>>temp;
		if (temp=="#") break;
		dict[i]=temp;
		i++;				//count记录相似的单词数，在count范围内result不需要清零
	}						//re用于接受check结果，在比较中发生变化	
	while (1)               //flag2表示相同，1表示相似,0表示未找到
	{
		cin>>temp;
		flag=0,count=0;
		if (temp=="#") break;
		for (int j=0;j<i+1;j++)
		{
			re=check(temp,dict[j]);
			if (re==2) {flag=2;cout<<temp<<" "<<"is correct"<<endl;break;}	
			else if(re==0) continue;
			else {result[count]=dict[j];count++;flag=1;}
		}
		if (flag==2);
		else if(flag==0) cout<<temp<<":"<<endl;
		else if (flag==1)
		{
			cout<<temp<<": ";
			for (int j=0;j<count;j++)
			{
				if (j==count-1) cout<<result[j]<<endl;
				else cout<<result[j]<<" ";
			}
		}
	}
	return 1;
}
