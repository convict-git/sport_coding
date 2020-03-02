#include      <bits/stdc++.h> /*{{{*/
#include      <ext/pb_ds/assoc_container.hpp>
#include      <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#ifndef CONVICTION
#pragma GCC       optimize ("Ofast")
#pragma GCC       optimize ("unroll-loops")
#pragma GCC       target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#endif

#define IOS       ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC      cout.precision (10); cout << fixed
#define X         first
#define Y         second
#define sz(x)     (int)x.size()
#define fr(i,x,y) for (int i = (int)x; i <= (int)y; ++i)
#define rv(i,x,y) for (int i = (int)x; i >= (int)y; --i)
#define cnt(x)    __builtin_popcount(x)
#define cntll(x)  __builtin_popcountll(x)
#define bg(x)     " [ " << #x << " : " << (x) << " ] "
#define un(x)     sort(x.begin(), x.end()), \
  x.erase(unique(x.begin(), x.end()), x.end())
using   ll  =     long long;
using   ull =     unsigned long long;
using   ff  =     long double;
using   pii =     pair<int,int>;
using   pil =     pair<int,ll>;
using   pll =     pair<ll,ll>;
using   vi  =     vector <int>;
using   vl  =     vector<ll>;
using   vvi =     vector <vi>;
using   vvl =     vector <vl>;
using   vp  =     vector <pii>;
using   vvp =     vector <vp>;
typedef tree
< int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
ordered_set;

struct chash {
  int operator () (pii x) const { return x.X*31 + x.Y; }
};
gp_hash_table <pii, int, chash> gmp;

#if __cplusplus > 201103L
seed_seq seq{
  (uint64_t) chrono::duration_cast<chrono::nanoseconds>
    (chrono::high_resolution_clock::now().time_since_epoch()).count(),
    (uint64_t) __builtin_ia32_rdtsc(),
    (uint64_t) (uintptr_t) make_unique<char>().get()
};
mt19937 rng(seq); //uniform_int_distribution<int> (l, h)(rng); //[low, high]
#else
auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 rng(seed);
#endif

#define debug(args...) { \
  /* WARNING : do NOT compile this debug func calls with following flags: // \
   * // -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2*/ \
  string _s = #args; replace(_s.begin(), _s.end(), ',', ' ');\
  stringstream _ss(_s); \
  istream_iterator<string> _it(_ss); err(_it, args); \
}
void err(istream_iterator<string> it) {
  it->empty(); cerr << " (Line : " << __LINE__ << ")" << '\n';
}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
  cerr << fixed << setprecision(15)
    << " [ " <<  *it << " : " << a  << " ] "<< ' ';
  err(++it, args...);
}
//         __                                           __
//        (**)                                         (**)
//        IIII                                         IIII
//        ####                                         ####
//        HHHH     Madness comes, and madness goes     HHHH
//        HHHH    An insane place, with insane moves   HHHH
//        ####   Battles without, for battles within   ####
//     ___IIII___        Where evil lives,          ___IIII___
//  .-`_._"**"_._`-.      and evil rules         .-`_._"**"_._`-.
// |/``  .`\/`.  ``\|    Breaking them up,      |/``  .`\/`.  ``\|
// `     }    {     '  just breaking them in    `     }    {     '
//       ) () (  Quickest way out, quickest way wins  ) () (
//       ( :: )      Never disclose, never betray     ( :: )
//       | :: |   Cease to speak or cease to breath   | :: |
//       | )( |        And when you kill a man,       | )( |
//       | || |          you're a murderer            | || |
//       | || |             Kill many                 | || |
//       | || |        and you're a conqueror         | || |
//       | || |        Kill them all ... Ooh..        | || |
//       | || |           Oh you're a God!            | || |
//       ( () )                       -Megadeth       ( () )
//        \  /                                         \  /
//         \/                                           \/
/*}}}*/
/*****************************************************************************/
//Don’t practice until you get it right. Practice until you can’t get it wrong

int books, lib, days;
vector <pair <int, int>> values; // for each book, (score, frequency)
vector <int> book_taken, orderlib;
vector <vector <int>> store; // for each lib,
vector <pair <int, int>> def; // for each lib (time signup, capacity)
set <int> hub;

