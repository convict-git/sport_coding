#include      <bits/stdc++.h>
using namespace std;
#define IOS       ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC      cout.precision (0); cout << fixed
#ifdef CONVICTION
#include "/home/convict/Dropbox/myfiles/sport_coding/cplib/snippets/debug.h"
#else
#define debug(x...)
#endif
//Don’t practice until you get it right. Practice until you can’t get it wrong

int n, m;
struct Node {
  bool end = false;
  vector <int> link{-1, -1};
};
vector <Node> trie;

void preproc() {
}

void solve() {
  int bytes = m;

  trie.clear();
  trie.push_back(Node());

  while (n--) {
    string s;
    cin >> s;
    s.pop_back();
    int cur_node = 0;
    for (char c : s) {
      if (trie[cur_node].link[c - '0'] == -1) {
        trie[cur_node].link[c - '0'] = (int)trie.size();
        trie.push_back(Node());
      }
      cur_node = trie[cur_node].link[c - '0'];
    }
    trie[cur_node].end = true;
  }

  vector <long double> f((int)trie.size());
  trie[0].end = true;

  function <long double(int, int)> dfs = [&] (int u, int depth) -> long double {
    long double ret = 0;
    for (int v : trie[u].link) {
      if (v != -1) {
        ret += dfs(v, depth + 1);
      }
    }
    if (trie[u].end) {
      long double p = powl(2, bytes - depth);
      f[u] = p - ret;
      return p;
    }
    else return ret;
  };

  dfs (0, 0);

  int k;
  cin >> k;
  while (k--) {
    string s;
    cin >> s;
    s.pop_back();
    int cur_node = 0;
    for (char c : s) {
      cur_node = trie[cur_node].link[c - '0'];
    }
    assert(trie[cur_node].end == true);
    cout << f[cur_node] << '\n';
  }
  cout << '\n';
}

signed main() {
  IOS; PREC;
  preproc();

  int tc = 1;
  // cin >> tc;
  for (int Tt = 1; Tt <= tc; ++Tt) {
    // cout << "Case #" << Tt << ": ";
    while (cin >> n >> m, n || m) {
      solve();
      cerr << '\n';
    }
  }
  return EXIT_SUCCESS;
}
