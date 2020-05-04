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

const int N = 2 * 510;

struct booking{
   int time_min;
   int x_src, y_src, x_dest, y_dest;
   int ride_time_in_min;

   booking (int hr, int mn, int x_s, int y_s, int x_d, int y_d) {
      time_min = 60 * hr + mn, x_src = x_s, y_src = y_s, x_dest = x_d, y_dest = y_d;
      ride_time_in_min = abs(x_s - x_d) + abs(y_s - y_d);
   }

   inline bool is_catched_by (const booking &o) { // o is the ride which came earlier
      int get_to_location = abs(x_src - o.x_dest) + abs(y_src - o.y_dest);
      int time_to_reach = time_min + (time_min < o.time_min ? 24 * 60 : 0);
      int time_reached = o.time_min + get_to_location  + 1 + o.ride_time_in_min;
      return (time_reached <= time_to_reach);
   }
};

vector <booking> schedule;

bool vis[N];
int match[N];
vector < vector <int> > Adj;
int n, nl, nr; // first 0, ..., nl - 1 vertices in left nl, ..., nr - 1 in right

void init() {
   n = nl + nr;
   assert(n);
   Adj.assign(n, vector <int> ());
   for (int i = 0; i < n; ++i)
      vis[i] = false, match[i] = -1;
}

inline void add_edge(int u, int v) {
   Adj[u].push_back(v);
}

bool augment(int u) {
   if (vis[u]) return false;
   vis[u] = true;

   for (int v : Adj[u]) {
      if (match[v] == -1 || augment(match[v])) {
         match[v] = u;
         return true;
      }
   }
   return false;
}

int MCBM() {
   assert (nl + nr == n);
   int mcbm = 0;

   for (int u = 0; u < nl; ++u) { // in left set
      fill(vis, vis + n, false);
      mcbm += augment(u);
   }
   return mcbm;
}
int books;
void solve() {
   int mcbm = MCBM();
   cout << books - mcbm << '\n';
}

void read() {
   schedule.clear();
   cin >> books;
   nr = nl = books;
   init();

   for (int i = 0; i < books; ++i) {
      int hr, mn, x_s, y_s, x_d, y_d;
      char ch;
      cin >> hr >> ch >> mn >> x_s >> y_s >> x_d >> y_d;

      schedule.push_back(booking(hr, mn, x_s, y_s, x_d, y_d));

      for (int j = 0; j < i; ++j) {
         if (schedule[i].is_catched_by(schedule[j]))
            add_edge(j, i);
      }
   }
}

signed main() {
   IOS; PREC;
   int tc;
   cin >> tc;
   while (tc--) {
      read();
      solve();
   }

   return EXIT_SUCCESS;
}

