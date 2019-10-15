#include         <bits/stdc++.h>
#define x        first
#define y        second
using namespace std;
using pii = pair <int, int>;
using vi = vector <int>;
const int N = int(1e6) + 10;
int mp[N];
int vis[N], sz[N];
int idx = 0;
vector < vector <pii> > Adj;
int V, E;


int a[300001], W[N];

vi st[1200001];

void combine(int id)
{
	int l = id*2; int r = (l^1);
	st[id].resize(st[l].size()+st[r].size());
	merge(st[l].begin(),st[l].end(),st[r].begin(),st[r].end(),st[id].begin());
}

void build(int id, int l, int r)
{
	if(r-l<2)
	{
		st[id].push_back(a[l]);
		return ;
	}
	int mid=(l+r)>>1;
	build(id*2,l,mid);
	build(id*2+1,mid,r);
	combine(id);
}

const int LG = 20;

int solve(vi &vec, int v)
{
	int l = 0; int r = vec.size() - 1;
	int cur = 0;
	int ans = 0;
	for(int i = LG - 1; i >= 0; i--)
	{
		if(v&(1<<i))
		{
			int x = lower_bound(vec.begin()+l, vec.begin()+r+1, cur+(1<<i)) - vec.begin();
			if(l<=x-1)
			{
				r = min(r, x-1);
				ans+=(1<<i);
			}
			else
			{
				cur+=(1<<i);
			}
		}
		else
		{
			int x = lower_bound(vec.begin()+l, vec.begin()+r+1, cur+(1<<i)) - vec.begin();
			if(r>=x)
			{
				l = max(x,l);
				ans+=(1<<i);
				cur+=(1<<i);
			}
			else
			{

			}
		}
		//cerr<<i<<' '<<l<<' '<<r<<' '<<ans<<'\n';
	}
	return ans;
}

int query(int id, int l, int r, int ql, int qr, int v)
{
	if(ql<=l&&r<=qr) return solve(st[id],v);
	if(qr<=l||r<=ql) return -1;
	int mid = (l+r)>>1;
	return max(query(id*2,l,mid,ql,qr,v),query(id*2+1,mid,r,ql,qr,v));
}
void dfs (int u, int pr) {
    mp[idx++] = u;
    vis[u] = 1;
    sz[u] = 1;
    for (auto vPair : Adj[u]) {
        int v = vPair.x;
        if (v == pr) continue;
        if (!vis[v]) {
            dfs (v, u);
            sz[u] += sz[v];
        }
    }
}

void read() {
    cin.ignore();
	int n, u, v, q, k;
	int w = 1;
	cin >> n >> q;
	V = n, E = n - 1;
	Adj.assign(V, vector <pii>());

    for (int i = 0; i < n; ++i) {
        cin >> W[i];
    }

	for (int e = 0; e < E; ++e) {
		cin >> u >> v;
		--u, --v;
		Adj[u].emplace_back(pii(v, w));
		Adj[v].emplace_back(pii(u, w)); // undirected
	}
    dfs(0, -1);
    for (int i = 0; i < n; ++i) a[mp[i]] = W[i];
    build(1, 0, n);

	while(q--)
	{
        int l, r;
		cin >> u >> k;
        l = mp[u], r = mp[u] + sz[u] - 1;
		cout << query(1, 0, n, l, r + 1, k) << '\n';
	}
}

signed main() {
    read();

	return EXIT_SUCCESS;
}
