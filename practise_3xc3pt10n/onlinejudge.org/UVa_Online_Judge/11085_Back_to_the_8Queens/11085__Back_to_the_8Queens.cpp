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
using pii = pair <int, int>;
vector < vector <int> > solutions;
int n = 8;
int row[8];
bitset <30> r_mask, l_mask, d_mask;
int ans = 0;

void backtrack(int c) {
   if (c == n) {
      vector <int> sol;
      for (int c = 0; c < n; ++c)
         sol.push_back(row[c]);
      solutions.push_back(sol);
      ++ans;
      return;
   }

   for (int r = 0; r < n; ++r) {
      if (!r_mask[r] && !l_mask[r - c + n - 1] && !d_mask[r + c]) {
         d_mask[r + c] = l_mask[r - c + n - 1] = r_mask[r] = true;
         row[c] = r;
         backtrack(c + 1);
         d_mask[r + c] = l_mask[r - c + n - 1] = r_mask[r] = false;
      }
   }
}
void init() {
   solutions.clear();
   r_mask.reset(), l_mask.reset(), d_mask.reset();
}

signed main() {
   IOS; PREC;
   init();
   backtrack(0);
   assert(solutions.size() == 92);

   int tc = 0;
   string st;
   while (getline(cin, st)) {
      ++tc;
      stringstream ss(st);
      cout << "Case " << tc << ": ";
      for (int c = 0; c < n; ++c) {
         ss >> row[c];
         --row[c];
      }

      int mn_val = INT_MAX;
      for (auto sol : solutions) {
         int diff = 0;
         for (int c = 0; c < n; ++c)
            diff += abs(sol[c] - row[c]) != 0;
         mn_val = min (diff, mn_val);
      }
      cout << mn_val << '\n';
   }

   return EXIT_SUCCESS;
}

