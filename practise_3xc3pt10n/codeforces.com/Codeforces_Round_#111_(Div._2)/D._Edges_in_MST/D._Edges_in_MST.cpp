#include      <bits/stdc++.h> /*{{{*/
#include      <ext/pb_ds/assoc_container.hpp>
#include      <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#ifndef CONVICTION
#pragma GCC       optimize ("Ofast")
#pragma GCC       optimize ("unroll-loops")
#pragma GCC       target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#endif

#define IOS       ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC      cout.precision (10); cout << fixed
#define x         first
#define y         second
#define fr(i,x,y) for (int i = int(x); i <= int(y); ++i)
#define fR(i,x,y) for (int i = int(x); i >= int(y); --i)
#define cnt(x)    __builtin_popcount(x)
#define cntll(x)  __builtin_popcountll(x)
#define bg(x)     " [ " << #x << " : " << (x) << " ] "
#define un(x)     sort(x.begin(), x.end()), \
  x.erase(unique(x.begin(), x.end()), x.end())
using   ll  =     long long;
using   ull =     unsigned long long;
using   ff  =     long double;
using   pii =     pair<int,int>;
using   pil =     pair<int,ll>;
using   vi  =     vector <int>;
using   vvi =     vector <vi>;
using   vp  =     vector <pii>;
using   vvp =     vector <vp>;
using   vl  =     vector<ll>;
typedef tree
< int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
ordered_set;

struct chash {
  int operator () (pii x) const { return x.x*31 + x.y; }
};
gp_hash_table <pii, int, chash> mp;

#if __cplusplus > 201103L
seed_seq seq{
  (uint64_t) chrono::duration_cast<chrono::nanoseconds>
    (chrono::high_resolution_clock::now().time_since_epoch()).count(),
    (uint64_t) __builtin_ia32_rdtsc(),
    (uint64_t) (uintptr_t) make_unique<char>().get()
};
mt19937 rng(seq); //uniform_int_distribution<int> (l, h)(rng); //[low, high]
#else
auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 rng(seed);
#endif

#define debug(args...) { \
  /* WARNING : do NOT compile this debug func calls with following flags: // \
   * // -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2*/ \
  string _s = #args; replace(_s.begin(), _s.end(), ',', ' ');\
  stringstream _ss(_s); \
  istream_iterator<string> _it(_ss); err(_it, args); \
}
void err(istream_iterator<string> it) {
  it->empty(); cerr << " (Line : " << __LINE__ << ")" << '\n';
}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
  cerr << fixed << setprecision(15)
    << " [ " <<  *it << " : " << a  << " ] "<< ' ';
  err(++it, args...);
}
/*}}}*/
/*****************************************************************************/
//Don’t practice until you get it right. Practice until you can’t get it wrong

signed main() {
  IOS; PREC;
  int n, m;
  cin >> n >> m;

  struct Edge {
    int u, v, w, id;
    bool operator < (const Edge &o) const {
      return w < o.w;
    }
  };
  vector <Edge> edges;

  fr(e, 1, m) {
    int u, v, w;
    cin >> u >> v >> w;
    --u, --v;
    edges.push_back({u, v, w, e-1});
  }
  sort (edges.begin(), edges.end());

  vector <vector <Edge>> layers;
  vector <Edge> t;

  t.push_back(edges[0]);
  fr(i, 1, m-1) {
    while (i <= m-1 && edges[i].w == t.back().w) {
      t.push_back(edges[i]);
      ++i;
    }
    layers.push_back(t);
    t.clear();
    if (i < m) t.push_back(edges[i]);
  }
  if (t.size()) layers.push_back(t);

  /*
     for (auto l : layers) if (l.size()) {
     for (Edge e : l) debug(e.u, e.v, e.w, e.id);
     cerr << endl;
     }
     */

  vi rep(n), rnk(n);
  fr(i, 0, n-1) rep[i] = i, rnk[i] = 1;

  function <int(int)> find_set = [&] (int x) -> int {
    return x == rep[x] ? x : rep[x] = find_set(rep[x]);
  };

  auto merge = [&] (int u, int v) {
    u = find_set(u), v = find_set(v);
    if (rnk[v] > rnk[u]) rep[u] = v;
    else rep[v] = u;
    if (rnk[v] == rnk[u]) ++rnk[u];
  };

  vector <string> ans(m, "yet");

  vi t_in(n), f(n), vis(n, false);
  int timer = 0;
  vvp G(n, vp());

  function <void(int, int)> dfs = [&] (int u, int last_id) -> void {
    debug(u, last_id);
    vis[u] = true;
    f[u] = t_in[u] = timer++;

    for (auto vpair : G[u]) {
      int v = vpair.x, id = vpair.y;
      if (id == last_id) continue;
      if (vis[v]) f[u] = min(f[u], t_in[v]);
      else dfs(v, id), f[u] = min(f[u], f[v]);

      // debug(u, v, t_in[u], t_in[v], f[u], f[v]);
      if (f[v] > t_in[u]) { // this is a bridge edge
        debug("marking bridge", u, v, t_in[u], t_in[v], f[u], f[v]);
        ans[id] = "any";
      }
    }
  };

  set <int> vertices;
  vector <Edge> take;
  for (auto l : layers) if (l.size()) {
    vertices.clear();
    take.clear();

    for (Edge &e : l) {
      e.u = rep[e.u], e.v = rep[e.v];
      int u = e.u, v = e.v, id = e.id;
      vertices.insert(u), vertices.insert(v);
      G[u].clear(), G[v].clear();
      if (u == v) ans[id] = "none";
      else {
        ans[id] = "at least one";
        take.push_back(e);
      }
    }

    for (Edge e : take) {
      int u = e.u, v = e.v, id = e.id;
      // debug(u, v, w, id);
      G[u].push_back(make_pair(v, id));
      G[v].push_back(make_pair(u, id));
      merge(u, v);
    }

    for (int v : vertices) vis[v] = false;
    for (int v : vertices) if (!vis[v]) dfs(v, -1);
  }

  fr(i, 0, m-1) cout << ans[i] << '\n';

  return EXIT_SUCCESS;
}
