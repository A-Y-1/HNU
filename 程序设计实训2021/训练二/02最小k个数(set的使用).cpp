#include<math.h>
#include<iostream>
#include<set>
using namespace std;

int main()
{
	int n,k,temp;
	set<int> a;
	cin>>n>>k;
	for (int i=0;i<n;i++)
	{
		cin>>temp;
		a.insert(temp);
	}
	int count=0;
	while(!a.empty()&&count<k)
	{
		cout<<*a.begin()<<" ";
		a.erase(a.begin());	
		count++;
	}
	return 0;
}
