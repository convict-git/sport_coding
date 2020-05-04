#include         <bits/stdc++.h>
using namespace std;
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define bg(x)    " [ " << #x << " : " << (x) << " ]"
#define x        first
#define y        second
using ll = long long;

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
using pib = pair <ll, bool>;

vector <pib> stones;
int n;
ll d;
ll solve(int idx) {
   vector <int> next_alt = {idx}, alt = {idx};
   int nxt_idx = idx + 1;
   if (nxt_idx >= n + 2) return 0;
   while(!stones[nxt_idx].y) {
      if ((nxt_idx - idx) & 1) next_alt.push_back(nxt_idx);
      else alt.push_back(nxt_idx);
      ++nxt_idx;
   }
   next_alt.push_back(nxt_idx), alt.push_back(nxt_idx);

   ll mx = 0;
   for (int i = 0; i < (int)next_alt.size() - 1; ++i)
      mx = max(mx, stones[next_alt[i+1]].x - stones[next_alt[i]].x);

   for (int i = 0; i < (int)alt.size() - 1; ++i)
      mx = max(mx, stones[alt[i+1]].x - stones[alt[i]].x);

   return max(mx, solve(nxt_idx));
}

void init() {
   stones.clear();
}
void read(int tc) {
   init();
   cin >> n >> d;
   int n_cp = n;
   stones.push_back({0, true});

   while (n_cp--) {
      string st; cin >> st; stringstream ss(st);
      char type, dash; int dist; ss >> type >> dash >> dist;
      stones.push_back({dist, type == 'B'});
   }
   stones.push_back({d, true});
   cout << "Case " << tc << ": " << solve(0) << '\n';
}

signed main() {
   IOS; PREC;
   int tc; cin >> tc;
   for (int i = 1; i <= tc; ++i) {
      read(i);
   }

   return EXIT_SUCCESS;
}

