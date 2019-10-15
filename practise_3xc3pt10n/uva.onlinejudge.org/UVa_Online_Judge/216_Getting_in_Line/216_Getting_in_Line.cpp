#include         <bits/stdc++.h>
using namespace std;
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (2); cout << fixed
#define bg(x)    " [ " << #x << " : " << (x) << " ] "
#define x        first
#define y        second
using ll = long long;
using ld = long double;
using pii = pair<int,int>;

#define debug(args...) { \
   string _s = #args; replace(_s.begin(), _s.end(), ',', ' ');\
   stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); \
}
void err(istream_iterator<string> it) { it->empty();
   cerr << " (Line : " << __LINE__ << ")" << '\n';
}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
   cerr << " [ " <<  *it << " : " << a  << " ] "<< ' ';
   err(++it, args...);
}
const int N = 10, infi = (int)1e9;
const ld eps = 1e-9;
vector <pii> point;
int n;
ld memo[N][1 << N], dp[N][1 << N];
int par[N][1 << N];

inline ld dist(int s, int e) {
   int sx, sy, ex, ey;
   sx = point[s].x, sy = point[s].y;
   ex = point[e].x, ey = point[e].y;
   return hypot(sx-ex, sy-ey);
}
/*****************************BOTTOM UP SOLUTION starts*************************/
void solve_bu_tsp(int tc) { // tsp bottom up solution
   cout << "**********************************************************\n";
   cout << "Network #" << tc << "\n";

   for (int mask = 0; mask < (1 << n); ++mask)
      for (int i = 0; i < n; ++i)
         dp[i][mask] = infi;

   for (int i = 0; i < n; ++i)
      dp[i][1 << i] = 0, par[i][1 << i] = -1;

   for (int mask = 1; mask < (1 << n); ++mask) {
      for (int pos = 0; pos < n; ++pos) {
         if (!(mask & (1 << pos))) continue;
         ld mn_val = (ld) infi;
         for (int prv = 0; prv < n; ++prv) {
            if (pos == prv || !(mask & (1 << prv)))
               continue;
            ld guess = dp[prv][mask-(1<<pos)] + dist(prv, pos);
            if (mn_val > guess) {
               mn_val = guess;
               par[pos][mask] = prv;
            }
         }
         dp[pos][mask] = min(dp[pos][mask], mn_val);
      }
   }

   ld mn_cycle = (ld) infi, total = 0;
   int pos = -1, mask = (1 << n) - 1;
   for (int i = 0; i < n; ++i) {
      ld go = dp[i][mask];
      if (mn_cycle > go) {
         mn_cycle = go;
         pos = i;
      }
   }

   vector <int> order = {pos};
   while (pos != -1) {
      order.push_back(par[pos][mask]);
      int tmp = pos;
      pos = par[pos][mask];
      mask -= (1 << tmp);
   }

   for (int i = 1; i < n; ++i) {
      int sx, sy, ex, ey;
      sx = point[order[i-1]].x, sy = point[order[i-1]].y;
      ex = point[order[i]].x, ey = point[order[i]].y;
      ld wt = dist(order[i-1], order[i]) + 16;
      cout << "Cable requirement to connect (" << sx << "," << sy << ") to ("
         << ex << "," << ey << ") is " << wt<< " feet.\n";
      total += wt;
   }
   cout << "Number of feet of cable required is " << total << ".\n";
   assert(fabs(total - mn_cycle - (n-1)*16) < eps);
}
/*****************************BOTTOM UP SOLUTION end *************************/

/*****************************TOP DOWN SOLUTION starts*************************/
ld tsp (int pos, int mask) {
   if (mask == (1 << n) - 1) return 0;
   if (memo[pos][mask] > -1 + eps) return memo[pos][mask];

   ld mn_val = (ld) infi;
   for(int nxt = 0; nxt < n; ++nxt) {
      if (pos == nxt || (mask & (1 << nxt))) continue;
      ld go = tsp(nxt, mask | (1 << nxt)) + dist(pos, nxt);

      if (mn_val > go + eps) {
         mn_val = go;
         par[pos][mask] = nxt;
      }
   }

   return memo[pos][mask] = mn_val;
}

void solve_td_tsp(int tc) { // topdown O(n^2 * 2^n)
   cout << "**********************************************************\n";
   cout << "Network #" << tc << "\n";
   for (int i = 0; i < n; ++i) for (int j = 0; j < (1 << n); ++j)
      memo[i][j] = -1;

   ld mn_cycle = (ld) infi, total = 0;
   int pos = -1;

   for (int i = 0; i < n; ++i) {
      ld go = tsp(i, 1 << i);
      if (mn_cycle > go) {
         mn_cycle = go;
         pos = i;
      }
   }
   vector <int> order = {pos};
   int mask = (1 << pos);
   while (mask != (1 << n) - 1) {
      order.push_back(par[pos][mask]);
      pos = par[pos][mask];
      mask |= (1 << pos);
   }

   for (int i = 1; i < n; ++i) {
      int sx, sy, ex, ey;
      sx = point[order[i-1]].x, sy = point[order[i-1]].y;
      ex = point[order[i]].x, ey = point[order[i]].y;
      ld wt = dist(order[i-1], order[i]) + 16;
      cout << "Cable requirement to connect (" << sx << "," << sy << ") to ("
         << ex << "," << ey << ") is " << wt<< " feet.\n";
      total += wt;
   }
   cout << "Number of feet of cable required is " << total << ".\n";
   assert(fabs(total - mn_cycle - (n-1)*16) < eps);
}

/*****************************TOP DOWN SOLUTION ends *************************/



/*****************************BRUTE FORCE SOLUTION starts *************************/
void solve_bruteforce(int tc) { //O(n!)
   cout << "**********************************************************\n";
   cout << "Network #" << tc << "\n";
   vector <int> perm, best;
   for (int i = 0; i < n; ++i) perm.push_back(i);
   best.assign(n, 0);

   ld mn_val = (ld)infi;

   do {
      ld wt = 0;
      for (int i = 1; i < n; ++i) {
         wt += dist(perm[i-1], perm[i]);
      }
      if (mn_val > wt + eps) {
         mn_val = wt;
         for (int i = 0; i < n; ++i) best[i] = perm[i];
      }
   } while (next_permutation(perm.begin(), perm.end()));

   ld total = 0;
   for (int i = 1; i < n; ++i) {
      int sx, sy, ex, ey;
      sx = point[best[i-1]].x, sy = point[best[i-1]].y;
      ex = point[best[i]].x, ey = point[best[i]].y;
      ld wt = dist(best[i-1], best[i]) + 16;
      cout << "Cable requirement to connect (" << sx << "," << sy << ") to ("
         << ex << "," << ey << ") is " << wt<< " feet.\n";
      total += wt;
   }
   cout << "Number of feet of cable required is " << total << ".\n";
}

/*****************************BRUTE FORCE SOLUTION starts *************************/

void read() {
   point.assign(n, pii());
   for (int i = 0; i < n; ++i) {
      cin >> point[i].x >> point[i].y;
   }
}

signed main() {
   IOS; PREC;
   int tc = 1;
   while (cin >> n, n) read(), solve_bu_tsp(tc++);
   // while (cin >> n, n) read(), solve_td_tsp(tc++);
   // while (cin >> n, n) read(), solve_bruteforce(tc++);

   return EXIT_SUCCESS;
}
