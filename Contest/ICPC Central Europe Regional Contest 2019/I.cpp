#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define SZ(x) ((int)x.size())
#define lowbit(x) x&-x
#define pb push_back
#define ls (u<<1)
#define rs (u<<1|1)
#define mid ((l+r)>>1)
#define Rint register int
#define ALL(x) (x).begin(),(x).end()
#define UNI(x) sort(ALL(x)),x.resize(unique(ALL(x))-x.begin())
#define GETPOS(c,x) (lower_bound(ALL(c),x)-c.begin())
#define LEN(x) strlen(x)
#define MS0(x) memset((x),0,sizeof((x)))
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> Vi;
typedef vector<ll> Vll;
typedef vector<pii> Vpii;
template<class T> void _R(T &x) { cin >> x; }
void _R(int &x) { scanf("%d", &x); }
void _R(ll &x) { scanf("%lld", &x); }
void _R(ull &x) { scanf("%llu", &x); }
void _R(double &x) { scanf("%lf", &x); }
void _R(char &x) { scanf(" %c", &x); }
void _R(char *x) { scanf("%s", x); }
void R() {}
template<class T, class... U> void R(T &head, U &... tail) { _R(head); R(tail...); }
template<class T> void _W(const T &x) { cout << x; }
void _W(const int &x) { printf("%d", x); }
void _W(const ll &x) { printf("%lld", x); }
void _W(const double &x) { printf("%.16f", x); }
void _W(const char &x) { putchar(x); }
void _W(const char *x) { printf("%s", x); }
template<class T,class U> void _W(const pair<T,U> &x) {_W(x.F); putchar(' '); _W(x.S);}
template<class T> void _W(const vector<T> &x) { for (auto i = x.begin(); i != x.end(); _W(*i++)) if (i != x.cbegin()) putchar(' '); }
void W() {}
template<class T, class... U> void W(const T &head, const U &... tail) { _W(head); putchar(sizeof...(tail) ? ' ' : '\n'); W(tail...); }
const int MOD=1e9+7,mod=1e9+9;
ll qpow(ll a,ll b) {ll res=1;a%=MOD; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%MOD;a=a*a%MOD;}return res;}
const int MAXN=2e6+10,MAXM=2e7+10;
const int INF=INT_MAX,SINF=0x3f3f3f3f;
const ll llINF=LLONG_MAX;
const int inv2=5e8+4;
const int Lim=1<<20;

int n,m,q;
int u[MAXN],v[MAXN];
Vi g[MAXN];

int fa[MAXN];
int _find(int x)
{
	return fa[x]^x?fa[x]=_find(fa[x]):fa[x];
}

void solve()
{
	R(n,m,q);
	for(int i=1;i<=m;i++)
	{
		R(u[i],v[i]);
		g[u[i]].pb(v[i]);
		g[v[i]].pb(u[i]);
	}
	for(int i=1;i<=n;i++)sort(ALL(g[i]));
	int L=10;
	while(q--)
	{
		int p;R(p);
		Vi query(p);
		for(int i=0;i<p;i++)R(query[i]);
		if(p>L)
		{
			for(int i=1;i<=n;i++)fa[i]=0;
			for(auto j:query)fa[j]=j;
			for(int i=1;i<=m;i++)
			{
				int uu=_find(u[i]),vv=_find(v[i]);
				if(!uu||!vv)continue;
				fa[uu]=vv;
			}
			set<int> s;
			for(auto j:query)s.insert(_find(j));
			W(SZ(s));
		}
		else
		{
			for(auto j:query)fa[j]=j;
			for(int i=0;i<SZ(query);i++)
				for(int j=i+1;j<SZ(query);j++)
				{
					int u=query[i],v=query[j];
					if(_find(u)==_find(v))continue;
					int t=GETPOS(g[u],v);
					if(t<SZ(g[u])&&g[u][t]==v)
					{
						fa[_find(u)]=_find(v);
					}
				}
			set<int> s;
			for(auto j:query)s.insert(_find(j));
			W(SZ(s));
		}
	}
}

int main()
{
	int t=1;
	//R(t);
	while(t--)solve();
	return 0;
}