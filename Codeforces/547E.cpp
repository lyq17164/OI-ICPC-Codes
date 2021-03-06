#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define SZ(x) ((int)x.size())
#define ALL(x) (x).begin(),(x).end()
#define lowbit(x) x&-x
#define pb push_back
#define ls (id<<1)
#define rs (id<<1|1)
#define Rint register int
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
const int MAXN=5e5+10,MAXM=4e6+10;
const int INF=INT_MAX,SINF=0x3f3f3f3f;
const ll llINF=LLONG_MAX;
const int MOD=1e9+7,mod=998244353;
const int inv2=5e8+4;
const int Lim=1<<20;

int tag[MAXN];

struct ACautomaton
{
	struct Node
	{
		int val,fail,son[26];
	}t[MAXN];
	int cnt,pa[MAXN];
	void insert_Trie(char *s,int val)
	{
		int u=0,n=strlen(s);
		for(int i=0;i<n;i++)
		{
			if(!t[u].son[s[i]-'a'])t[u].son[s[i]-'a']=++cnt,pa[cnt]=u;
			u=t[u].son[s[i]-'a'];
		}
		tag[val]=u;
	}
	queue<int> q;
	void getfail()
	{
		for(int i=0;i<26;i++)if(t[0].son[i])q.push(t[0].son[i]);
		while(!q.empty())
		{
			int u=q.front();q.pop();
			for(int i=0;i<26;i++)
			{
				if(t[u].son[i])
				{
					t[t[u].son[i]].fail=t[t[u].fail].son[i];
					q.push(t[u].son[i]);
				}
				else t[u].son[i]=t[t[u].fail].son[i];
			}
		}
	}
}G;

Vi g[MAXN];
ll sz[MAXN],in[MAXN],tot=1,out[MAXN];

void dfs(int u)
{
	in[u]=tot++;out[u]=1;
	for(auto j:g[u]) dfs(j),out[u]+=out[j];
}

ll tr[MAXN];

void add(int x,ll val)
{
	while(x<=G.cnt+10)
	{
		tr[x]+=val;
		x+=lowbit(x);
	}
}

ll query(int x)
{
	ll ans=0;
	while(x)
	{
		ans+=tr[x];
		x-=lowbit(x);
	}
	return ans;
}

Vi vec[MAXN];
char s[MAXN];
int l[MAXN],r[MAXN],k[MAXN];
ll ans[MAXN];

void solve()
{
	int n,q;
	R(n,q);
	for(int i=1;i<=n;i++)
	{
		R(s);
		G.insert_Trie(s,i);
	}
	G.getfail();
	for(int i=1;i<=G.cnt;i++)g[G.t[i].fail].pb(i);
	dfs(0);
	for(int i=1;i<=q;i++)
	{
		R(l[i],r[i],k[i]);
		vec[r[i]].pb(i);
		vec[l[i]-1].pb(i);
	}
	for(int i=0;i<=n;i++)
	{
		int u=tag[i];
		while(u)
		{
			add(in[u],1);
			u=G.pa[u];
		}
		for(auto j:vec[i])
		{
			ll op=1;
			if(i==l[j]-1)op=-1;
			ans[j]+=op*(query(in[tag[k[j]]]+out[tag[k[j]]]-1)-query(in[tag[k[j]]]-1));
		}
	}
	for(int i=1;i<=q;i++)W(ans[i]);
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int t=1;
	//R(t);
	while(t--)solve();
	return 0;
}