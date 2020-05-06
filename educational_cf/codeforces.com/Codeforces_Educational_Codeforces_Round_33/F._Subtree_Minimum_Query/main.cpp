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
#define X         first
#define Y         second
#define sz(x)     (int)x.size()
#define fr(i,x,y) for (int i = (int)x; i <= (int)y; ++i)
#define rv(i,x,y) for (int i = (int)x; i >= (int)y; --i)
#define bcnt(x)   __builtin_popcount(x)
#define bcntll(x) __builtin_popcountll(x)
#define bg(x)     " [ " << #x << " : " << (x) << " ] "
#define un(x)     sort(x.begin(), x.end()), \
  x.erase(unique(x.begin(), x.end()), x.end())
using   ll  =     long long;
using   ull =     unsigned long long;
using   ff  =     long double;
using   pii =     pair<int,int>;
using   pil =     pair<int,ll>;
using   pll =     pair<ll,ll>;
using   vi  =     vector <int>;
using   vl  =     vector<ll>;
using   vvi =     vector <vi>;
using   vvl =     vector <vl>;
using   vp  =     vector <pii>;
using   vvp =     vector <vp>;
typedef tree
< int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
ordered_set;

struct chash {
  int operator () (pii x) const { return x.X*31 + x.Y; }
};
gp_hash_table <pii, int, chash> gmp;

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

#ifdef CONVICTION
void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}

template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]" << endl;}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif
//         __                                           __
//        (**)                                         (**)
//        IIII                                         IIII
//        ####                                         ####
//        HHHH     Madness comes, and madness goes     HHHH
//        HHHH    An insane place, with insane moves   HHHH
//        ####   Battles without, for battles within   ####
//     ___IIII___        Where evil lives,          ___IIII___
//  .-`_._"**"_._`-.      and evil rules         .-`_._"**"_._`-.
// |/``  .`\/`.  ``\|    Breaking them up,      |/``  .`\/`.  ``\|
// `     }    {     '  just breaking them in    `     }    {     '
//       ) () (  Quickest way out, quickest way wins  ) () (
//       ( :: )      Never disclose, never betray     ( :: )
//       | :: |   Cease to speak or cease to breath   | :: |
//       | )( |        And when you kill a man,       | )( |
//       | || |          you're a murderer            | || |
//       | || |             Kill many                 | || |
//       | || |        and you're a conqueror         | || |
//       | || |        Kill them all ... Ooh..        | || |
//       | || |           Oh you're a God!            | || |
//       ( () )                       -Megadeth       ( () )
//        \  /                                         \  /
//         \/                                           \/
/*}}}*/
/*****************************************************************************/
//Don’t practice until you get it right. Practice until you can’t get it wrong

vector <int> mark;
vector <int> mp;

class seg_less { /*{{{*/
  // Recurisve Segment Tree with lazy propogation for "less than" library
  // This library is created by Priyanshu Shrivastav (mr.convict)
  // https://github.com/convict-git/sport_coding/blob/master/cplib/snippets/segment_tree_less.cpp
  using ll = long long;
  public:
    static const int MXN = (int)2e5 + 10;
    int sz;
    int ar[MXN];
    int lz[4 * MXN];

    struct Node {
      int sz, bg;
      pair <int, int> *v;
      int *minNode;

      void update_node(Node left, Node right) {
        assert (sz == left.sz + right.sz);
        for (int i = 0; i < left.sz; ++i) v[i] = left.v[i];
        for (int i = 0; i < right.sz; ++i) v[i + left.sz] = right.v[i];
        sort (v, v + sz);
        minNode[0] = mark[mp[v[0].second]];
        for (int i = 1; i < sz; ++i) {
          minNode[i] = min(minNode[i - 1], mark[mp[v[i].second]]);
        }
      }

      void add_val (int x) {
        for (int i = 0; i < sz; ++i) v[i].first += x;
      }

      int get (int x) {
        int l = 0, h = sz - 1;
        while (l <= h) {
          int g = (l + h)/2;
          if (v[g].first <= x) l = g + 1;
          else h = g - 1;
        }
        return (h >= 0 ? minNode[h] : INT_MAX);
      }
    };

    Node seg[4 * MXN];

