#include <cstdio>
#define MAXN 1000010
using namespace std;

struct node
{
	int left_child;
	int right_child;
	int s;
	int key;
};

node tree[MAXN];
int n, k;
int siz;

void right_rotate(int &node)
{
	int k = tree[node].left_child;
	tree[node].left_child = tree[k].right_child;
	tree[k].right_child = node;
	tree[k].s = tree[node].s;
	tree[node].s = tree[tree[node].left_child].s + tree[tree[node].right_child].s + 1;
	node = k;
}

void left_rotate(int &node)
{
	int k = tree[node].right_child;
	tree[node].right_child = tree[k].left_child;
	tree[k].left_child = node;
	tree[k].s = tree[node].s;
	tree[node].s = tree[tree[node].left_child].s + tree[tree[node].right_child].s + 1;
	node = k;
}

void maintain(int &node, bool flag)
{
	if (!flag)
	{
		if (tree[tree[tree[node].left_child].left_child].s > tree[tree[node].right_child].s)
			right_rotate(node);
		else if (tree[tree[tree[node].right_child].left_child].s > tree[tree[node].right_child].s)
		{
			left_rotate(node);
			right_rotate(node);
		}
		else return;
	}
	else
	{
		if (tree[tree[tree[node].right_child].right_child].s > tree[tree[node].left_child].s)
			left_rotate(node);
		else if (tree[tree[tree[node].left_child].right_child].s > tree[tree[node].left_child].s)
		{
			right_rotate(node);
			left_rotate(node);
		}
		else return;
	}
	maintain(tree[node].left_child, false);
	maintain(tree[node].right_child, true);
	maintain(node, false);
	maintain(node, true);
}

void insert(int &node, int k)
{
	if (!node)
	{
		tree[node = ++siz].s = 1;
		tree[node].left_child = tree[node].right_child = 0;
		tree[node].key = k;
	}
	else
	{
		tree[node].s++;
		if (tree[node].key > k)
			insert(tree[node].left_child, k);
		else insert(tree[node].right_child, k);
		maintain(node, k >= tree[node].key);
	}
}

int select(int &node, int k)
{
	int v = tree[tree[node].left_child].s + 1;
	if (k == v) return tree[node].key;
	else if (k < v) return select(tree[node].left_child, k);
	else return select(tree[node].right_child, k - v);
}

int main()
{
	while (scanf("%d %d", &n, &k) != EOF)
	{
		char c;
		int x;
		int u = siz = tree[0].s = 0;
		while (n--)
		{
			scanf(" %c", &c);
			if (c == 'I')
			{
				scanf("%d", &x);
				insert(u, x);
			}
			else printf("%d\n", select(u, tree[u].s + 1 - k));
		}
	}
	return 0;
}
