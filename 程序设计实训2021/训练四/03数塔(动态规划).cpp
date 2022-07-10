#include<iostream>
#include<stack>
#include<algorithm>
using namespace std;
int tower[1000][1000],maxsum[1000][1000];
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=i;j++)
		{
			cin>>tower[i][j];
		}
	}
	for(int i=1;i<=n;i++)
	{
		maxsum[n][i]=tower[n][i];
	}
	for(int i=n-1;i>=1;i--)
	{
		for(int j=1;j<=i;j++)
		{
			if(maxsum[i+1][j]+tower[i][j]>maxsum[i+1][j+1]+tower[i][j])
			{
				maxsum[i][j]=maxsum[i+1][j]+tower[i][j];
			}
			else 
			{
				maxsum[i][j]=maxsum[i+1][j+1]+tower[i][j]; 
			}
		}
	}
	cout<<maxsum[1][1]<<endl;
	cout<<tower[1][1];
	int j=1;
    for(int i=2;i<=n;i++){
        int temp = maxsum[i-1][j]-tower[i-1][j];
        if(temp == maxsum[i][j+1])
		{
            j++;
        }
        cout<<" "<<tower[i][j];
    }
	cout<<endl;
	return 0;
}
