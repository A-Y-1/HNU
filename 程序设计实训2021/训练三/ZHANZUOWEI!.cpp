#include<iostream>
#include<string>
using namespace std;
int seat[10000]={0};
int main()
{
	int row=0;//行数 
	while(cin>>row)
	{
		for(int i=0;i<row*row;i++)//初始化 
		{
			seat[i]=0;
		}
		int m=0;//人数，但我觉得没用啊 
		cin>>m;
		int n=0;
		cin>>n;
		string s;//什么操作 in还是out 
		int id=0;//是什么同学 
		int num=0;//要占多少个座位 
		int k=0; //记录究竟现在占到什么座位了 
		for(int i=0;i<n;i++)
		{
			cin>>s;
 
		//	cout<<s<<endl<<id<<endl<<num<<endl;
			if(s[0]=='i')//如果是in操作的话 
			{
				cin>>id;
				cin>>num;
				bool occupy=false;//首先判断是否已经占过座位了 
				for(int j=0;j<row*row;j++)//如果占了座位，后面的in就无效了 
				{
					if(seat[j]==id)//找到了占过座位的痕迹 
					{
						occupy=true;
						break;// * 
					}
				}
				if(occupy==true)//这里我纯粹是真的想起到“continue ”的作用，因为在 *处加continue还是困在那个for循环 
				{
					cout<<"no"<<endl;
					continue;
				} 
				bool enough=false;
				int seattotal=0;
				for(int j=0;j<row*row;j++)//检查是否够位子，要注意，你有可能释放前面占过的座位，所以要从头开始寻 
				{
					if(seat[j]==0)
					{
						seattotal++;
						if(seattotal==num)//如果足够位置了，那么就直接break出去好了，用k记录当前位置，倒序占座位 
						{
							k=j;
							break;
						}
					}
					else//不连续，直接清零能够占的座位 
					{
						seattotal=0;
					} 
				}
				if(seattotal==num)
				enough=true;
				if(enough==true)
				{
					cout<<"yes"<<endl;
					for(int j=k;num>0;j--)//霸座位，数组内容为id ，这样子做就可以表示是这个人占的座位了 
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
			else//遇到了out操作不用判断是否有效，无效就无法清空嘛，有效的直接清空嘛，不需要输出yes or no 
			{
				cin>>id;
				for(int j=0;j<row*row;j++)//占过就清空 
				{
					if(seat[j]==id)
					seat[j]=0;
				}
				cout<<"yes"<<endl;		
			}
		}
	}
 } 
