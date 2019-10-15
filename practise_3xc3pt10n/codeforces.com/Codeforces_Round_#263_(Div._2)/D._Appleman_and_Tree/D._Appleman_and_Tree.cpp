// dp on no. of sets (what kind of sets allowed? a set of connected vertices that either
// [contains one black vertex and/or some white vertices]
// or [contains all white vertices including root of the subtree]
//
// in[u] := no. of sets possible in subtree of u such
// that vertex u is already covered in some set with one black vertex
//
// out[u] := no. of sets possible in subtree of u such
// that vertex u is NOT already covered in some set with one black vertex
//
// let u be the parent and vi be the childs of u
//
// if u is black, in[u] --> either u has to be in seperate set
// or it can contain white vertices which were not yet included in some set which has one black vertex
//
// therefore in[u] = (in[v1] + out[v1]) * (in[v2] + out[v2]) * (...) * ...
// and out[u] = 0 (not possible, how can a black vertex not be already covered)
//
// if u is white,
// out[u] --> u is not covered in any set with one black vertex, so has two options
// either go with with white child vertices which are not covered yet or go alone
// therefore out[u] = (in[v1] + out[v1]) * (in[v2] + out[v2]) * (...) * ...
// and in[u] = chose one of the child that is already covered and go with that set (all the
// remaining white not covered child sets will also go in that set)
// hence in[u] = sum over i{(in[vi] * {mul of j(in[vj] + out[vj]), such that j != i}
//
// NOTE : the last recurrence can be done efficiently by finding the complete prod
// (which is already out[u] and multiplying by mod_inv((in[vi] + out[vi]), MOD) * in[vi]

#include         <bits/stdc++.h>
using namespace std;
#ifndef CONVICTION
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#endif

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define bg(x)    " [ " << #x << " : " << (x) << " ] "
#define x        first
#define y        second
using ll = long long;
using ff = long double;
using pii = pair<int,int>;

#define debug(args...) \
{ \
/* WARNING : do NOT compile this debug func calls with following flags: // \
 * // -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2*/ \
   string _s = #args; replace(_s.begin(), _s.end(), ',', ' ');\
   stringstream _ss(_s); \
   istream_iterator<string> _it(_ss); err(_it, args); \
}
void err(istream_iterator<string> it)
{
   it->empty(); cerr << " (Line : " << __LINE__ << ")" << '\n';
}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args)
{
	cerr << fixed << setprecision(15)
      << " [ " <<  *it << " : " << a  << " ] "<< ' ';
	err(++it, args...);
}

const int N = (int)1e5 + 10;
const int MOD = (int)1e9 + 7;
int n;
int col[N]; // 0 for white and 1 for black
int in[N], out[N];
vector <vector<int>> adj;
vector <bool> vis;
vector <int> order;

inline int add (int a, int b)
{
   return (a + b)%MOD;
}
inline int mul (int a, int b)
{
   return int(1ll*a*b % MOD);
}

inline int mul_inv (int a)
{
   // res = a ^ p-2
   int p = MOD - 2;
   int res = 1;
   while (p)
   {
      if (p & 1)
         res = mul(res, a);
      a = mul(a, a);
      p >>= 1;
   }
   return res;
}

void dfs (int u, int pr) {
   vis[u] = true;
   for (int i = 0; i < (int)adj[u].size(); ++i)
      if (adj[u][i] == pr) adj[u].erase(adj[u].begin() + i);

   for (int v : adj[u]) if (!vis[v]) dfs(v, u);
   order.push_back(u);
}

void solve() {
   order.clear();
   vis.assign(n, false);
   dfs(0, -1);

   for (int u : order) {
      if (col[u]) { // black
         in[u] = 1, out[u] = 0;
         for (int v : adj[u])
            in[u] = mul(in[u], add(in[v], out[v]));
      }
      else { // white
         in[u] = 0, out[u] = 1;

         for (int v : adj[u])
            out[u] = mul(out[u], add(in[v], out[v]));

         int prod = 1;
         for (int v : adj[u])
            prod = mul(prod, add(in[v], out[v]));

         for (int v : adj[u])
            in[u] = add(in[u], mul(in[v], mul(prod, mul_inv(add(out[v], in[v])))));
      }
   }

   cout << in[0] << '\n';
}

void read() {
   cin >> n;
   adj.assign(n, vector <int>());
   for (int i = 1; i < n; ++i) {
      int p; cin >> p;
      adj[i].push_back(p);
      adj[p].push_back(i);
   }

   for (int i = 0; i < n; ++i)
      cin >> col[i];
}

signed main()
{
   IOS; PREC;
   read(), solve();

   return EXIT_SUCCESS;
}
