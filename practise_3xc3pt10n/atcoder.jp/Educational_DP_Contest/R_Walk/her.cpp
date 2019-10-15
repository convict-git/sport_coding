#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MOD = (int)1e9 + 7;
ll n;
inline int mul(int a, int b)
{
   return int(1ll*a*b % MOD);
}
inline int add (int a, int b)
{
   return (a + b)%MOD;
}

struct Mat
{
   int sz;
   static const int mxn = 55;
   int M[mxn][mxn];

   Mat(int n_)
   {
      sz = n_;
      reset();
   }

   Mat(const Mat& other)
   {
      sz = other.sz;
      for (int i = 0; i < sz; ++i)
         for (int j = 0; j < sz; ++j)
            M[i][j] = other.M[i][j];
   }

   void reset()
   {
      for (int i = 0; i < sz; ++i) for (int j = 0; j < sz; ++j)
            M[i][j] = 0;
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
      Mat M_cp(*this), res(sz);
      res.make_I();

      assert(k >= 0);
      while (k)
      {
         if (k & 1) res = res * M_cp;
         M_cp = M_cp * M_cp;
         k >>= 1;
      }
      return res;
   }

   friend istream& operator >> (istream &is, Mat& o)
   {
      for (int i = 0; i < o.sz; ++i) for (int j = 0; j < o.sz; ++j)
            cin >> o.M[i][j];
      return is;
   }
   friend ostream& operator << (ostream &os, const Mat& o)
   {
      for (int i = 0; i < o.sz; ++i) for (int j = 0; j < o.sz; ++j)
         os << o.M[i][j] << (j == o.sz -1 ? '\n' : ' ');
      return os;
   }

};

void solve()
{
   if (n == 1) cout << 1 << '\n';
   else if (n == 2) cout << 2 << '\n';
   else {
      Mat base(3);
      base.M[1][0] = base.M[2][1] = base.M[0][0] =  base.M[0][1] =  base.M[0][2] = 1;
      /*
       * dp(n) = dp(n-1) + dp(n-2) + dp(n-3)
       *
       *         | 1 1 1 |
       * base =  | 1 0 0 |
       *         | 0 1 0 |
       *
       * |dp(n)  |                    |dp(2)|
       * |dp(n-1)| = (base ^ (n-2)) * |dp(1)|
       * |dp(n-2)|                    |dp(0)|
       */

      base = base.pow(n-2);
      int ans = add(add(mul(base.M[0][0], 2), mul(base.M[0][1],1)), base.M[0][2]);
      cout << ans << '\n';
   }
}

signed main()
{
   int tc;
   cin >> tc;
   while (tc--) cin >> n, solve();
   return EXIT_SUCCESS;
}