    seg_less(int n, vector <int> Ar) {
      sz = n;
      assert((int)Ar.size() == n);
      for (int i = 0; i < sz; ar[i] = Ar[i], ++i);
      create(0, n - 1, 0);
    }

    void create (int l, int r, int x) {
      seg[x].bg = l;
      seg[x].sz = r - l + 1;
      seg[x].v = new pair <int, int> [seg[x].sz];
      seg[x].minNode = new int [seg[x].sz];

      if (l == r)
      {
        seg[x].v[0] = make_pair(ar[l], l);
        seg[x].minNode[0] = mark[mp[l]];
        return;
      }
      int mid = (l + r)/2;
      create(l, mid, x + x + 1);
      create(mid + 1, r, x + x + 2);
      seg[x].update_node(seg[x + x + 1], seg[x + x + 2]);
    }

    void lz_upd(int l, int r, int x) {
      if (lz[x] != 0) {
        seg[x].add_val(lz[x]);
        if (l != r)
        {
          lz[x + x + 1] += lz[x];
          lz[x + x + 2] += lz[x];
        }
        lz[x] = 0;
        return;
      }
    }

    void upd(int ql, int qr, int val, int l, int r, int x) {
      lz_upd(l, r, x);
      if (l > qr || r < ql) return;
      if (l >= ql && r <= qr) {
        seg[x].add_val(val);
        if (l != r)
        {
          lz[x + x + 1] += val;
          lz[x + x + 2] += val;
        }
        return;
      }
      int mid = (l + r)/2;
      upd(ql, qr, val, l, mid, x + x + 1);
      upd(ql, qr, val, mid + 1, r, x + x + 2);
      seg[x].update_node(seg[x + x + 1], seg[x + x + 2]);
    }

    int get (int ql, int qr, int l, int r, int x, int limit) {
      lz_upd(l, r, x);
      if (l > qr || r < ql) return INT_MAX;
      if (l >= ql && r <= qr) return seg[x].get(limit);

      int mid = (l + r)/2;
      int lq = get(ql, qr, l, mid, x + x + 1, limit);
      int rq = get(ql, qr, mid + 1, r, x + x + 2, limit);
      return min(lq, rq);
    }

    void update_range (int ql, int qr, int val) {
      upd(ql, qr, val, 0, sz - 1, 0);
    }

    int query_range_less (int ql, int qr, int limit) {
      return get (ql, qr, 0, sz - 1, 0, limit);
    }
}; /*}}}*/

void solve() {
  int n, r;
  cin >> n >> r;
  mark.assign(n, 0);
  mp.assign(2 * n, 0);
  for (int i = 0; i < n; ++i) cin >> mark[i];

  int idx = 0;
  vector <int> F(n), L(n);
  vector <int> depth(n);
  vector <vector <int>> T(n, vector <int>());
  vector <int> euler;

  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    cin >> u >> v;
    --u, --v;
    T[u].push_back(v);
    T[v].push_back(u);
  }

  vector <bool> vis(n);
  function <void(int, int)> dfs = [&] (int u, int d) {
    vis[u] = true;
    depth[u] = d;
    mp[idx] = u;
    F[u] = idx++;

    for (int v : T[u]) if (!vis[v])
      dfs(v, d + 1);

    mp[idx] = u;
    L[u] = idx++;
  };

  dfs(r - 1, 0);

  vector <int> ar(2 * n);
  for (int i = 0; i < 2 * n; ++i) {
    ar[i] = depth[mp[i]];
  }

  seg_less ST(2 * n, ar);

  int q;
  cin >> q;
  int lst = 0;
  while (q--) {
    int pp, qq;
    cin >> pp >> qq;
    int x = (pp + lst) % n + 1;
    int k = (qq + lst) % n;
    --x;
    // dist(y, x) = depth[y] - depth[x] <= k
    // depth[y] <= depth[x] + k

    int res = ST.query_range_less(F[x], L[x], k + depth[x]);
    cout << res << '\n';
    lst = res;
  }
}

signed main() {
  IOS; PREC;
  int tc = 1;
  // cin >> tc;
  for (int Tt = 1; Tt <= tc; ++Tt) {
    // cout << "Case #" << Tt << ": ";
    solve();
  }
  return EXIT_SUCCESS;
}
