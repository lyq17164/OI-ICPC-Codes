#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 1<<17
using namespace std;

const double pi = acos(-1.0);

struct Complex
{
	double a, b;
	Complex() {}
	Complex(double _a, double _b): a(_a), b(_b) {}
	Complex(double _a): a(_a), b(0.0) {}
	inline Complex operator + (const Complex &z)const
	{
		return Complex(a + z.a, b + z.b);
	}
	inline Complex operator - (const Complex &z)const
	{
		return Complex(a - z.a, b - z.b);
	}
	inline Complex operator * (const Complex &z)const
	{
		return Complex(a * z.a - b * z.b, a * z.b + b * z.a);
	}
	inline Complex operator / (const Complex &z)const
	{
		double m = z.a * z.a + z.b * z.b;
		return Complex((a * z.a + b * z.b) / m, (z.a * b - z.b * a) / m);
	}
};

Complex a[MAXN], b[MAXN];
int len, L, n, rev[MAXN], ans[MAXN];
char _a[MAXN], _b[MAXN];

inline void FFT(Complex c[], int n, int f)
{
	Complex wn, w, x, y;
	for (int i = 0; i < n; i++)
		if (i < rev[i]) swap(c[i], c[rev[i]]);
	for (int i = 1; i < n; i <<= 1)
	{
		wn = Complex(cos(pi / i), sin(pi / i) * f);
		for (int p = i << 1, j = 0; j < n; j += p)
		{
			w = Complex(1, 0);
			for (int k = 0; k < i; k++, w = w * wn)
			{
				x = c[j + k];
				y = w * c[j + k + i];
				c[j + k] = x + y;
				c[j + k + i] = x - y;
			}
		}
	}
	if (!~f)
		for (int i = 0; i < n; i++) c[i].a /= (double)n;
	return ;
}

int main()
{
	scanf("%d", &n);
	len = n;
	scanf("%s%s", _a, _b);
	for (n = 1; n < (len << 1) - 1; n <<= 1, L++);
	for (int i = 0; i < n; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1));
	for (int i = 0; i < len; i++) a[i] = _a[len - i - 1] - '0';
	for (int i = 0; i < len; i++) b[i] = _b[len - i - 1] - '0';
	FFT(a, n, 1);
	FFT(b, n, 1);
	for (int i = 0; i < n; i++) a[i] = a[i] * b[i];
	FFT(a, n, -1);
	len <<= 1;
	for (int i = 0; i <= len; i++) ans[i] = (int)(a[i].a + 0.5);
	for (int i = 0; i <= len; i++)
		ans[i + 1] += ans[i] / 10, ans[i] %= 10;
	while (!ans[len] && len) len--;
	for (int i = len; ~i; i--) putchar(ans[i] + '0');
	putchar('\n');
	return 0;
}