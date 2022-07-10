#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 105;
const int MAXS = MAXN * MAXN / 2;
 
int num[MAXN]; //ԭ����
int sum[MAXS]; //��
int vis[MAXS]; //�͵ķ������
 
int main()
{
	int n; //ԭ��������
	while (cin >> n)
	{
		if (n == 0)
			break;
		int m = n * (n - 1) / 2; //������
		for (int i = 1; i <= m; i++) //�����
		{
			cin >> sum[i];
		}
		sort(sum + 1, sum + 1 + m);
		for (int i = 3; i <= m; i++) //ö��num[2]+num[3]�ĺ�
		{
			num[1] = (sum[1] + sum[2] - sum[i]) / 2;
			num[2] = sum[1] - num[1];
			num[3] = sum[2] - num[1];
			memset(vis, 0, sizeof(vis));
			vis[i] = 1;
			bool flag = true;
			int start = 3; //Ŀǰδ�����ʵ���С�ĺ�
			for (int j = 4; j <= n && flag == true; j++)
			{ //���β���num[4]��num[n]
				while (vis[start])
					++start;
 
				vis[start] = 1; //�ų�num[1]+num[j]
				num[j] = sum[start] - num[1]; //���num[j]
				for (int k = 2; k < j && flag == true; k++)
				{ //�ų�num[2]+num[j]��num[3]+num[j]��...��num[j-1]+num[j]
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
			if (flag == true) //�ҵ���num��������sum
				break;
		}
		for (int i = 1; i < n; i++) //���
			cout << num[i] << " ";
		cout << num[n] << endl;
	}
	return 0;
}
