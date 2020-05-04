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
// #define cnt(x)    __builtin_popcount(x)
// #define cntll(x)  __builtin_popcountll(x)
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

const int MAX_P = 2101000;
set <int> primes = {2}, powers;
void sieve() {
  vector <bool> isPrime(MAX_P + 1, true);
  for (int i = 3; i*2 <= MAX_P; i += 2) {
    int p = 0;
    while (1ll * i*(i + p) <= MAX_P) isPrime[i*(i + p)] = false, ++p;
  }
  for (int i = 3; i <= MAX_P; i += 2) {
    if (isPrime[i]) primes.insert(i);
  }
}
struct Card { int idx, p, c, l; };
vector <Card> cards, ones;
int n;

const int N = 110, infi = (int)1e9;
const ll inf = 1ll * 1e18;
struct max_flow {
   int V;
   vector < vector <pii> > Adj;
   int Par[N];
   int cap[N][N], fcap[N][N];
   long long ds[N];

   max_flow(int V_) {
      V = V_;
      init();
   }

   void init () {
      assert(V);
      Adj.assign(V, vector <pii> ());
      for (int i = 0; i < V; ++i)
         for (int j = 0; j < V; ++j)
            fcap[i][j] = cap[i][j] = 0;
   }

   int spfa (int s, int t) {
      bool inQueue[N];
      int cnt[N];
      queue <int> q;
      for (int i = 0; i < V; ++i)
         ds[i] = inf, Par[i] = -1, inQueue[i] = false, cnt[i] = 0;

      ds[s] = 0, q.push(s), inQueue[s] = true;

      while (!q.empty()) {
         int u = q.front();
         q.pop();
         inQueue[u] = false;

         for (pii vPair : Adj[u])  {
            int v = vPair.first;
            long long cost = vPair.second;
            if (ds[v] > ds[u] + cost) {
               ds[v] = ds[u] + cost;
               Par[v] = u;
               if (!inQueue[v]) {
                  q.push(v);
                  inQueue[v] = true;
                  ++cnt[v];
                  assert (cnt[v] <= V); // negative cost cycle
               }
            }
         }
      }

      if (ds[t] == inf) return 0;
      int flow = infi;
      int cur = t;
      while (cur != s) {
         int prv = Par[cur];
         flow = min(flow, fcap[prv][cur]);
         cur = prv;
      }
      return flow;
   }

   long long min_cost_K_flow (int s, int t, int K = infi) {
      for (int i = 0; i < V; ++i)
         for (int j = 0; j < V; ++j)
            fcap[i][j] = cap[i][j];

      int flow = 0;
      int newFlow;
      long long cost = 0;

      while ((newFlow = spfa(s, t)) && flow < K) {
         newFlow = min(newFlow, K - flow);
         flow += newFlow;
         cost += newFlow * ds[t];

         int cur = t;
         while (cur != s) {
            int prv = Par[cur];
            fcap[prv][cur] -= newFlow;
            fcap[cur][prv] += newFlow;
            cur = prv;
         }
      }

      return flow;
      // assert (flow != 0); if (flow < K) return -1; // CHECK ERROR //TODO else return cost;
   }

   inline void addEdge (int u, int v, int flow,  long long cost = 0) {
      Adj[u].push_back(pii(v, cost));
      Adj[v].push_back(pii(u, cost));
      cap[u][v] = flow;
   }
};

int solve (int lvl) {
  max_flow G(n + 2);
  int sm = 0, idx = -1;
  for (int i = 0, mx = 0; i < (int)ones.size(); ++i) {
    if (ones[i].l <= lvl && mx <= ones[i].p) idx = i, mx = max(mx, ones[i].p);
  }

  if (idx != -1) {
    sm += ones[idx].p;
    G.addEdge(n, ones[idx].idx, ones[idx].p);
    for (int i = 0; i < (int)cards.size(); ++i) {
      if (primes.find(ones[idx].c + cards[i].c) != primes.end()) {
       G.addEdge(ones[idx].idx, cards[i].idx, infi);
      }
    }
  }

  for (int i = 0; i < (int)cards.size(); ++i) { // source and sink
    if (cards[i].l <= lvl) {
      sm += cards[i].p;
      if (cards[i].c & 1) G.addEdge(n, cards[i].idx, cards[i].p);
      else G.addEdge(cards[i].idx, n + 1, cards[i].p);
    }
  }

  for (int i = 0; i < (int)cards.size(); ++i) { // between two
    if (cards[i].l <= lvl) {
      for (int j = i + 1; j < (int)cards.size(); ++j) {
        if (cards[j].l <= lvl) {
          if (primes.find(cards[i].c + cards[j].c) != primes.end()) {
            if (cards[i].c & 1) G.addEdge(cards[i].idx, cards[j].idx, infi);
            else G.addEdge(cards[j].idx, cards[i].idx, infi); }
        }
      }
    }
  }
  int res = (int) G.min_cost_K_flow(n, n + 1);
  return sm - res;
}


signed main() {
  IOS; PREC;
  sieve();
  int k;
  cin >> n >> k;
  for (int i = 0; i < n; ++i) {
    int p, c, l;
    cin >> p >> c >> l;
    if (c == 1) ones.push_back({i, p, c, l});
    else cards.push_back({i, p, c, l});
  }

  int l = 1, h = n;

  while (l <= h) {
    int g = (l + h) / 2;
    int res = solve(g);
    if (res >= k) {
      h = g - 1;
    }
    else l = g + 1;
  }
  if (l > n) cout << -1 << "\n";
  else cout << l << '\n';

  return EXIT_SUCCESS;
}


