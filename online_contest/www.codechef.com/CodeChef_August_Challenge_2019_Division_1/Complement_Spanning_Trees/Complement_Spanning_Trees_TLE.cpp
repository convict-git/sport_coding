#include      <bits/stdc++.h>
#include      <ext/pb_ds/assoc_container.hpp>
#include      <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#pragma GCC   optimize ("Ofast")
#pragma GCC   optimize ("unroll-loops")
#pragma GCC   target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS   ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC  cout.precision (10); cout << fixed
#define x     first
#define y     second
#define bg(x) " [ " << #x << " : " << (x) << " ] "
#define un(x) sort(x.begin(), x.end()), \
   x.erase(unique(x.begin(), x.end()), x.end())
using   ll  = long long;
using   ull = unsigned long long;
using   ff  = long double;
using   pii = pair<int,int>;
using   pil = pair<int,ll>;
typedef tree
< int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
ordered_set;

struct chash {
   int operator()(pii x) const { return x.x*31 + x.y; }
};
gp_hash_table <pii, int, chash> mp;

seed_seq seq{
   (uint64_t) chrono::duration_cast<chrono::nanoseconds>
      (chrono::high_resolution_clock::now().time_since_epoch()).count(),
      (uint64_t) __builtin_ia32_rdtsc(),
      (uint64_t) (uintptr_t) make_unique<char>().get()
};
mt19937 rng(seq); //uniform_int_distribution<int> (l, h)(rng); //[low, high]

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

#define MAX 1501
const int MOD = 998244353;
const long double OP = (long double)1 / 998244353;

int mul(int a, int b){
   long double res = a;
   res *= b;
   int c = (int)(res * OP);
   ll val = a;
   val *= b;
   val -= 1ll * c * MOD;
   if (val >= 1ll*MOD) val -= MOD;
   if (val < 0) val += MOD;
   return int(val);
}

int add(int x, int y) {
   x += y;
   if (x >= MOD) x -= MOD;
   return x;
}

int sub(int x, int y) {
   x -= y;
   if (x < 0) x += MOD;
   return x;
}

int expo(int x, int n){
   int res = 1;
   while (n){
      if (n & 1) res = mul(res, x);
      x = mul(x, x);
      n >>= 1;
   }
   return res;
}

int gauss(int n, int ar[MAX][MAX]){
   int x;
   int i, j, k, p, counter = 0;

   for (i = 0; i < n; i++){
      for (p = i, j = i + 1; j < n && !ar[p][i]; j++){
         p = j;
      }
      if (!ar[p][i]) return -1;

      for (j = i; j < n; j++){
         x = ar[p][j], ar[p][j] = ar[i][j], ar[i][j] = x;
      }

      if (p != i) counter++;
      for (j = i + 1; j < n; j++){
         x = expo(ar[i][i], sub(MOD, 2));
         x = mul(x, sub(MOD, ar[j][i]));

         for (k = i; k < n; k++){
            ar[j][k] = ar[j][k] + mul(x, ar[i][k]);
            if (ar[j][k] >= MOD) ar[j][k] -= MOD;
         }
      }
   }
   return counter;
}

int determinant(int n, int ar[MAX][MAX]){
   int i, j, free;
   int res = 1;

   for (i = 0; i < n; i++){
      for (j = 0; j < n; j++){
         if (ar[i][j] < 0) ar[i][j] += MOD;
      }
   }

   free = gauss(n, ar);
   if (free == -1) return 0;

   for (i = 0; i < n; i++) res = mul(res, ar[i][i]);
   if (free & 1) res = sub(MOD, res);
   if ((MOD - res) < res) res = sub(res, MOD);
   return res;
}

const int N = 35;
int D[MAX][MAX], A[MAX][MAX], M[MAX][MAX];
int d[N][N], a[N][N];
int n, m, k;

void make_det() {
   for (int ii = 0; ii < n*k; ++ii) {
      for (int jj = 0; jj < n*k; ++jj) {
         int i = ii % n, j = jj % n, k_i = ii/n, k_j = jj/n;
         if (ii == jj) D[ii][jj] = (k - 1) * n + (n - 1 - d[i][j]);
         else D[ii][jj] = 0;
         if (k_i == k_j) {
            if (ii == jj) A[ii][jj] = 0;
            else {
               A[ii][jj] = 1^a[i][j];
            }
         }
         else {
            A[ii][jj] = 1;
         }
         M[ii][jj] = D[ii][jj] - A[ii][jj];
      }
   }
}

void read() {
   cin >> n >> m >> k;
   for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
         d[i][j] = 0, a[i][j] = 0;
   for (int e = 0; e < m; ++e) {
      int u, v;
      cin >> u >> v;
      --u, --v;
      ++d[u][u], ++d[v][v];
      ++a[u][v], ++a[v][u];
   }
}

signed main() {
   IOS; PREC;
   int tc;
   cin >> tc;
   while (tc--) {
      read();
      make_det();
      cout << determinant(n*k - 1, M) << '\n';
   }

   return EXIT_SUCCESS;
}