void input () {
  cin >> books >> lib >> days;
  values.assign(books, pair <int, int> (0, 0));
  store.assign(lib, vector <int> ());
  def.assign(lib, pair <int, int>());
  book_taken.assign(books, false);

  for (int b = 0; b < books; ++b)
    cin >> values[b].first;

  for (int l = 0; l < lib; ++l) {
    int n, t, m;
    cin >> n >> t >> m;
    def[l] = make_pair(t, m);
    store[l].assign(n, 0);
    for (int b = 0; b < n; ++b) {
      cin >> store[l][b];
      ++values[store[l][b]].second;
    }
  }
  hub.clear();
}

vector <int> get_lib_order_rand() {
  vector <int> order(lib);
  for (int i = 0; i < lib; ++i) { order[i] = i; }
  random_shuffle(order.begin(), order.end());
  return order;
}

vector <int> get_lib_some_order () {
  vector <int> order;
  vector <int> taken_lib(lib, false);
  vector <vector <int>> pref_score(lib, vector <int> ());

  /*
  vector <long double> bscore(books);
  for (int b = 0; b < books; ++b) {
    bscore[b] = (1.0 * values[b].first)/values[b].second;
  }
  */
  //
  for (int l = 0; l < lib; ++l) {
    pref_score[l].assign((int)store[l].size(), 0);
    for (int b_idx = 0; b_idx < (int)store[l].size(); ++b_idx) {
      int b = store[l][b_idx];
      if (b_idx) pref_score[l][b_idx] = pref_score[l][b_idx - 1] + values[b].first;
      else pref_score[l][b_idx] = values[b].first;
    }
  }

  // exit(0);
  for (int d = 0; d < days;) {
    int rem = days - d;
    int to_take_lib = -1; // index of the lib to be chosen for signup
    int mx_score_lib = 0;
    int cnt_inside_lib = -1;
    for (int l = 0; l < lib; ++l) {
      if (taken_lib[l] == false) {
        int cur_left =  rem - def[l].first;
        if (cur_left > 0) {
          int total_serve = cur_left * def[l].second;
          total_serve = min(total_serve, static_cast <int> (store[l].size()));
          int get_cum_den = pref_score[l][total_serve - 1]; /// check the index again
          if (mx_score_lib < get_cum_den) {
            mx_score_lib = get_cum_den;
            to_take_lib = l;
            cnt_inside_lib = total_serve;
          }
        }
      }
    }
    if (to_take_lib == -1) break;
    taken_lib[to_take_lib] = true;
    d += def[to_take_lib].first;
    order.push_back(to_take_lib);
  }
  set <int> tk;

  for (int i = 0; i < lib; ++i) tk.insert(i);
  for (auto &el : order) tk.erase(el);
  for (int el : tk) order.push_back(el);
  return order;
}

vector <int> get_lib_order_sim () {
  vector <int> order;
  vector <int> cap(lib);
  vector <int> book_taken(books, false);
  vector <int> lib_take(lib, false);
  set <int> s(greater <int> ());

  bool is_signedup = false;
  for (int d = 0; d < days; ++d) {
    for (int l = 0; l < lib; ++l) {
      cap[l] = def[l].second;
    }

    if (is_signedup == false) {

    }
  }
}

void approach_hub() {
  /*
  vector <int> cap(lib);

  for (int d = 0; d < days; ++d) {
    for (int l = 0; l < lib; ++l) {
      cap[l] = def[l].second;
    }
  }
  */
}

signed main() {
  IOS; PREC;
  input();
  for (int l = 0; l < lib; ++l) {
    sort(store[l].begin(), store[l].end(), [&] (int x, int y) { return values[x].first > values[y].first; });
  }

  // vector <int> order = get_lib_order_rand();
  vector <int> order = get_lib_some_order();

  cout << lib << '\n';
  for (int &el : order) {
    cout << el<< ' ' << (int)store[el].size() << '\n';
    for (int i = 0; i < (int)store[el].size(); ++i) {
      cout << store[el][i] << ' ';
    }
    cout << '\n';
  }

  return EXIT_SUCCESS;
}


