#include<iostream>
#include<string>
using namespace std;
int seat[10000]={0};
int main()
{
	int row=0;//���� 
	while(cin>>row)
	{
		for(int i=0;i<row*row;i++)//��ʼ�� 
		{
			seat[i]=0;
		}
		int m=0;//���������Ҿ���û�ð� 
		cin>>m;
		int n=0;
		cin>>n;
		string s;//ʲô���� in����out 
		int id=0;//��ʲôͬѧ 
		int num=0;//Ҫռ���ٸ���λ 
		int k=0; //��¼��������ռ��ʲô��λ�� 
		for(int i=0;i<n;i++)
		{
			cin>>s;
 
		//	cout<<s<<endl<<id<<endl<<num<<endl;
			if(s[0]=='i')//�����in�����Ļ� 
			{
				cin>>id;
				cin>>num;
				bool occupy=false;//�����ж��Ƿ��Ѿ�ռ����λ�� 
				for(int j=0;j<row*row;j++)//���ռ����λ�������in����Ч�� 
				{
					if(seat[j]==id)//�ҵ���ռ����λ�ĺۼ� 
					{
						occupy=true;
						break;// * 
					}
				}
				if(occupy==true)//�����Ҵ�����������𵽡�continue �������ã���Ϊ�� *����continue���������Ǹ�forѭ�� 
				{
					cout<<"no"<<endl;
					continue;
				} 
				bool enough=false;
				int seattotal=0;
				for(int j=0;j<row*row;j++)//����Ƿ�λ�ӣ�Ҫע�⣬���п����ͷ�ǰ��ռ������λ������Ҫ��ͷ��ʼѰ 
				{
					if(seat[j]==0)
					{
						seattotal++;
						if(seattotal==num)//����㹻λ���ˣ���ô��ֱ��break��ȥ���ˣ���k��¼��ǰλ�ã�����ռ��λ 
						{
							k=j;
							break;
						}
					}
					else//��������ֱ�������ܹ�ռ����λ 
					{
						seattotal=0;
					} 
				}
				if(seattotal==num)
				enough=true;
				if(enough==true)
				{
					cout<<"yes"<<endl;
					for(int j=k;num>0;j--)//����λ����������Ϊid �����������Ϳ��Ա�ʾ�������ռ����λ�� 
					{
						seat[j]=id;
						num--;
					}
				}
				else
				{
					cout<<"no"<<endl;
				}
			}
			else//������out���������ж��Ƿ���Ч����Ч���޷�������Ч��ֱ����������Ҫ���yes or no 
			{
				cin>>id;
				for(int j=0;j<row*row;j++)//ռ������� 
				{
					if(seat[j]==id)
					seat[j]=0;
				}
				cout<<"yes"<<endl;		
			}
		}
	}
 } 
