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

vector <string> dict, stck, rule;
vector <int> num = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
vector <vector <string>> passwords;
int d_len, r_len;

void backtrack(int idx, int r_idx) {
   // cerr << "STACK: "; for (string s : stck) { cerr << s; } cerr << '\n';
   if (idx == (int)rule[r_idx].size()) {
      passwords.push_back(stck);
      return;
   }

   if (rule[r_idx][idx] == '#') {
      for (string s : dict) {
         stck.push_back(s);
         backtrack(idx + 1, r_idx);
         stck.pop_back();
      }
   }
   else if (rule[r_idx][idx] == '0') {
      for (int i = 0; i <= 9; ++i) {
         stck.push_back(to_string(i));
         backtrack(idx + 1, r_idx);
         stck.pop_back();
      }
   }
   else assert(rule[r_idx][idx] != '#' && rule[r_idx][idx] != '0');
}

void solve_backtrack() {
   cout << "--\n";
   for (int r_idx = 0; r_idx < r_len; ++r_idx) {
      passwords.clear();
      stck.clear();
      backtrack(0, r_idx);
      for (auto pass : passwords) {
         for (auto s : pass) {cout << s;} cout << '\n';
      }
   }
}

void solve_iter() {
   cout << "--\n";
   for (int r_idx = 0; r_idx < r_len; ++r_idx) {
      queue <string> q;
      q.push("");
      int sz = (int)rule[r_idx].size();
      for (int i = 0; i < sz; ++i) {
         int q_sz = (int)q.size();
         while (q_sz--) {
            string popped = q.front();
            q.pop();
            if (rule[r_idx][i] == '#')
               for (string d : dict) q.push(popped + d);
            else if (rule[r_idx][i] == '0')
               for (int j : num) q.push(popped + to_string(j));
         }
      }
      sz = (int)q.size();
      while (sz--) cout << q.front() << '\n', q.pop();
   }
}

void init () {
   dict.clear();
   rule.clear();
   stck.clear();
   passwords.clear();
}

void read() {
   init();
   string st;
   for (int i = 0; i < d_len; ++i) {
      cin >> st; dict.push_back(st);
   }

   cin >> r_len;
   for (int i = 0; i < r_len; ++i) {
      cin >> st; rule.push_back(st);
   }
}

signed main() {
   IOS; PREC;
   while (cin >> d_len) {
      read();
      // solve_backtrack();
      solve_iter(); // iterative is faster, ofcourse
   }

   return EXIT_SUCCESS;
}

