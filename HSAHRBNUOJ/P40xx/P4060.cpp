#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 1<<10
using namespace std;

const long double pi = acos(-1.0);

struct Complex
{
	long double a, b;
	Complex() {}
	Complex(long double _a, long double _b): a(_a), b(_b) {}
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
};

struct Cellular_Automaton
{
	long long arr[MAXN];
} cell, base;

Complex a[MAXN], b[MAXN];
int n, m, d, k, L, rev[MAXN];
long long MOD;

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
		for (int i = 0; i < n; i++) c[i].a /= (long double)n;
	return ;
}

Cellular_Automaton Multiply(Cellular_Automaton x, Cellular_Automaton y)
{
	Cellular_Automaton z;
	memset(a, 0, sizeof a);
	memset(b, 0, sizeof b);
	for (int i = 0; i < n; i++)
	{
		a[i] = Complex(x.arr[n - i], 0);
		b[i + n] = b[i] = Complex(y.arr[i + 1], 0);
	}
	FFT(a, m, 1);
	FFT(b, m, 1);
	for (int i = 0; i < m; i++) a[i] = a[i] * b[i];
	FFT(a, m, -1);
	for (int i = 1; i <= n; i++) z.arr[i] = (long long)(a[(n << 1) - i].a + 0.5) % MOD;
	return z;
}

inline void read(int &x)
{
	x = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9') ch = getchar();
	while (ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
	return ;
}

inline void read(long long &x)
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
	read(MOD);
	read(d);
	read(k);
	for (int i = 1; i <= n; i++) read(cell.arr[i]);
	for (int i = 1; i <= d + 1; i++) base.arr[i] = 1;
	for (int i = n; i >= n - d + 1; i--) base.arr[i] = 1;
	for (m = 1, L = 0; m <= (n << 1); m <<= 1, L++);
	for (int i = 0; i < m; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1));
	while (k)
	{
		if (k & 1) cell = Multiply(cell, base);
		base = Multiply(base, base);
		k >>= 1;
	}
	for (int i = 1; i <= n; i++) printf("%lld%c", cell.arr[i] % MOD, i == n ? '\n' : ' ');
	return 0;
}