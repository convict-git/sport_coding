#include      <bits/stdc++.h>
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

struct Edge {
   int u, v, w;
   bool operator < (const Edge& other) const {
      return w < other.w;
   }
};

bool kruskal(int n, vector<Edge> &edges, vector <vector <pii>> &T) {
   vector <int> rnk(n, 1), rep(n, -1);

   for (int i = 0; i < n; ++i) {
      rep[i] = i, rnk[i] = 1;
   }

   auto find_set = [&] (int u) -> int {
      int x = u, temp;
      while (rep[u] != u)
         u = rep[u];
      while (rep[x] != x)
         temp = rep[x], rep[x] = u, x = temp;
      return u;
   };

   auto merge_set = [&] (int u, int v) -> void {
      int rep_u = find_set(u);
      int rep_v = find_set(v);
      if (rnk[rep_u] > rnk[rep_v]) rep[rep_v] = rep_u;
      else rep[rep_u] = rep_v;
      if (rnk[rep_u] == rnk[rep_v]) ++rnk[rep_v];
   };

   sort(edges.begin(), edges.end());
   int edge_cnt = 0;
   for (Edge e : edges) {
      int u = e.u, v = e.v, w = e.w;
      if (find_set(u) == find_set(v)) {
         continue;
      }
      T[u].push_back(make_pair(v, w));
      T[v].push_back(make_pair(u, w));
      merge_set(u, v);
      ++edge_cnt;
   }
   return (edge_cnt == n - 1);
}

signed main() {
   IOS; PREC;

   int n;
   cin >> n;
   vector <vector <int>> d(n, vector <int>(n, -1));
   vector <vector <int>> dist(n, vector <int>(n, INT_MAX));
   vector <vector<pii>> T(n, vector<pii>());
   vector <Edge> edges;
   bool ok = true;

   for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
         cin >> d[i][j];
         edges.push_back({i, j, d[i][j]});
         if (d[j][i] != -1 && d[j][i] != d[i][j])
            ok = false;

         if ((i == j && d[i][j] != 0) || (i != j && d[i][j] == 0)) {
            ok = false;
         }
      }
   }

   // apply kruskal and get adjacecy list
   bool is_mst = kruskal(n, edges, T);

   if (ok && is_mst) {
      for (int i = 0; i < n; ++i) {
         dist[i][i] = 0;
         function <void(int, int)> dfs =
            [&] (int u, int pr) -> void {
               for (auto v_pair : T[u]) {
                  int v = v_pair.x, w = v_pair.y;
                  if (v == pr) continue;
                  dist[i][v] = dist[i][u] + w;
                  dfs(v, u);
               }
            };
         dfs(i, -1);
      }

      for (int i = 0; i < n && ok; ++i) {
         for (int j =  i; j < n && ok; ++j) {
            if (d[i][j] != dist[i][j]) {
               ok = false;
            }
         }
      }
   }

   cout << (ok ? "YES\n" : "NO\n");

   return EXIT_SUCCESS;
}

