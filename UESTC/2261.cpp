#include <bits/stdc++.h>
#define fi first
#define se second
#define nowsta gethash(now[1].fi,now[2].fi,now[3].fi,now[4].fi)
using namespace std;

const int _24num=566;
const int _24flow[]={7,15,16,17,18,19,23,24,25,26,27,28,29,33,34,35,36,37,38,39,44,45,46,47,55,57,58,69,77,113,114,115,116,117,118,119,122,123,124,125,126,127,128,129,133,134,135,136,137,138,139,144,145,146,147,148,149,155,156,157,158,159,166,167,168,169,177,178,179,222,223,224,225,226,227,228,229,233,234,235,236,237,238,239,245,246,247,248,249,255,256,257,258,259,266,267,268,269,277,278,279,288,289,299,333,334,335,336,337,338,339,344,345,346,347,348,349,355,356,357,358,359,366,367,368,377,378,389,399,444,445,448,449,455,456,457,458,459,467,468,469,477,478,479,488,489,499,555,557,558,559,568,569,577,578,579,588,589,668,669,677,678,679,688,689,777,778,779,1112,1113,1114,1116,1117,1118,1119,1122,1123,1124,1125,1126,1127,1128,1129,1133,1134,1135,1136,1137,1138,1139,1144,1145,1146,1147,1148,1149,1155,1156,1157,1158,1159,1166,1167,1169,1177,1178,1179,1189,1199,1222,1224,1225,1226,1227,1228,1229,1233,1234,1235,1236,1237,1238,1239,1244,1245,1246,1247,1248,1249,1255,1256,1257,1258,1259,1266,1267,1268,1269,1277,1278,1279,1288,1289,1299,1333,1334,1335,1336,1337,1338,1339,1344,1345,1346,1347,1348,1349,1355,1356,1357,1358,1359,1366,1367,1368,1369,1377,1378,1379,1388,1389,1399,1446,1447,1448,1449,1455,1456,1457,1458,1459,1466,1467,1468,1469,1477,1478,1479,1489,1499,1555,1556,1557,1558,1559,1567,1568,1569,1577,1578,1579,1588,1589,1599,1667,1669,1677,1678,1689,1699,1777,1778,1779,1788,1789,1799,1899,2222,2223,2224,2225,2226,2227,2228,2229,2233,2234,2235,2236,2237,2238,2244,2245,2246,2248,2249,2255,2256,2257,2258,2259,2266,2267,2268,2277,2278,2279,2288,2289,2333,2334,2335,2336,2337,2338,2339,2344,2345,2346,2347,2348,2349,2355,2357,2358,2359,2366,2367,2368,2369,2378,2379,2388,2399,2445,2446,2447,2448,2455,2456,2457,2458,2459,2467,2468,2469,2477,2478,2488,2489,2499,2555,2556,2557,2558,2559,2566,2567,2568,2569,2577,2578,2579,2588,2589,2599,2666,2667,2668,2669,2677,2678,2688,2689,2699,2777,2778,2779,2788,2789,2799,2888,2889,2899,3333,3334,3335,3336,3337,3338,3339,3344,3345,3346,3347,3349,3357,3358,3359,3366,3367,3368,3369,3377,3378,3379,3399,3444,3445,3446,3447,3448,3449,3455,3456,3457,3458,3459,3466,3467,3468,3469,3477,3478,3479,3488,3489,3499,3555,3556,3557,3558,3559,3566,3567,3568,3569,3577,3578,3579,3588,3589,3599,3666,3667,3677,3678,3679,3688,3689,3699,3777,3778,3779,3788,3789,3799,3889,4444,4445,4448,4455,4456,4457,4466,4467,4469,4477,4478,4479,4488,4489,4499,4555,4556,4557,4558,4559,4566,4567,4568,4577,4578,4579,4588,4589,4599,4668,4669,4677,4678,4679,4689,4699,4777,4778,4779,4899,5555,5557,5558,5559,5568,5569,5577,5578,5579,5589,5669,5678,5679,5688,5699,5777,5778,5779,5788,5789,5889,5999,6689,6778,6779,6789,6799,7779};

bool judge[10000];

int T,n,m;
bool visa[7];
char s[3];
pair <int,bool> now[5],a[7],b[7];

int gethash(int a,int b,int c,int d)
{
	--a;--b;--c;--d;
	int x=min(min(a,b),min(c,d));
	if (x==a) a=~(1<<31);
	else if (x==b) b=~(1<<31);
	else if (x==c) c=~(1<<31);
	else d=~(1<<31);
	int y=min(min(a,b),min(c,d));
	if (y==a) a=~(1<<31);
	else if (y==b) b=~(1<<31);
	else if (y==c) c=~(1<<31);
	else d=~(1<<31);
	int z=min(min(a,b),min(c,d));
	if (z==a) a=~(1<<31);
	else if (z==b) b=~(1<<31);
	else if (z==c) c=~(1<<31);
	else d=~(1<<31);
	if (a!=~(1<<31)) return x*1000+y*100+z*10+a;
	if (b!=~(1<<31)) return x*1000+y*100+z*10+b;
	if (c!=~(1<<31)) return x*1000+y*100+z*10+c;
	return x*1000+y*100+z*10+d;
}

bool dfs(bool x,bool f)
{
	if (x)
	{
		if (judge[nowsta])
			if (!f||dfs(!x,false)) return true;
		for (int i=1;i<=n;i++)
			if (!visa[i])
				for (int j=1;j<=4;j++)
				{
					pair<int,bool> t1=a[i],t2=now[j];
					now[j]=t1;a[i]=t2;visa[i]=true;
					bool sta=dfs(!x,false);
					a[i]=t1;now[j]=t2;visa[i]=false;
					if (sta) return true;
				}
		return false;
	}
	else
	{
		if (!judge[nowsta]) return false;
		for (int i=1;i<=m;i++)
			if (b[i].se)
				for (int j=1;j<=4;j++)
				{
					pair<int,bool> t1=b[i],t2=now[j];
					now[j]=t1;b[i]=t2;
					bool sta=dfs(!x,false);
					b[i]=t1;now[j]=t2;
					if (!sta) return false;
				}
		return true;
	}
}

int main()
{
	for (int i=0;i<_24num;i++) judge[_24flow[i]]=true;
	scanf("%d",&T);
	while (T--)
	{
		for (int i=1;i<=4;i++)
		{
			scanf("%d",&now[i].fi);
			scanf("%s",s);
			if (s[0]=='b') now[i].se=true;
			else now[i].se=false;
		}
		scanf("%d %d",&n,&m);
		for (int i=1;i<=n;i++)
		{
			scanf("%d",&a[i].fi);
			scanf("%s",s);
			if (s[0]=='b') a[i].se=true;
			else a[i].se=false;
		}
		for (int i=1;i<=m;i++)
		{
			scanf("%d",&b[i].fi);
			scanf("%s",s);
			if (s[0]=='b') b[i].se=true;
			else b[i].se=false;
		}
		if (dfs(true,true)) puts("You are MengNan!");
		else puts("Gan si 25zai!");
	}
	return 0;
}