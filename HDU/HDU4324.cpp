#include <cstdio>
#include <cstring>
#define MAXN 5010
using namespace std;

int n, m, T, cas;
bool g[MAXN][MAXN], flag;
char s[MAXN];
int in_degree[MAXN];

int main()
{
	//freopen("game.in","r",stdin);freopen("game.out","w",stdout);
	scanf("%d", &T);
	while (T--)
	{
		memset(in_degree, 0, sizeof(in_degree));
		flag = false;
		printf("Case #%d: ", ++cas);
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
		{
			scanf("%s", s);
			for (int j = 0; j < n; j++)
			{
				g[i][j + 1] = (s[j] == '1');
				if (s[j] == '1') in_degree[j + 1]++;
			}
		}
		for (int i = 1; i <= n; i++)
		{
			int j;
			for (j = 1; j <= n; j++) if (!in_degree[j]) break;
			if (j == n + 1)
			{
				flag = true;
				break;
			}
			in_degree[j]--;
			for (int k = 1; k <= n; k++)
				if (g[j][k] && in_degree[k]) in_degree[k]--;
		}
		if (flag) puts("Yes");
		else puts("No");
	}
	return 0;
}
