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

const int M = 35;
struct Edge {
  int u, v, id;
  vector <Edge*> adj;
  inline bool operator == (const Edge &o) const {
    return u == o.u && v == o.v && id == o.id;
  }
};
Edge edges[M];

int vis[M];
Edge start, last;

int n, m, idx = 0;
vector <Edge> stck;

bool dfs (Edge cur, int level) {
  // cerr << "STACK NOW : -> "; for (Edge e : stck) { cerr << "[ " << e.u << ',' << e.v << " ]->"; } cerr << '\n';
  if (level == n + 1) {
    if (cur == last) {
      return true;
    }
    else return false;
  }

  bool ok = false;
  for (Edge *e : cur.adj) {
    if (!vis[e->id]) {
      vis[e->id] = true;
      // stck.push_back(*e);
      ok = dfs (*e, level + 1);
      // stck.pop_back();
      vis[e->id] = false;
    }
    if (ok) return true;
  }
  return false;
}

void init() {
  idx = 0;
  for (int i = 0; i < m + 2; ++i) vis[i] = false;
}

void read() {
  cin >> m;
  init();
  cin >> edges[2 * m].u >> edges[2 * m].v;
  edges[2 * m].id = idx++;
  edges[2 * m].adj.clear();

  cin >> edges[2 * m + 1].u >> edges[2 * m + 1].v;
  edges[2 * m + 1].id = idx++;
  edges[2 * m + 1].adj.clear();

  for (int i = 0; i < m; ++i) {
    cin >> edges[2 *i].u >> edges[2 * i].v;
    edges[2 * i + 1].v = edges[2 * i].u, edges[2 * i + 1].u = edges[2 * i].v;
    edges[2 * i].id = edges[2 * i + 1].id = idx;
    edges[2 * i].adj.clear(), edges[2 * i + 1].adj.clear();
    idx++;
  }

  for (int i = 0; i <= 2 * m + 1; ++i) {
    for (int j = 0; j <= 2 * m + 1; ++j) {
      if (i == j || edges[i].id == edges[j].id) continue;
      if (edges[i].v == edges[j].u) {
        edges[i].adj.push_back(&edges[j]);
      }
    }
  }

  start = edges[2 * m], last = edges[2 * m + 1];
  vis[start.id] = true;
  // stck.push_back(start);
  bool ok = dfs (start, 0);
  // stck.pop_back();
  cout << (ok ? "YES\n" : "NO\n");
}

signed main() {
  IOS; PREC;

  while (cin >> n, n) {
    read();
  }
  return EXIT_SUCCESS;
}

