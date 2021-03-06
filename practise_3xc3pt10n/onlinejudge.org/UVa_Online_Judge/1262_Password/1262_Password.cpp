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
vector <string> cols;
int mask[2][5];
int k, cnt;
string ans;
vector <char> stck;
bool ok;

void backtrack(int idx) {
   if (idx == 5) {
      ++cnt;
      if (cnt == k) {
         ans = "";
         for (char c : stck) ans += c;
         ok = true;
      }
      return;
   }

   for (char ch : cols[idx]) {
      if (!ok) {
         stck.push_back(ch);
         backtrack(idx + 1);
         stck.pop_back();
      }
   }
   return;
}

void init() {
   cols.clear();
   stck.clear();
   ok = false;
   cnt = 0;
}

void read() {
   init();
   cin >> k;
   string st;
   for (int conf = 0; conf < 2; ++conf) {
      fill(mask[conf], mask[conf] + 5, 0);
      for (int i = 0; i < 6; ++i) {
         cin >> st;
         for (int j = 0; j < 5; ++j) {
            mask[conf][j] |= (1 << (st[j] - 'A'));
         }
      }
   }
   for (int i = 0; i < 5; ++i) {
      int bit_mask = mask[0][i] & mask[1][i];
      st = "";
      for (int j = 0; j < 26; ++j) {
         if (bit_mask & (1 << j)) {
            st += char('A' + j);
         }
      }
      cols.push_back(st);
   }
   backtrack(0);

   cout << (ok ? ans : "NO") << '\n';
}

signed main() {
   IOS; PREC;
   int tc;
   cin >> tc;
   while (tc--) read();

   return EXIT_SUCCESS;
}

