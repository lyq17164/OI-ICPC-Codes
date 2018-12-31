#include <queue>
#include <cstdio>
#include <cstring>
#define MAXL 35
#define MAXN 2000
#define MAXM 200000
#define GetPos(a,b) (a-1)*m+b
using namespace std;

const int d[4][2] =
{
	{1, 0}, {-1, 0},
	{0, 1}, {0, -1}
};

struct link
{
	int to, val, flow, nxt;
};

link e[MAXM << 1];
int head[MAXN], cnt = 1;
int n, m, S, T, ans, delta;
char g[MAXL];
bool vis[MAXN];
int dis[MAXN], f[MAXN], from[MAXN];
queue <int> q;

inline int mymin(int a, int b)
{
	return a < b ? a : b;
}

inline void add(int u, int v, int f, int c)
{
	e[++cnt] = (link)
	{
		v, c, f, head[u]
	};
	head[u] = cnt;
	e[++cnt] = (link)
	{
		u, -c, 0, head[v]
	};
	head[v] = cnt;
}

inline bool Edmonds_Karp()
{
	memset(dis, 0x7f, sizeof dis);
	memset(vis, false, sizeof vis);
	q.push(S);
	dis[S] = 0;
	vis[S] = true;
	f[S] = ~(1 << 31);
	f[T] = 0;
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		vis[u] = false;
		for (int i = head[u]; i; i = e[i].nxt)
			if (dis[e[i].to] > dis[u] + e[i].val && e[i].flow)
			{
				dis[e[i].to] = dis[u] + e[i].val;
				from[e[i].to] = i;
				f[e[i].to] = mymin(f[u], e[i].flow);
				if (!vis[e[i].to])
				{
					vis[e[i].to] = true;
					q.push(e[i].to);
				}
			}
	}
	if (!f[T]) return false;
	ans += dis[T] * f[T];
	for (int i = from[T]; i; i = from[e[i ^ 1].to])
		e[i].flow -= f[T], e[i ^ 1].flow += f[T];
	return true;
}

int main()
{
	scanf("%d %d", &n, &m);
	S = 0;
	T = (n * m) << 1 | 1;
	delta = n * m;
	for (int i = 1; i <= n; i++)
	{
		scanf("%s", g + 1);
		for (int j = 1; j <= m; j++)
		{
			if (g[j] == 'm') add(S, GetPos(i, j), 1, 0);
			if (g[j] == 'H') add(GetPos(i, j) + delta, T, 1, 0);
			add(GetPos(i, j), GetPos(i, j) + delta, ~(1 << 31), 0);
			for (int k = 0; k < 4; k++)
			{
				int x = i + d[k][0], y = j + d[k][1];
				if (x < 1 || x > n || y < 1 || y > m) continue;
				add(GetPos(i, j) + delta, GetPos(x, y), ~(1 << 31), 1);
			}
		}
	}
	while (Edmonds_Karp());
	printf("%d\n", ans);
	return 0;
}