#include<iostream>
using namespace std;

int main()
{
	int coin[10];
	int m,k;
	while(cin>>m)
	{
		if(m==0) break;
		int dp[m+1];
		dp[0]=0;
		for(int i=1;i<m+1;i++) dp[i]=9999;
		cin>>k;
		for(int i=0;i<k;i++) cin>>coin[i];
		for(int i=1;i<m+1;i++)
		{
			for(int j=0;j<k;j++)
			{
				if(i>=coin[j])
				{
					dp[i]=min(dp[i-coin[j]]+1,dp[i]);
				}
			}
		}
		if(dp[m]==9999) cout<<"Impossible"<<endl;
		else cout<<dp[m]<<endl;
	}			
	return 0;
}
