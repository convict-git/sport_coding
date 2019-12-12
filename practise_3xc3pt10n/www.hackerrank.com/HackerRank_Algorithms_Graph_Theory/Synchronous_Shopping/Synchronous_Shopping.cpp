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
#define fr(i,x,y) for (int i = (int)x; i <= (int)y; ++i)
#define rv(i,x,y) for (int i = (int)x; i >= (int)y; --i)
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
using   vl  =     vector<ll>;
using   vvi =     vector <vi>;
using   vp  =     vector <pii>;
using   vvp =     vector <vp>;
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

const int N = (int)1e3 + 10;
const ll inf = (ll)1e18;
ll dp[N][1 << 10];
bool vis[N][1 << 10];
vi A; vvp G;
int n, m, k;

struct Node {
  int u, mask; ll d;
  bool operator < (const Node&o) const {return d > o.d;}
};

void dijkstra () {
  priority_queue <Node> q;

  int sub_mask = A[0];
  dp[0][sub_mask] = 0;
  q.push(Node{0, sub_mask, 0});

  while (!q.empty()) {
    Node u_node = q.top();
    q.pop();
    int u = u_node.u, mask = u_node.mask;
    // if (u == n-1) debug(u, show_mask(mask), dp[u][mask]);
    if (vis[u][mask]) continue;
    vis[u][mask] = true;

    for (auto v_p : G[u]) {
      int v = v_p.x, w = v_p.y;
      int new_mask = mask | A[v];

      if (dp[v][new_mask] > dp[u][mask] + w) {
        dp[v][new_mask] = dp[u][mask] + w;
        q.push({v, new_mask, dp[v][new_mask]});
      }
    }
  }
}

signed main() {
   IOS; PREC;
   cin >> n >> m >> k;

   A.assign(n, 0);
   G.assign(n, vp());
   fr (i, 0, n-1) fr (mask, 0, (1 << k)-1)
     dp[i][mask] = inf, vis[i][mask] = false;

   fr (i, 0, n-1) {
     int t;
     cin >> t;
     int foo;
     fr (j, 0, t-1) cin >> foo, A[i] |= (1 << (foo-1));
   }

   fr(e, 0, m-1) {
     int u, v, w;
     cin >> u >> v >> w;
     --u, --v;
     G[u].emplace_back(v, w), G[v].emplace_back(u, w);
   }

   dijkstra();

   ll mn = inf;

   for (int f_mask = 0; f_mask < (1 << k); ++f_mask)
     for (int s_mask = 0; s_mask < (1 << k); ++s_mask)
       if ((f_mask | s_mask) == (1 << k) - 1) {
         mn = min(mn, max(dp[n-1][f_mask], dp[n-1][s_mask]));
       }

   cout << mn << '\n';
   return EXIT_SUCCESS;
}
