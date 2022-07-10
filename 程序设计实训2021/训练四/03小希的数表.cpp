#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 105;
const int MAXS = MAXN * MAXN / 2;
 
int num[MAXN]; //原数字
int sum[MAXS]; //和
int vis[MAXS]; //和的访问情况
 
int main()
{
	int n; //原数字数量
	while (cin >> n)
	{
		if (n == 0)
			break;
		int m = n * (n - 1) / 2; //和数量
		for (int i = 1; i <= m; i++) //输入和
		{
			cin >> sum[i];
		}
		sort(sum + 1, sum + 1 + m);
		for (int i = 3; i <= m; i++) //枚举num[2]+num[3]的和
		{
			num[1] = (sum[1] + sum[2] - sum[i]) / 2;
			num[2] = sum[1] - num[1];
			num[3] = sum[2] - num[1];
			memset(vis, 0, sizeof(vis));
			vis[i] = 1;
			bool flag = true;
			int start = 3; //目前未被访问的最小的和
			for (int j = 4; j <= n && flag == true; j++)
			{ //依次查找num[4]至num[n]
				while (vis[start])
					++start;
 
				vis[start] = 1; //排除num[1]+num[j]
				num[j] = sum[start] - num[1]; //求得num[j]
				for (int k = 2; k < j && flag == true; k++)
				{ //排除num[2]+num[j]，num[3]+num[j]，...，num[j-1]+num[j]
					for (int p = start + 1; p <= m; p++)
					{
						flag = false;
						if (!vis[p] && num[k] + num[j] == sum[p])
						{
							vis[p] = 1;
							flag = true;
							break;
						}
					}
				}
			}
			if (flag == true) //找到的num满足所有sum
				break;
		}
		for (int i = 1; i < n; i++) //输出
			cout << num[i] << " ";
		cout << num[n] << endl;
	}
	return 0;
}
