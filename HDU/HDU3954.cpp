#include <cstdio>
#include <climits>
#define MAXN 10005
using namespace std;

struct SegmentTree
{
	int p, r, m;
	int left, right;
	int lazy;
	int exp, lev, rest;
};

SegmentTree tree[MAXN * 2];
int top, n, k, T, l, r, e, cas, cnt;
int need[11];
char opt[3];

int mymin(int a, int b)
{
	return a < b ? a : b;
}
int mymax(int a, int b)
{
	return a > b ? a : b;
}

int read()
{
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9')
	{
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
	return x * f;
}

void Build_A_Tree(int u)
{
	tree[u].lazy = 0;
	tree[u].exp = 0;
	tree[u].lev = 1;
	tree[u].rest = need[1];
	if (tree[u].p + 1 == tree[u].r) return ;
	tree[u].m = (tree[u].p + tree[u].r) >> 1;
	top++;
	tree[u].left = top;
	tree[top].p = tree[u].p;
	tree[top].r = tree[u].m;
	Build_A_Tree(top);
	top++;
	tree[u].right = top;
	tree[top].p = tree[u].m;
	tree[top].r = tree[u].r;
	Build_A_Tree(top);
	return ;
}

void lazy(int u)
{
	int np = tree[u].left;
	tree[np].exp += tree[u].lazy * tree[np].lev;
	tree[np].rest -= tree[u].lazy;
	tree[np].lazy += tree[u].lazy;
	np = tree[u].right;
	tree[np].exp += tree[u].lazy * tree[np].lev;
	tree[np].rest -= tree[u].lazy;
	tree[np].lazy += tree[u].lazy;
	tree[u].lazy = 0;
	return ;
}

void up(int u)
{
	tree[u].exp = mymax(tree[tree[u].left].exp, tree[tree[u].right].exp);
	tree[u].lev = mymax(tree[tree[u].left].lev, tree[tree[u].right].lev);
	tree[u].rest = mymin(tree[tree[u].left].rest, tree[tree[u].right].rest);
	return ;
}

void modify(int u, int l, int r, int delta)
{
	if (tree[u].p + 1 == tree[u].r)
	{
		tree[u].exp += tree[u].lev * delta;
		while (tree[u].exp >= need[tree[u].lev]) tree[u].lev++;
		tree[u].rest = (need[tree[u].lev] - tree[u].exp) / tree[u].lev;
		if ((need[tree[u].lev] - tree[u].exp) % tree[u].lev) tree[u].rest++;
		return ;
	}
	if (tree[u].p == l && tree[u].r == r)
	{
		if (tree[u].rest <= delta)
		{
			lazy(u);
			modify(tree[u].left, l, tree[u].m, delta);
			modify(tree[u].right, tree[u].m, r, delta);
			up(u);
		}
		else
		{
			tree[u].lazy += delta;
			tree[u].exp += tree[u].lev * delta;
			tree[u].rest -= delta;
		}
		return ;
	}
	if (tree[u].lazy) lazy(u);
	if (tree[u].m >= r) modify(tree[u].left, l, r, delta);
	else if (tree[u].m <= l) modify(tree[u].right, l, r, delta);
	else
	{
		modify(tree[u].left, l, tree[u].m, delta);
		modify(tree[u].right, tree[u].m, r, delta);
	}
	up(u);
	return ;
}

int query(int u, int l, int r)
{
	if (tree[u].p == l && tree[u].r == r) return tree[u].exp;
	if (tree[u].lazy) lazy(u);
	if (tree[u].m >= r) return query(tree[u].left, l, r);
	else if (tree[u].m <= l) return query(tree[u].right, l, r);
	else return mymax(query(tree[u].left, l, tree[u].m), query(tree[u].right, tree[u].m, r));
}

int main()
{
	cas = read();
	while (cas--)
	{
		printf("Case %d:\n", ++cnt);
		n = read();
		k = read();
		T = read();
		for (int i = 1; i < k; i++) need[i] = read();
		need[k] = INT_MAX; //need[k+1]=INT_MAX;
		top = 1;
		tree[1].p = 1;
		tree[1].r = n + 1;
		Build_A_Tree(1);
		while (T--)
		{
			scanf("%s", opt);
			if (opt[0] == 'W')
			{
				l = read();
				r = read();
				e = read();
				modify(1, l, r + 1, e);
			}
			else
			{
				l = read();
				r = read();
				printf("%d\n", query(1, l, r + 1));
			}
		}
		puts("");
	}
	return 0;
}

