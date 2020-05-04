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

struct Rect {
   int x_min, x_max, y_min, y_max;
   inline bool inside(int xx, int yy) {
      return xx >= x_min && xx <= x_max && yy >= y_min && yy <= y_max;
   }
};

const int N = 26;
vector <Rect> rect;
vector <set <int>> Adj;
int n;
int match[N];

void init() {
   rect.clear();
   Adj.assign(n, set <int> ());
   for (int i = 0; i < n; ++i)
      match[i] = -1;
}

void read() {
   init();
   int x_min, x_max, y_min, y_max;
   for (int i = 0; i < n; ++i) {
      cin >> x_min >> x_max >> y_min >> y_max;
      rect.push_back({x_min, x_max, y_min, y_max});
   }

   int xx, yy;
   for (int i = 0; i < n; ++i) {
      cin >> xx >> yy;
      for (int j = 0; j < n; ++j) {
         if (rect[j].inside(xx, yy))
            Adj[i].insert(j);
      }
   }
}

void solve(int tc) {
   cout << "Heap " << tc << '\n';
   bool ok = true;

   while (ok) {
      ok = false;
      for (int i = 0; i < n; ++i) {
         if (Adj[i].size() == 1) {
            ok = true;
            int must = *Adj[i].begin();
            match[i] = must;
            for (int j = 0; j < n; ++j) {
               set <int>::iterator to_remove = Adj[j].find(must);
               if (to_remove != Adj[j].end()) {
                  Adj[j].erase(to_remove);
               }
            }
         }
      }
   }
   using pci = pair <char, int>;
   vector <pci> ans;
   for (int i = 0; i < n; ++i)
      if (match[i] != -1) ans.push_back(pci(char(match[i] + 'A'), i + 1));
   sort (ans.begin(), ans.end());

   if (ans.size())
      for (int i = 0; i < (int)ans.size(); ++i)
         cout << "(" << ans[i].x << ',' << ans[i].y << ")" << " \n"[i == (int)ans.size() - 1];
   else cout << "none\n";
   cout << '\n';
}

signed main() {
   IOS; PREC;
   int tc = 1;
   while (cin >> n, n) {
      read();
      solve(tc++);
   }

   return EXIT_SUCCESS;
}


