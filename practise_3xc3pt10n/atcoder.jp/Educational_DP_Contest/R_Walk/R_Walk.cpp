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

#define debug(args...) { \
/* WARNING : do NOT compile this debug func calls with following flags: // \
 * // -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2*/ \
   string _s = #args; replace(_s.begin(), _s.end(), ',', ' ');\
   stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); \
}
void err(istream_iterator<string> it) { it->empty();
   cerr << " (Line : " << __LINE__ << ")" << '\n';
}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
	cerr << fixed << setprecision(15) << " [ " <<  *it << " : " << a  << " ] "<< ' ';
	err(++it, args...);
}

const int N = 55, MOD = (int)1e9 + 7;
inline int add (int a, int b)
{
   return (a + b) % MOD;
}
inline int mul (int a, int b) {
   return int(1ll*a*b % MOD);
}

struct Mat
{
   int sz;
   static const int mxn = 55, inf = (int)1e9;
   int M[mxn][mxn];

   Mat(int n_, int val = 0)
   {
      sz = n_;
      set(val);
   }

   Mat(const Mat& other)
   {
      sz = other.sz;
      for (int i = 0; i < sz; ++i)
         for (int j = 0; j < sz; ++j)
            M[i][j] = other.M[i][j];
   }

   void set(int val)
   {
      for (int i = 0; i < sz; ++i) for (int j = 0; j < sz; ++j)
            M[i][j] = val;
   }

   void make_I()
   {
      for (int i = 0; i < sz; ++i) for (int j = 0; j < sz; ++j)
         M[i][j] = (i == j ? 1 : 0);
   }

   Mat operator+(const Mat &other)  // O(n^2)
   {
      Mat sum(sz);
      for (int i = 0; i < sz; ++i)
         for (int j = 0; j < sz; ++j)
            sum.M[i][j] = add(M[i][j], other.M[i][j]);
      return sum;
   }

   Mat operator*(const Mat &other) // O(n^3)
   {
      Mat prod(sz);
      for (int i = 0; i < sz; ++i)
         for (int j = 0; j < sz; ++j)
            for (int k = 0; k < sz; ++k)
               prod.M[i][j] =
                  add(prod.M[i][j], mul(M[i][k], other.M[k][j]));
      return prod;
   }

   Mat pow(ll k) // O(n^3*logk)
   {
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

   Mat mx_op (const Mat &other)
   {
      Mat res(sz, -inf);
      for (int i = 0; i < sz; ++i) for (int j = 0; j < sz; ++j)
         for (int k = 0; k < sz; ++k)
            res.M[i][j] = max(res.M[i][j], M[i][k] + other.M[k][j]);

      return res;
   }

   Mat mn_op (const Mat &other)
   {
      Mat res(sz, inf);
      for (int i = 0; i < sz; ++i) for (int j = 0; j < sz; ++j)
         for (int k = 0; k < sz; ++k)
            res.M[i][j] = min(res.M[i][j], M[i][k] + other.M[k][j]);

      return res;
   }


   friend istream& operator >> (istream &is, Mat& o)
   {
      for (int i = 0; i < o.sz; ++i) for (int j = 0; j < o.sz; ++j)
            is >> o.M[i][j];
      return is;
   }

   friend ostream& operator << (ostream &os, const Mat& o)
   {
      for (int i = 0; i < o.sz; ++i) for (int j = 0; j < o.sz; ++j)
         os << o.M[i][j] << (j == o.sz -1 ? '\n' : ' ');
      return os;
   }

};

int n;
ll k;
int edge[N][N];

void solve()
{
   Mat G(n);
   cin >> G;
   G = G.pow(k);

   int total = 0;
   for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
         total = add(total, G.M[i][j]);
   cout << total << '\n';
}

signed main()
{
   IOS; PREC;
   cin >> n >> k;
   solve();

   return EXIT_SUCCESS;
}
