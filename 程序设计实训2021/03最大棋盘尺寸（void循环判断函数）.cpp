#include<iostream>
#include<string>
using namespace std;

int chessboard[2000][2000]={};
int num[2000]={};
int maxsize=0;


void check(int i,int j,int size,int n)
{
	if (chessboard[i][j]==0) return;
	if (i+size-1>n||j+size-1>n) return;
	for (int k=1;k<size+1;k++)
	{
		for (int t =1;t<size+1;t++)   //k和 t要从1取到size+1
		{
			if ((k+t)%2==0&&chessboard[k-1+i][j-1+t]==0) return;
			else if ((k+t)%2!=0&&chessboard[k-1+i][t-1+j]==1) return;	
		}
	}
	num[size]+=1;
	if (size>maxsize)
	{
		maxsize=size;
	}
	check(i,j,size+1,n);
}

int main()
{
	int n;
	cin>>n;
	string temp;
	for (int i=0;i<n;i++)
	{
		cin>>temp;
		for (int j=0;j<n;j++)
		{
			chessboard[i][j]=temp[j]-'0';
		}
	}
	for (int i=0;i<n;i++)
	{
		for (int j =0;j<n;j++) {check(i,j,1,n);}
	}
	cout<<maxsize<<" "<<num[maxsize]<<endl;
	
	
	return 0;
}
