#include <bits/stdc++.h>
using namespace std;
struct Mat {
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
               prod.M[i][j] = add(prod.M[i][j], mul(M[i][k], other.M[k][j]));
      return prod;
   }

   Mat pow(long long k) { // O(n^3*logk)
      assert(k >= 0);
      Mat M_cp(*this), res(sz);
      res.make_I();

      while (k) {
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

   int det() { // O(n ^ 3)
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
      for (int i = 0; i < o.sz; ++i) for (int j = 0; j < o.sz; ++j)
         is >> o.M[i][j];
      return is;
   }

   friend ostream& operator << (ostream &os, const Mat& o) {
      for (int i = 0; i < o.sz; ++i) for (int j = 0; j < o.sz; ++j)
         os << o.M[i][j] << (j == o.sz -1 ? '\n' : ' ');
      return os;
   }
   };

   int main() {
      cout << 4 << '\n';
   }
