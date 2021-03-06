#include <bits/stdc++.h>
#define MAXN 410
#define MAXM 41000
using namespace std;

struct link
{
	int to, flow, nxt;
};

link e[MAXM << 1], bak[MAXM << 1], bak2[MAXM << 1];
int head[MAXN], cnt = 1;
int n, m, u, v, x, S, T, A, B, ans, now, delta;
int dpt[MAXN];
bool first = true;
queue <int> q;

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
	for (int i = 1; i <= n; i++)
	{
		read(x);
		add(i, i + n, x);
	}
	for (int i = 1; i <= m; i++)
	{
		read(u);
		read(v);
		add(u + n, v, ~(1 << 31));
		add(v + n, u, ~(1 << 31));
	}
	memcpy(bak, e, sizeof e);
	while (BFS()) ans += Dinic(S, ~(1 << 31));
	for (int i = 1; i <= n; i++)
	{
		memcpy(bak2, e, sizeof e);
		memcpy(e, bak, sizeof e);
		delta = e[i << 1].flow;
		e[i << 1].flow = e[i << 1 | 1].flow = 0;
		now = 0;
		while (BFS()) now += Dinic(S, ~(1 << 31));
		if (ans - now == delta)
		{
			if (first)
			{
				first = false;
				printf("%d", i);
			}
			else printf(" %d", i);
			bak[i << 1].flow = 0;
			ans = now;
		}
		else memcpy(e, bak2, sizeof bak2);
	}
	puts("");
	return 0;
}