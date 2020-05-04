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

vector <string> dict;
vector <int> num = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int d_len, r_len;

void read() {
   dict.clear();
   string st, rule;
   for (int i = 0; i < d_len; ++i) {
      cin >> st; dict.push_back(st);
   }

   cin >> r_len;
   for (int r = 0; r < r_len; ++r) {
      cin >> rule;
      cout << "--\n";
      queue <string> q;
      q.push("");
      int sz = (int)rule.size();
      for (int i = 0; i < sz; ++i) {
         int q_sz = (int)q.size();
         while (q_sz--) {
            string popped = q.front();
            q.pop();
            if (rule[i] == '#')
               for (string d : dict) q.push(popped + d);
            else if (rule[i] == '0')
               for (int j : num) q.push(popped + to_string(j));
         }
      }
      sz = (int)q.size();
      while (sz--) cout << q.front() << '\n', q.pop();
   }
}

signed main() {
   IOS; PREC;
   while (cin >> d_len) {
      read();
   }

   return EXIT_SUCCESS;
}

