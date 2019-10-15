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

#include <bits/stdc++.h>
using namespace std;

class Mat {
   public:
      using ll = long long;
      static const int mxn = 1005, inf = (int)1e9, Mod = (int)1e9 + 7;
      constexpr static const long double OP = (long double) 1 / ((int)1e9 + 7);

      static inline int mul(int a, int b){
         long double res = a; res *= b;
         int c = (int)(res * OP);
         ll val = a * b - 1ll * c * Mod;
         if (val >= 1ll*Mod) val -= Mod;
         if (val < 0) val += Mod;
         return int(val);
      }

      static inline int add(int x, int y) {
         x += y;
         if (x >= Mod) x -= Mod;
         return x;
      }

      static inline int sub(int x, int y) {
         x -= y;
         if (x < 0) x += Mod;
         return x;
      }

      int sz;
      int M[mxn][mxn];

      Mat(int n_, int val = 0) {
         sz = n_;
         set(val);
      }

      Mat(const Mat& other) {
         sz = other.sz;
         for (int i = 0; i < sz; ++i)
            for (int j = 0; j < sz; ++j)
               M[i][j] = other.M[i][j];
      }

      void set(int val) {
         for (int i = 0; i < sz; ++i) for (int j = 0; j < sz; ++j)
            M[i][j] = val;
      }

      void make_I() {
         for (int i = 0; i < sz; ++i) for (int j = 0; j < sz; ++j)
            M[i][j] = (i == j ? 1 : 0);
      }

      Mat operator+(const Mat &other) {// O(n^2)
         Mat sum(sz);
         for (int i = 0; i < sz; ++i)
            for (int j = 0; j < sz; ++j)
               sum.M[i][j] = add(M[i][j], other.M[i][j]);
         return sum;
      }

      Mat operator*(const Mat &other) { // O(n^3) {
         Mat prod(sz);
         for (int i = 0; i < sz; ++i)
            for (int j = 0; j < sz; ++j)
               for (int k = 0; k < sz; ++k)
                  prod.M[i][j] =
                     add(prod.M[i][j], mul(M[i][k], other.M[k][j]));
         return prod;
      }

      Mat pow(long long k) { // O(n^3*logk)
         assert(k >= 0);
         Mat M_cp(*this), res(sz);
         res.make_I();

         while (k)
         {
            if (k & 1) res = res * M_cp;
            M_cp = M_cp * M_cp;
            k >>= 1;
         }
         return res;
      }

      Mat mx_op (const Mat &other) {
         Mat res(sz, -inf);
         for (int i = 0; i < sz; ++i) for (int j = 0; j < sz; ++j)
            for (int k = 0; k < sz; ++k)
               res.M[i][j] = max(res.M[i][j], M[i][k] + other.M[k][j]);

         return res;
      }

      Mat mn_op (const Mat &other) {
         Mat res(sz, inf);
         for (int i = 0; i < sz; ++i) for (int j = 0; j < sz; ++j)
            for (int k = 0; k < sz; ++k)
               res.M[i][j] = min(res.M[i][j], M[i][k] + other.M[k][j]);

         return res;
      }

      int gauss() {
         function <int(int, int)> expo;
         expo = [&] (int a, int x)->int {
            int res = 1;
            while (x){
               if (x & 1) res = mul(res, a);
               a = mul(a, a);
               x >>= 1;
            }
            return res;
         };
         int x;
         int i, j, k, p, counter = 0;

         for (i = 0; i < sz; i++){
            for (p = i, j = i + 1; j < sz && !M[p][i]; j++){
               p = j;
            }
            if (!M[p][i]) return -1;

            for (j = i; j < sz; j++){
               x = M[p][j], M[p][j] = M[i][j], M[i][j] = x;
            }

            if (p != i) counter++;
            for (j = i + 1; j < sz; j++){
               x = expo(M[i][i], sub(Mod, 2));
               x = mul(x, sub(Mod, M[j][i]));

               for (k = i; k < sz; k++){
                  M[j][k] = M[j][k] + mul(x, M[i][k]);
                  if (M[j][k] >= Mod) M[j][k] -= Mod;
               }
            }
         }
         return counter;
      }

      int determinant() { // O(n ^ 3)
         int i, j, free;
         int res = 1;

         for (i = 0; i < sz; i++){
            for (j = 0; j < sz; j++){
               if (M[i][j] < 0) M[i][j] += Mod;
            }
         }

         free = gauss();
         if (free == -1) return 0;

         for (i = 0; i < sz; i++) res = mul(res, M[i][i]);
         if (free & 1) res = sub(Mod, res);
         if ((Mod - res) < res) res = sub(res, Mod);
         return res;
      }


      friend istream& operator >> (istream &is, Mat& o) {
         for (int i = 0; i < o.sz; ++i) for (int j = 0; j < o.sz; ++j) {
            is >> o.M[i][j];
         }
         return is;
      }

      friend ostream& operator << (ostream &os, const Mat& o) {
         for (int i = 0; i < o.sz; ++i) for (int j = 0; j < o.sz; ++j) {
            os << o.M[i][j] << (j == o.sz -1 ? '\n' : ' ');
         }
         return os;
      }
      };

      const int MAX = 1005;
      const int N = 35;
      int D[MAX][MAX], A[MAX][MAX];
      int d[N][N], a[N][N];
      int n, m, k;

      void solve() {
         Mat Laplacian(n*k - 1);
         for (int ii = 0; ii < n*k - 1; ++ii) {
            for (int jj = 0; jj < n*k - 1; ++jj) {
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
               Laplacian.M[ii][jj] = D[ii][jj] - A[ii][jj];
            }
         }
         cout << Laplacian.determinant() << '\n';
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
            solve();
         }

         return EXIT_SUCCESS;
      }
