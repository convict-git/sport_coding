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

const int N = 2 * 26 + 10;

struct Rect {
   int x_min, x_max, y_min, y_max;
   inline bool inside (int xx, int yy) {
      return xx > x_min && xx < x_max && yy > y_min && yy < y_max;
   }
};

struct Edge {
   int u, v;
   Edge(int _u = -1, int _v = -1) : u(_u), v(_v) {};
   inline bool operator == (const Edge &o) const {
      return u == o.u && v == o.v;
   }
};

vector <Rect> rect;
bool vis[N];
int match[N];
vector < vector <int> > Adj;
int n, nl, nr; // first 0, ..., nl - 1 vertices in left nl, ..., nr - 1 in right

inline void re_init() {
   for (int i = 0; i < n; ++i) {
      vis[i] = false, match[i] = -1;
   }
}

void init() {
   n = nl + nr;
   assert(n);
   rect.clear();
   Adj.assign(n, vector <int> ());
   re_init();
}

inline void add_edge(int u, int v) {
   Adj[u].push_back(v);
}

bool augment(int u, const Edge &ban) {
   if (vis[u]) return false;
   vis[u] = true;

   for (int v : Adj[u]) {
      if (Edge(u, v) == ban) continue;
      if (match[v] == -1 || augment(match[v], ban)) {
         match[v] = u;
         return true;
      }
   }
   return false;
}

int MCBM(const Edge &ban = Edge()) {
   assert (nl + nr == n);
   int mcbm = 0;

   for (int u = 0; u < nl; ++u) { // in left set
      fill(vis, vis + n, false);
      mcbm += augment(u, ban);
   }
   return mcbm;
}

void solve(int tc) {
   cout << "Heap " << tc << '\n';
   using pci = pair <char, int>;
   vector <pci> ans;

   for (int u = 0; u < nl; ++u) {
      for (int v : Adj[u]) {
         re_init();
         int flow_ban_uv = MCBM(Edge(u, v));
         //debug(u, v, flow_ban_uv);
         if (flow_ban_uv != nl) {
            ans.push_back(pci(char('A' + u), v + 1));
         }
      }
   }

   if (ans.size())
      for (int i = 0; i < (int)ans.size(); ++i)
         cout << "(" << ans[i].x << ',' << ans[i].y << ")" <<
            " \n"[ i == (int)ans.size() - 1];
   else cout << "none\n";
   cout << '\n';
}

void read() {
   nr = nl;
   init();

   int x_min, x_max, y_min, y_max;
   for (int i = 0; i < nl; ++i) {
      cin >> x_min >> x_max >> y_min >> y_max;
      rect.push_back({x_min, x_max, y_min, y_max});
   }

   int xx, yy;
   for (int i = 0; i < nr; ++i) {
      cin >> xx >> yy;
      for (int j = 0; j < nl; ++j) {
         if (rect[j].inside(xx, yy))
            add_edge(j, i);
      }
   }
}

signed main() {
   IOS; PREC;
   int tc = 1;
   while (cin >> nl, nl) {
      read();
      solve(tc++);
   }

   return EXIT_SUCCESS;
}


