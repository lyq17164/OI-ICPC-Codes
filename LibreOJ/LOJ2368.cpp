#include <bits/stdc++.h>
#define MAXN 410
#define MAXM 41000
using namespace std;

struct link
{
	int to, flow, nxt;
};

link e[MAXM << 1], ebak[MAXM << 1], ebak2[MAXM << 1];
int head[MAXN], cnt = 1;
int n, m, u, v, x, S, T, ans, now;
int dpt[MAXN], a[MAXN >> 1];
queue <int> q;
bool first = true;

inline int mymin(int a, int b)
{
	return a < b ? a : b;
}

inline void add(int u, int v, int f)
{
	e[++cnt] = (link)
	{
		v, f, head[u]
	};
	head[u] = cnt;
	e[++cnt] = (link)
	{
		u, 0, head[v]
	};
	head[v] = cnt;
}

inline bool BFS()
{
	memset(dpt, -1, sizeof dpt);
	dpt[S] = 1;
	q.push(S);
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		for (int i = head[u]; i; i = e[i].nxt)
			if (e[i].flow && !~dpt[e[i].to])
			{
				dpt[e[i].to] = dpt[u] + 1;
				q.push(e[i].to);
			}
	}
	return dpt[T] != -1;
}

inline int Dinic(int x, int flow)
{
	int left = flow;
	if (x == T) return flow;
	for (int i = head[x]; i && left; i = e[i].nxt)
		if (e[i].flow && dpt[e[i].to] == dpt[x] + 1)
		{
			int t = Dinic(e[i].to, mymin(e[i].flow, left));
			e[i].flow -= t;
			e[i ^ 1].flow += t;
			left -= t;
		}
	if (left) dpt[x] = -1;
	return flow - left;
}

inline int Flow()
{
	int ans = 0;
	while (BFS()) ans += Dinic(S, ~(1 << 31));
	return ans;
}

inline void read(int &x)
{
	x = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9') ch = getchar();
	while (ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
	return ;
}

int main()
{
	read(n);
	read(m);
	read(S);
	read(T);
	T += n;
	for (int i = 1; i <= n; i++) read(a[i]), add(i, i + n, a[i]);
	for (int i = 1; i <= m; i++)
	{
		read(u);
		read(v);
		add(u + n, v, ~(1 << 31));
		add(v + n, u, ~(1 << 31));
	}
	memcpy(ebak2, e, sizeof e);
	ans = Flow();
	memcpy(e, ebak2, sizeof ebak2);
	for (int i = 1; i <= n; i++)
		if (e[i << 1].flow)
		{
			memcpy(ebak, e, sizeof ebak);
			e[i << 1].flow = e[i << 1 | 1].flow = 0;
			now = Flow();
			if (ans - now == a[i])
			{
				if (first)
				{
					first = false;
					printf("%d", i);
				}
				else printf(" %d", i);
				ans = now;
				ebak2[i << 1].flow = ebak2[i << 1 | 1].flow = 0;
			}
			else memcpy(e, ebak, sizeof ebak);
			memcpy(e, ebak2, sizeof ebak2);
		}
	puts("");
	return 0;
}