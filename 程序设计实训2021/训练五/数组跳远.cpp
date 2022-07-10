#include<iostream>
#include<algorithm>
using namespace std;
int arr[100001];
int main()
{
	int k,n,pos;
	cin>>k;
	for(int i=0;i<k;i++)
	{
		cin>>n;
		int dp[100001]={};
		for(int j=0;j<n;j++)
		{
			cin>>arr[j];
		}
		for(int j=0;j<n;j++)
		{
			pos=j;
			while(pos+arr[pos]<n)
			{
				dp[j]+=arr[pos];
				pos+=arr[pos];
			}
			dp[j]+=arr[pos];
			//cout<<j<<"max="<<dp[j]<<endl;
		}
		sort(dp,dp+n);
		cout<<dp[n-1]<<endl;
	}
	return 0;
}
