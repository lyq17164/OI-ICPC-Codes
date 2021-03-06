#include <cstdio>
#include <climits>
#include <cstring>
using namespace std;
int f[3010], p[3010], a[3010];
int n, ml;
int main()
{
	memset(f, 0, sizeof(f));
	memset(p, 0, sizeof(p));
	scanf("%d", &n);
	ml = 1;
	p[0] = 1;
	a[0] = INT_MAX;
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		for (int j = 0; j < i; j++)
		{
			if (a[j] == a[i])
			{
				p[i] = 0;
				continue;
			}
			if (a[j] > a[i] && f[i] <= f[j] + 1)
			{
				if (f[i] == f[j] + 1) p[i] = (p[i] + p[j]) % 10000;
				else p[i] = p[j];
				f[i] = f[j] + 1;
			}
		}
		if (f[i] > ml) ml = f[i];
	}
	int pp = 0;
	for (int i = 1; i <= n; i++)
		if (f[i] == ml) pp = (pp + p[i]) % 10000;
	printf("%d %d", ml, pp);
	return 0;
}