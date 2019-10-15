#include         <bits/stdc++.h>
using namespace std;
// #pragma GCC      optimize ("Ofast")
// #pragma GCC      optimize ("unroll-loops")
// #pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

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

unordered_map <string, int> mp;
const int N = (int)4e6 + 10; // 10! = 3628800 max
const int infi = (int)1e9;
int idx = 0;

int get_idx (const string &s) {
   if (mp.find(s) == mp.end())
      mp[s] = idx++;
   return mp[s];
}

template <typename T> int perm_idx(const T &s) {
   int index = 0;
   int position = 2;
   int factor = 1;
   for (int p = (int) s.size() - 2; p >= 0; p--) {
      int successors = 0;
      for (int q = p + 1; q < (int) s.size() ; q++) {
         if (s[p] > s[q]) {
            successors++;
         }
      }
      index += (successors * factor);
      factor *= position;
      position++;
   }
   return index;
}

int bfs (const string &s, const string &t) {
   queue <string> q;
   vector <bool> vis(N, false);
   vector <int> dist(N, infi);

   q.push(s);
   int s_idx = get_idx(s);
   int t_idx = get_idx(t);
   vis[s_idx] = true;
   dist[s_idx] = 0;

   while (!q.empty()) {
      string cur_state = q.front();
      q.pop();

      int cur_idx = get_idx(cur_state);
      if (cur_state == t) break;

      for (int i = 0; i < 10; ++i) {
         for (int len = 2; len <= 10 - i; ++len) {
            string nxt_state(cur_state);
            reverse(nxt_state.begin() + i, nxt_state.begin() + i + len);
            int nxt_idx = get_idx(nxt_state);

            if (!vis[nxt_idx] && dist[nxt_idx] > dist[cur_idx] + 1) {
               q.push(nxt_state);
               vis[nxt_idx] = true;
               dist[nxt_idx] = dist[cur_idx] + 1;
            }
            // debug(s, cur_state, nxt_state, t, idx, dist[cur_idx], dist[nxt_idx]);
         }
      }
   }
   return dist[t_idx];
}

signed main() {
   IOS; PREC;
   string source, target;
   while (true) {
      cin >> source >> target;
      if (source.size() == 1 && target.size() == 1) {
         break;
      }
      cout << bfs(source, target) << '\n';
      cout.flush();
   }
   return EXIT_SUCCESS;
}

