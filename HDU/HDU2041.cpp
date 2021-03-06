#include <cstdio>
#define MAXN 50
#define MOD 2333333
using namespace std;

long long f[MAXN];
int n, t;

void pre_work()
{
	f[1] = 1;
	f[2] = 2;
	for (int i = 3; i <= MAXN; i++)
		f[i] = (f[i - 1] + f[i - 2]); //%MOD;
	return ;
}

int main()
{
	pre_work();
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &n);
		printf("%lld\n", f[n - 1]);
	}
	return 0;
}

