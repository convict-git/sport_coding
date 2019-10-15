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

struct ch {
   int freq, start_idx;
} table[52];

int query_freq[52];
int k;

inline int get_idx(char c) {
   if (c - 'a' >= 0 && 'z' - c >= 0) return c - 'a' + 26;
   else if (c - 'A' >= 0 && 'Z' - c >= 0) return c - 'A';
   return -1;
}
inline char get_char(int idx) {
   if (idx >= 0 && idx < 26) return char('A' + idx);
   else if (idx >= 26 && idx < 52) return char('a' + idx);
   return '#';
}

void read() {
   for (int i = 0; i < 52; ++i) table[i] = {0, -1};
   string st;
   cin >> st;
   for (int i = 0; i < (int)st.size(); ++i) {
      int idx = get_idx(st[i]);
      if (!table[idx].freq) table[idx].start_idx = i;
      ++table[idx].freq;
   }

   cin >> k;
   while (k--) {
      for (int i = 0; i < 52; ++i) query_freq[i] = 0;
      cin >> st;
      for (char c : st) ++query_freq[get_idx(c)];

      int start_idx = -1, last_idx = -1;
      bool ok = true;
      for (int i = 0; i < 52; ++i) {
         if (query_freq[i]) {
            if (query_freq[i] > table[i].freq) {
               ok = false;
               cout << "Not matched\n";
               break;
            }
            if (start_idx == -1)
               start_idx = table[i].start_idx;
            last_idx = table[i].start_idx + query_freq[i] - 1;
         }
      }
      if (ok) cout << "Matched " << start_idx << ' ' << last_idx << '\n';
   }
}

signed main() {
   IOS; PREC;
   read();

   return EXIT_SUCCESS;
}

