#include         <bits/stdc++.h>
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define x        first
#define y        second
using namespace std;
using pii = pair <int, int>;

const int N = 55;
const long double inf = 1e9, eps = 1e-9;

long double C[N][N], d[N][N];
bool isEdge[N][N];
pii point[N];
int n, m;
inline bool feq(long double a, long double b) {
   return abs(a - b) < eps;
}

inline long double dist(int u, int v) {
   return hypot (point[u].x - point[v].x, point[u].y - point[v].y);
}

struct ans {
   int u, v;
   long double w, dval;

   ans(int _u, int _v) : u(min(_u, _v)), v(max(_u, _v)) { w = C[u][v], dval = dist(u, v); }
   ans() : u(-1), v(-1), w(-1), dval(-1) {}

   inline bool operator < (const ans &other) const {
      if (!feq(w, other.w)) return w < other.w;
      if (!feq(dval, other.dval)) return dval > other.dval;
      if (u != other.u) return u > other.u;
     if (v != other.v) return v > other.v;
      return false;
   }
   bool isNotValid () { return w + eps < 1.0; }
};

void FloydWarshall() {
   for (int k = 0; k < n; ++k)
      for (int i = 0; i < n; ++i)
         for (int j = 0; j < n; ++j)
            if (d[i][k]  + eps < inf && d[k][j] + eps < inf)
               if (d[i][j] + 2 * eps > d[i][k] + d[k][j])
                  d[i][j] = d[i][k] + d[k][j];
}

void solve() {
   FloydWarshall();

   ans Ans;

   for (int u = 0; u < n; ++u) {
      for (int v = 0; v < n; ++v) {
         if (u == v) continue;
         if (isEdge[u][v]) continue;
         C[u][v] = 0;
         for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
               if (i == j) continue;
               long double mn;
               if (d[i][u] + d[v][j] < d[i][v] + d[u][j] + 2 * eps)
                  mn = d[i][u] + d[v][j];
               else mn = d[i][v] + d[u][j];

               mn += dist(u, v);
               if (mn + eps < d[i][j]) C[u][v] += d[i][j] - mn;
            }
         }

         Ans = max(Ans, ans(u, v));
      }
   }
   if (Ans.isNotValid()) cout << "No road required\n";
   else cout << Ans.u + 1 << ' ' << Ans.v + 1 << '\n';
}

void read() {
   while (cin >> n >> m, n || m) {
      for (int i = 0; i < n; ++i) {
         for (int j = 0; j < n; ++j) {
            d[i][j] = (i == j ? 0 : inf);
            isEdge[i][j] = false;
         }
      }

      int u, v;
      for (int i = 0; i < n; ++i)
         cin >> point[i].x >> point[i].y;
      for (int i = 0; i < m; ++i) {
         cin >> u >> v;
         --u, --v;
         isEdge[v][u] = isEdge[u][v] = true;
         d[v][u] = d[u][v] = dist(u, v);
      }
      solve();
   }
}

signed main() {
   IOS; PREC;
   read();
   return EXIT_SUCCESS;
}

