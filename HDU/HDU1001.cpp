#include <cstdio>
using namespace std;

int work(int a)
{
	int ans = 0;
	for (int i = 1; i <= a; i++)
		ans += i;
	return ans;
}

int main()
{
	int a, b;
	while (scanf("%d", &a) != EOF)
	{
		printf("%d\n", work(a));
		printf("\n");
	}
	return 0;
}
