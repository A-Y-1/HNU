#include<iostream>
using namespace std;

int main()
{
	int coin[10];
	int m,k;
	while(cin>>m)
	{
		if(m==0) break;
		int dp[m+1];//dp数组，存储每个金额所需的最小钱币数
		dp[0]=0;
		for(int i=1;i<m+1;i++) dp[i]=9999;
		cin>>k;
		for(int i=0;i<k;i++) cin>>coin[i];
		for(int i=1;i<m+1;i++)
		{
			for(int j=0;j<k;j++)
			{
				if(i>=coin[j])//比面额数大才可拿掉
				{
					dp[i]=min(dp[i-coin[j]]+1,dp[i]);//动态方程,计算拿掉每一种钱币后金额的最小钱币数，存储最小值
				}
			}
		}
		if(dp[m]==9999) cout<<"Impossible"<<endl;
		else cout<<dp[m]<<endl;
	}			
	return 0;
}
