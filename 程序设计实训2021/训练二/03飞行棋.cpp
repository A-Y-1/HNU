#include<string>
#include<iostream>
#include<math.h>
using namespace std;
int str2num(string a)//�������ϵ��ַ�ת��Ϊʵ��
{
	int len=a.length();
	int num=0;
	for (int i=1;i<len;i++)
	{
		a[i]=a[i]-'0';
		num=num+a[i]*pow(10,len-1-i);
	}
	return num;
}
int main()
{
	int n,a,b,c;
	int lele[1],yueyue[1];  //��¼���˵�λ��
	string qipan[200];		//����
	int step;				//����
	int turn;				//�غ�
	while(cin>>n>>a>>b>>c)
	{
		for (int i=0;i<n;i++)
		{
			cin>>qipan[i];
		}
		lele[0]=0,yueyue[0]=0;
		step=0;				//ע���ʼ������
		turn=0;
		while(1)			//��Ϸ���� 
		{
			if(turn==0) step=(a*c+b)%6+1;
			else step=(a*step+b)%6+1;
			if (turn%2==0)
			{
				if (lele[0]+step<=n-1) lele[0]+=step;
				else if (lele[0]+step>n-1) lele[0]=n-1-(step-(n-1-lele[0]));
				if (qipan[lele[0]]!="N") lele[0]=str2num(qipan[lele[0]]);
				if (lele[0]==yueyue[0]) yueyue[0]=0;
				if (lele[0]==n-1) break;
				
			}
			if (turn%2!=0)
			{
				if (yueyue[0]+step<=n-1) yueyue[0]+=step;
				else if (yueyue[0]+step>n-1) yueyue[0]=n-1-(step-(n-1-yueyue[0]));
				if (qipan[yueyue[0]]!="N") yueyue[0]=str2num(qipan[yueyue[0]]);
				if (lele[0]==yueyue[0]) lele[0]=0;
				if (yueyue[0]==n-1) break;
							
			}
				
			turn++;
		}
		
		if (lele[0]==n-1) cout<<"Lele"<<endl;
		else if (yueyue[0]==n-1) cout<<"Yueyue"<<endl;//�жϽ��
		
		
	}
	return 0;
}
