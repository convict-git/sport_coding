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

const int N = 13;
int n, t;
int val[N];
vector < vector <int> > solutions;
vector <int> stck;

void dfs (int u, int sum_now) {
   if (sum_now >= t) {
      if (sum_now == t) {
         vector <int> tmp(stck);
         reverse(tmp.begin(), tmp.end());
         solutions.push_back(tmp);
      }
      return;
   }

   for (int v = u + 1; v < n; ++v) {
      stck.push_back(val[v]);
      dfs(v, sum_now + val[v]);
      stck.pop_back();
   }
}

bool comp1 (vector <int> v1, vector <int> v2) {
   return v1.size() < v2.size();
}

bool comp2 (vector <int> v1, vector <int> v2) {
   int mn = min((int)v1.size(), (int)v2.size());
   for (int i = 0; i < mn; ++i) {
      if (v1[i] == v2[i]) continue;
      else return v1[i] > v2[i];
   }
   return false;
}


void solve() {
   solutions.clear();
   stck.clear();
   cout << "Sums of " << t << ":\n";
   for (int i = 0; i < n; ++i)
      cin >> val[i];
   sort(val, val + n);
   for (int i = 0; i < n; ++i) {
      stck.push_back(val[i]);
      dfs (i, val[i]);
      stck.pop_back();
   }
   if (!solutions.size()) {
      cout << "NONE\n";
      return;
   }
   sort(solutions.begin(), solutions.end(), comp1);
   set <vector <int>> set_shit;
   for (auto el : solutions) set_shit.insert(el);
   solutions.clear();
   for (auto el : set_shit) solutions.push_back(el);

   sort(solutions.begin(), solutions.end(), comp2);
   for (auto sol : solutions) {
      for (int i = 0; i < (int)sol.size(); ++i) {
         if (i) cout << "+";
         cout << sol[i];
      }
      cout << '\n';
   }
}

signed main() {
   IOS; PREC;
   while (cin >> t >> n, t || n) {
      solve();
   }

   return EXIT_SUCCESS;
}

