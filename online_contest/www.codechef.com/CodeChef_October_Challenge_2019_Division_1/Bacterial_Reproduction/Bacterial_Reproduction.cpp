#include      <bits/stdc++.h>
#include      <ext/pb_ds/assoc_container.hpp>
#include      <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define IOS       ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC      cout.precision (10); cout << fixed
#define x         first
#define y         second
#define fr(i,x,y) for (int i = x; i <= y; ++i)
#define fR(i,x,y) for (int i = x; i >= y; --i)
#define bg(x)     " [ " << #x << " : " << (x) << " ] "
#define un(x)     sort(x.begin(), x.end()), \
   x.erase(unique(x.begin(), x.end()), x.end())

using   ll  =     long long;
using   ull =     unsigned long long;
using   ff  =     long double;
using   pii =     pair<int,int>;
using   pil =     pair<int,ll>;
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
/*****************************************************************************/
//Don’t practice until you get it right. Practice until you can’t get it wrong

class seg_sum {
   public:
      using ll = long long;
      static const int MAXN = (int)2e6 + 10;
      ll seg[4 * MAXN], ar[MAXN];
      int sz;
      seg_sum(int n, vector <ll> Ar) {
         sz = n;
         for (int i = 0; i < sz; seg[i + sz] = Ar[i], ++i);
         build();
      }
      void build() {  // build the tree
         for (int i = sz - 1; i > 0; --i) seg[i] = seg[i << 1] + seg[i << 1|1];
      }
      void modify(int p, int value) {  // set value at position p
         for (seg[p += sz] += value; p > 1; p >>= 1) seg[p>>1] = seg[p] + seg[p^1];
      }
      ll query(int l, int r) {  // sum on interval [l, r)
         ++r;
         ll res = 0;
         for (l += sz, r += sz; l < r; l >>= 1, r >>= 1) {
            if (l&1) res += seg[l++];
            if (r&1) res += seg[--r];
         }
         return res;
      }
};

signed main() {
   IOS; PREC;
   const int D = 22;
   int n, q;
   cin >> n >> q;
   int m = n + q;

   vector <ll> ar(m), a_entry(2*m + 1), a_xit(2*m + 1);
   vector <vector <int>> T(m, vector <int>());
   vector <vector <int>> table(m, vector <int> (D + 1, -1));
   vector <int> euler, entry(m), xit(m), depth(m);
   vector <bool> is_leaf(m, false);

   for (int i = n; i < m - 1; ++i) {
      T[i].push_back(i + 1);
   }
   T[m - 1].push_back(0);

   for (int i = 0; i < n - 1; ++i) {
      int u, v;
      cin >> u >> v; --u, --v;
      T[u].push_back(v);
      T[v].push_back(u);
   }

   for (int i = 0; i < n; ++i)
      cin >> ar[i];

   function <void(int, int, int)> dfs = // O(ND)
      [&] (int u, int pr, int d) -> void {
         depth[u] = d;

         euler.push_back(u);
         entry[u] = (int)euler.size();
         a_entry[entry[u]] = ar[u];

         for (int k = 1; k <= D; ++k) if (table[u][k - 1] != -1)
            table[u][k] = table[table[u][k - 1]][k - 1];

         for (int v : T[u]) {
            if (v == pr) continue;
            table[v][0] = u;
            dfs(v, u, d + 1);
         }

         euler.push_back(u);
         xit[u] = (int)euler.size();
         a_xit[xit[u]] = ar[u];

         is_leaf[u] = (entry[u] + 1 == xit[u]);
      };

   auto walk = [&] (int u, int k) { // O(log(N))
      for (int d = 0; d <= D && u >= 0; ++d) {
         if ((1 << d) & k) u = table[u][d];
      }
      return u;
   };

   dfs(n, -1, 0);
   // assert((int)euler.size() == 2*m);
   seg_sum S_entry((int)euler.size() + 1, a_entry);
   seg_sum S_xit((int)euler.size() + 1, a_xit);

   struct Query {
      int u, time_el;
   };
   struct Update {
      int u, val, time_el;
   };
   vector <pair <int, ll>> answers;
   vector <vector <Update>> updates(n, vector <Update>());
   vector <vector <Query>> queries(n, vector <Query>());

   for (int i = 1; i <= q; ++i) {
      string qs; int u, val;
      cin >> qs;
      if (qs == "?") {
         cin >> u; --u;
         queries[u].push_back({u, i});
      }
      else {
         cin >> u >> val; --u;
         updates[u].push_back({u, val, i});
      }
   }

   vector <bool> visited(m, false);

   for (int i = entry[0]; i <= xit[0]; ++i) {
      int u = euler[i - 1];
      if (!visited[u]) { // update the system and answer the queries
         for (int j = 0; j < (int)updates[u].size(); ++j) {
            int tm = updates[u][j].time_el;
            int val = updates[u][j].val;
            int v = walk(u, tm);
            ar[v] += val;
            S_entry.modify(entry[v], val);
            S_xit.modify(xit[v], val);
         }
         for (int j = 0; j < (int)queries[u].size(); ++j) {
            int tm = queries[u][j].time_el;
            int v = walk(u, tm);
            if (!is_leaf[u]) { // for non-leaf
               answers.push_back(make_pair(tm, ar[v]));
            }
            else { // for leaf
               ll inc = S_xit.query(xit[u], xit[v]);
               ll exc = S_entry.query(xit[u], xit[v]);
               answers.push_back(make_pair(tm, inc - exc));
            }
         }
         visited[u] = true;
      }
      else { // remove the updates
         for (int j = 0; j < (int)updates[u].size(); ++j) {
            int tm = updates[u][j].time_el;
            int val = updates[u][j].val;
            int v = walk(u, tm);
            ar[v] -= val;
            S_entry.modify(entry[v], -val);
            S_xit.modify(xit[v], -val);
         }
      }
   }
   sort(answers.begin(), answers.end());
   for (auto el : answers) {
      cout << el.y << '\n';
   }

   return EXIT_SUCCESS;
}
