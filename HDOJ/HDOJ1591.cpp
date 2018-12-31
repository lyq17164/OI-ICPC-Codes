#include <cstdio>
#include <cstring>
using namespace std;

char s[130], t[130];
char c;

void pre_work()
{
	int n = strlen(t);
	for (int i = 0; i < n; i++) s[i] = t[i];
	int flag = 25;
	for (int i = 25; ~i; i--)
	{
		int j;
		for (j = 0; j < n; j++)
			if ('Z' - i == t[j]) break;
		if (j == n) s[flag--] = 'Z' - i;
	}
}

int main()
{
	//freopen("a.txt","r",stdin);freopen("aout.txt","w",stdout);
	scanf("%s", t);
	getchar();
	pre_work();
	while (~scanf("%c", &c))
	{
		int i;
		for (i = 0; i < 26; i++)
		{
			if (c == s[i])
			{
				printf("%c", i + 'A');
				break;
			}
			else if (c == s[i] + 32)
			{
				printf("%c", i + 'a');
				break;
			}
		}
		if (i == 26) printf("%c", c);
	}
	return 0;
}

