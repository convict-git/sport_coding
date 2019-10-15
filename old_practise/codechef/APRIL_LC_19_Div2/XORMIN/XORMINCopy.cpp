#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define fbo find_by_order
#define ook order_of_key

typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<int> vi;
typedef long double ld;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> pbds;
typedef set<int>::iterator sit;
typedef map<int,int>::iterator mit;
typedef vector<int>::iterator vit;

int a[300001];

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
		st[id].pb(a[l]);
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

int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n; cin >> n;
	for(int i = 0; i < n; i++) cin>>a[i];
	build(1,0,n);
	int q; cin >> q;
	while(q--)
	{
		int l, r, x;
		cin>>l>>r>>x;
		l--; r--;
		cout<<query(1,0,n,l,r+1,x)<<'\n';
	}
}
