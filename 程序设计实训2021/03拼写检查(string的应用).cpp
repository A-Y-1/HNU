#include<iostream>
#include<string>
using namespace std;

int check(string a,string b)   //ȷ��a�Ƿ���b����
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
				temp.replace(i,1,x[j]);   //�ַ���Ԫ���滻
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
			temp.erase(i,1);             //�ַ���ɾ���ض�Ԫ��
			if (temp==b) return 1;
		}
	}
	else if(lena==lenb-1)
	{
		for (int i=0;i<lena+1;i++)		//����ʱҪȡ���ȳ��ȴ󣬼�����ĩβ
		{
			for(int j=0;j<26;j++)
			{
				temp=a;
				temp.insert(i,x[j]);	//�ַ�������Ԫ��
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
		i++;				//count��¼���Ƶĵ���������count��Χ��result����Ҫ����
	}						//re���ڽ���check������ڱȽ��з����仯	
	while (1)               //flag2��ʾ��ͬ��1��ʾ����,0��ʾδ�ҵ�
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
