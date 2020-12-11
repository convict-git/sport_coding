#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef double db; 
typedef string str; 

typedef pair<int,int> pi;
typedef pair<ll,ll> pl; 
typedef pair<db,db> pd; 

typedef vector<int> vi; 
typedef vector<ll> vl; 
typedef vector<db> vd; 
typedef vector<str> vs; 
typedef vector<pi> vpi;
typedef vector<pl> vpl; 
typedef vector<pd> vpd; 

#define mp make_pair
#define f first
#define s second
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rall(x) (x).rbegin(), (x).rend() 
#define rsz resize
#define ins insert 
#define ft front() 
#define bk back()
#define pf push_front 
#define pb push_back
#define eb emplace_back 
#define lb lower_bound 
#define ub upper_bound 

#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define trav(a,x) for (auto& a: x)

const int MOD = 1e9+7; // 998244353;
const int MX = 1000005;
const ll INF = 1e18; 
const ld PI = acos((ld)-1);
const int xd[4] = {1,0,-1,0}, yd[4] = {0,1,0,-1}; 
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count()); 

template<class T> bool ckmin(T& a, const T& b) { 
	return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { 
	return a < b ? a = b, 1 : 0; } 
constexpr int pct(int x) { return __builtin_popcount(x); } 
constexpr int bits(int x) { return 31-__builtin_clz(x); } // floor(log2(x)) 
ll cdiv(ll a, ll b) { return a/b+((a^b)>0&&a%b); } // divide a by b rounded up
ll fdiv(ll a, ll b) { return a/b-((a^b)<0&&a%b); } // divide a by b rounded down
ll half(ll x) { return fdiv(x,2); }

template<class T, class U> T fstTrue(T lo, T hi, U f) {
	hi ++; assert(lo <= hi); // assuming f is increasing
	while (lo < hi) { // find first index such that f is true 
		T mid = half(lo+hi);
		f(mid) ? hi = mid : lo = mid+1; 
	} 
	return lo;
}
template<class T, class U> T lstTrue(T lo, T hi, U f) {
	lo --; assert(lo <= hi); // assuming f is decreasing
	while (lo < hi) { // find first index such that f is true 
		T mid = half(lo+hi+1);
		f(mid) ? lo = mid : hi = mid-1;
	} 
	return lo;
}
template<class T> void remDup(vector<T>& v) { 
	sort(all(v)); v.erase(unique(all(v)),end(v)); }

// INPUT
template<class A> void re(complex<A>& c);
template<class A, class B> void re(pair<A,B>& p);
template<class A> void re(vector<A>& v);
template<class A, size_t SZ> void re(array<A,SZ>& a);

template<class T> void re(T& x) { cin >> x; }
void re(db& d) { str t; re(t); d = stod(t); }
void re(ld& d) { str t; re(t); d = stold(t); }
template<class H, class... T> void re(H& h, T&... t) { re(h); re(t...); }

template<class A> void re(complex<A>& c) { A a,b; re(a,b); c = {a,b}; }
template<class A, class B> void re(pair<A,B>& p) { re(p.f,p.s); }
template<class A> void re(vector<A>& x) { trav(a,x) re(a); }
template<class A, size_t SZ> void re(array<A,SZ>& x) { trav(a,x) re(a); }

// TO_STRING
#define ts to_string
str ts(char c) { return str(1,c); }
str ts(const char* s) { return (str)s; }
str ts(str s) { return s; }
str ts(bool b) { 
	#ifdef LOCAL
		return b ? "true" : "false"; 
	#else 
		return ts((int)b);
	#endif
}
template<class A> str ts(complex<A> c) { 
	stringstream ss; ss << c; return ss.str(); }
str ts(vector<bool> v) {
	str res = "{"; F0R(i,sz(v)) res += char('0'+v[i]);
	res += "}"; return res; }
template<size_t SZ> str ts(bitset<SZ> b) {
	str res = ""; F0R(i,SZ) res += char('0'+b[i]);
	return res; }
template<class A, class B> str ts(pair<A,B> p);
template<class T> str ts(T v) { // containers with begin(), end()
	#ifdef LOCAL
		bool fst = 1; str res = "{";
		for (const auto& x: v) {
			if (!fst) res += ", ";
			fst = 0; res += ts(x);
		}
		res += "}"; return res;
	#else
		bool fst = 1; str res = "";
		for (const auto& x: v) {
			if (!fst) res += " ";
			fst = 0; res += ts(x);
		}
		return res;

	#endif
}
template<class A, class B> str ts(pair<A,B> p) {
	#ifdef LOCAL
		return "("+ts(p.f)+", "+ts(p.s)+")"; 
	#else
		return ts(p.f)+" "+ts(p.s);
	#endif
}

// OUTPUT
template<class A> void pr(A x) { cout << ts(x); }
template<class H, class... T> void pr(const H& h, const T&... t) { 
	pr(h); pr(t...); }
void ps() { pr("\n"); } // print w/ spaces
template<class H, class... T> void ps(const H& h, const T&... t) { 
	pr(h); if (sizeof...(t)) pr(" "); ps(t...); }

// DEBUG
void DBG() { cerr << "]" << endl; }
template<class H, class... T> void DBG(H h, T... t) {
	cerr << ts(h); if (sizeof...(t)) cerr << ", ";
	DBG(t...); }
#ifdef LOCAL // compile with -DLOCAL
	#define dbg(...) cerr << "LINE(" << __LINE__ << ") -> [" << #__VA_ARGS__ << "]: [", DBG(__VA_ARGS__)
#else
	#define dbg(...) 0
#endif

// FILE I/O
void setIn(str s) { freopen(s.c_str(),"r",stdin); }
void setOut(str s) { freopen(s.c_str(),"w",stdout); }
void unsyncIO() { ios_base::sync_with_stdio(0); cin.tie(0); }
void setIO(str s = "") {
	unsyncIO();
	// cin.exceptions(cin.failbit); 
	// throws exception when do smth illegal
	// ex. try to read letter into int
	if (sz(s)) { setIn(s+".in"), setOut(s+".out"); } // for USACO
}

/**
 * Description: The centroid of a tree of size $N$ is a vertex such that 
 	* after removing it, all resulting subtrees have size at most $\frac{N}{2}.$ 
 	* Supports updates in the form ``add 1 to all verts $v$ such that $dist(x,v)\le y$."
 * Time: O(N\log N) build, O(\log N) update and query
 * Memory: O(N\log N)
 * Source: own
 * Verification: 
	* solves https://dmoj.ca/problem/dmopc19c7p6
	* https://codeforces.com/contest/342/problem/E
	* Triway Cup 2019 G
 */

typedef pair<ll,int> T;
priority_queue<T,vector<T>,greater<T>> pq;
ll c[MX], dist[MX];
int ind[MX];

void ad(int x, ll y) {
	if (dist[x] != INF) return;
	dist[x] = y; if (c[x] == 0) return;
	pq.push({dist[x]+c[x],x});
};

int N,M,A,B;

void ad(vi& a, int b) { ckmin(b,sz(a)-1); if (b>=0) a[b]++; }
void prop(vi& a) { R0F(i,sz(a)-1) a[i] += a[i+1]; }
template<int SZ> struct Centroid {
	vi adj[SZ]; void ae(int a,int b){adj[a].pb(b),adj[b].pb(a);}
	bool done[SZ]; // processed as centroid yet
	int N,sub[SZ],cen[SZ],lev[SZ]; // subtree size, centroid anc
	int dist[32-__builtin_clz(SZ)][SZ]; // dists to all ancs
	vpi stor[SZ];
	void dfs(int x, int p) { sub[x] = 1; 
		trav(y,adj[x]) if (!done[y] && y != p) 
			dfs(y,x), sub[x] += sub[y]; 
	}
	int centroid(int x) {
		dfs(x,-1); 
		for (int sz = sub[x];;) {
			pi mx = {0,0};
			trav(y,adj[x]) if (!done[y] && sub[y] < sub[x]) 
				ckmax(mx,{sub[y],y});
			if (mx.f*2 <= sz) return x; 
			x = mx.s;
		}
	}
	int wut;
	void genDist(int x, int p, int lev) {
		dist[lev][x] = dist[lev][p]+1; 
		stor[wut].pb({dist[lev][x],x});
		// dbg("GENDIST",x,p,lev,dist[lev][x]);
		trav(y,adj[x]) if (!done[y] && y != p) genDist(y,x,lev); }
	void gen(int CEN, int _x) { // CEN = centroid above x
		int x = centroid(_x); done[x] = 1; cen[x] = CEN; 
		sub[x] = sub[_x]; lev[x] = (CEN == -1 ? 0 : lev[CEN]+1);
		wut = x;
		dist[lev[x]][x] = 0; stor[wut].pb({0,x});
		trav(y,adj[x]) if (!done[y]) genDist(y,x,lev[x]);
		sort(all(stor[wut]),[](const pi& a, const pi& b) { return a.f < b.f; });
		// dbg("HUH",wut,stor[wut]);
		trav(y,adj[x]) if (!done[y]) gen(x,y);
	}
	void init(int _N) { N = _N; FOR(i,1,N+1) done[i] = 0;
		gen(-1,1); } // start at vert 1
	void upd(int x, ll y) { 
		int cur = x;
		R0F(i,lev[x]+1) {
			int BIG = M-dist[i][x];
			while (ind[cur] < sz(stor[cur]) && stor[cur][ind[cur]].f <= BIG) {
				//dbg("HAHA",x,y,i,cur,stor[cur][ind[cur]]);
				ad(stor[cur][ind[cur]].s,y);
				ind[cur] ++;
			}
			if (i > 0) cur = cen[cur];
		}
	} // call propAll() after all updates
};

Centroid<1000001> C;

void solve(int tc) {
	cerr << "Doing #" << tc << "\n";
	re(N,M,A,B); 
	FOR(i,1,N+1) {
		C.adj[i].clear(), ind[i] = 0, dist[i] = INF;
		C.stor[i].clear();
	}
	FOR(i,1,N+1) {
		int p; re(p,c[i]);
		if (p) C.ae(p,i);
	}
	// FOR(i,1,N+1) dbg(i,)
	C.init(N);
	pq.push({0,A});
	while (sz(pq)) {
		auto a = pq.top(); pq.pop();
		//dbg(a);
		C.upd(a.s,a.f);
	}
	if (dist[B] == INF) dist[B] = -1;
	ps(dist[B]);
}

int main() {
	// setIO("A");
	int TC; re(TC);
	FOR(i,1,TC+1) {
		pr("Case #",i,": ");
		solve(i);
	}
}

/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and stay organized
	* WRITE STUFF DOWN
*/
