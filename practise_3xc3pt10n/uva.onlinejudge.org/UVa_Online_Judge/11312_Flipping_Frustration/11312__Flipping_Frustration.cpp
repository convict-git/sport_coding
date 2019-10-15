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

template <class T = int> T giveRand (const T& low, const T& high) {
   auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
   mt19937 mt_rand(seed);
   return uniform_int_distribution<T> (low, high)(mt_rand); //closed interval [low, high]
}

const int N = (int)1e7;
const int infi = (int)1e9;

int n, l, r, t;

// vector <int> dist;
// vector <bool> vis;
// queue <int> q;
//
// void dissolve(int v, int u) {
//    if (v >= 1 && v <= n && !vis[v]) {
//       vis[v] = true;
//       dist[v] = dist[u] + 1;
//       q.push(v);
//    }
// }
//
// int bfs (const int &s) {
//    while (!q.empty()) q.pop();
//    int cnt = 0;
//
//    dist.assign(n + 1, infi);
//    vis.assign(n + 1, false);
//
//    dist[s] = 0, q.push(s), vis[s] = true;
//    while (!q.empty()) {
//       int u = q.front(); q.pop();
//       if (u == t) break;
//       dissolve(u - l, u);
//       dissolve(u + r, u);
//    }
//    return dist[t];
// }
//

//solution using linear algebra
//

signed main() {
   IOS; PREC;
   int tc;
   cin >> tc;
   while (tc--) {
      cin >> n >> l >> r >> t;
   }

   return EXIT_SUCCESS;
}

