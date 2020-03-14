#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <cassert>
#include <cstring>
#define MAXN 10205
using namespace std;

struct link
{
	int to, rev, flow; double val;
	link(){}
	link(int _to, int _rev, int _flow, double _val):
		to(_to), rev(_rev), flow(_flow), val(_val){}
};

vector <link> g[MAXN];
int n, m, u, v, s, t, S, T, flow, ptr[MAXN];
double dis[MAXN];
bool vis[MAXN];
queue <int> q;

inline void add(int u, int v, double c, int f)
{
	g[u].push_back(link(v, g[v].size(), f, c));
	g[v].push_back(link(u, int(g[u].size()) - 1, 0, -c));
}

inline bool SPFA()
{
	for (int i=S;i<=T;i++) dis[i]=1e18;
	memset(vis, false, sizeof vis);
	q.push(S); dis[S] = 0;
	while (!q.empty())
	{
		int u = q.front(); q.pop(); vis[u] = false;
		for (auto& e : g[u])
			if (e.flow && dis[e.to] > dis[u] + e.val)
			{
				dis[e.to] = dis[u] + e.val;
				if (!vis[e.to])
				{
					vis[e.to] = true;
					q.push(e.to);
				}
			}
	}
	return dis[T] != 1e18;
}

inline int Dinic(int x, int flow)
{
	int left = flow;
	if (x == T) return flow;
	vis[x] = true;
	for (int& i = ptr[x]; i < int(g[x].size()) && left && flow; i++)
	{
		link& e = g[x][i];
		if (dis[e.to] == dis[x] + e.val && e.flow && !vis[e.to])
		{
			int t = Dinic(e.to, min(e.flow, left));
			e.flow -= t; g[e.to][e.rev].flow += t; left -= t;
		}
	}
	if (!left) vis[x] = false;
	return flow - left;
}

int main()
{
	scanf("%d",&n);S=0;T=(n+1)*(n+1);
	for (int i=1;i<=n;i++)
	{
		add(S,i,0,1);
		add((n+1)*n+i,T,0,1);
	}
	for (int i=1;i<=n;i++)
		for (int j=1,x;j<=n;j++)
		{
			scanf("%d",&x);
			add(i,i*n+j,-log(x),1);
			add(i*n+j,(n+1)*n+j,0,1);
		}
	while (SPFA())
	{
		memset(ptr, 0, sizeof ptr);
		int d = Dinic(S, ~(1 << 31));
		flow += d;
	}
	assert(flow==n);
	for (int i=1;i<=n;i++)
	{
		for (auto x:g[(n+1)*n+i])
			if (x.flow==1)
			{
				printf("%d%c",(x.to-1)/n,i==n?'\n':' ');
				break;
			}
	}
	return 0;
}
