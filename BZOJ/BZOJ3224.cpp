#include <cstdio>
#define MAXN 101000
using namespace std;

struct SBT
{
	int left_child;
	int right_child;
	int s;
	int key;
};

SBT tree[MAXN];
int t, opt, x;
int siz, root;

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

void add(int &node, int k)
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
			add(tree[node].left_child, k);
		else add(tree[node].right_child, k);
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

int del(int &node, int v)
{
	tree[node].s--;
	int r;
	if ((v == tree[node].key) || (v < tree[node].key && !tree[node].left_child) || (v > tree[node].key && !tree[node].right_child))
	{
		r = tree[node].key;
		if (!tree[node].left_child || !tree[node].right_child)
			node = tree[node].left_child + tree[node].right_child;
		else tree[node].key = del(tree[node].left_child, tree[node].key + 1);
	}
	else
	{
		if (v < tree[node].key) return del(tree[node].left_child, v);
		else return del(tree[node].right_child, v);
	}
	return r;
}

bool exist(int &node, int v)
{
	if (!node) return false;
	if (v < tree[node].key) return exist(tree[node].left_child, v);
	else return (tree[node].key == v) || exist(tree[node].right_child, v);
}

int getrank(int &node, int v)
{
	if (!node) return 1;
	if (v <= tree[node].key) return getrank(tree[node].left_child, v);
	else return tree[tree[node].left_child].s + 1 + getrank(tree[node].right_child, v);
}

int prec(int &node, int v)
{
	if (!node) return v;
	if (v <= tree[node].key) return prec(tree[node].left_child, v);
	else
	{
		int r = prec(tree[node].right_child, v);
		if (r == v) return tree[node].key;
	}
}

int succ(int &node, int v)
{
	if (!node) return v;
	if (tree[node].key <= v) return succ(tree[node].right_child, v);
	else
	{
		int r = succ(tree[node].left_child, v);
		if (r == v) return tree[node].key;
	}
}

int main()
{
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d %d", &opt, &x);
		if (opt == 1) add(root, x);
		else if (opt == 2) del(root, x);
		else if (opt == 3) printf("%d\n", getrank(root, x));
		else if (opt == 4) printf("%d\n", select(root, x));
		else if (opt == 5) printf("%d\n", prec(root, x));
		else printf("%d\n", succ(root, x));
	}
	return 0;
}