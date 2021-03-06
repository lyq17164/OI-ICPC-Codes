#include <vector>
#include <cstdio>
#include <cstring>
#define MAXN 2010
using namespace std;

int T, n, m, a1, a2, c1, c2;
int edge_num[MAXN];
int sta[MAXN], top, cnt;
int dfn[MAXN], low[MAXN], belong[MAXN];
bool vis[MAXN], out;
vector<int> p[MAXN];

inline void add(int p1, int p2)
{
	p[p1].push_back(p2 ^ 1);
	p[p2].push_back(p1 ^ 1);
	return ;
}

inline int mymin(int a, int b)
{
	return a < b ? a : b;
}

inline void clear()
{
	memset(vis, false, sizeof(vis));
	memset(p, 0, sizeof(p));
	memset(dfn, 0, sizeof(dfn));
	memset(low, 0, sizeof(low));
	memset(belong, 0, sizeof(belong));
	top = cnt = T = 0;
	out = false;
	return ;
}

void Tarjan(int x)
{
	dfn[x] = low[x] = ++T;
	sta[++top] = x;
	vis[x] = true;
	for (int i = 0; i < p[x].size(); i++)
	{
		int y = p[x][i];
		if (!dfn[y])
		{
			Tarjan(y);
			low[x] = mymin(low[x], low[y]);
		}
		else if (vis[y]) low[x] = mymin(low[x], dfn[y]);
	}
	if (dfn[x] == low[x])
	{
		int t;
		cnt++;
		do
		{
			t = sta[top--];
			vis[t] = false;
			belong[t] = cnt;
		}
		while (t != x);
	}
}

int main()
{
	while (~scanf("%d%d", &n, &m))
	{
		clear();
		for (int i = 1; i <= m; i++)
		{
			scanf("%d %d %d %d", &a1, &a2, &c1, &c2);
			add(a1 * 2 + c1, a2 * 2 + c2);
		}
		for (int i = 0; i < 2 * n; i++) if (!dfn[i]) Tarjan(i);
		for (int i = 0; i < 2 * n - 1; i = i + 2)
			if (belong[i] == belong[i + 1])
			{
				out = true;
				puts("NO");
				break;
			}
		if (!out) puts("YES");
	}
	return 0;
}
