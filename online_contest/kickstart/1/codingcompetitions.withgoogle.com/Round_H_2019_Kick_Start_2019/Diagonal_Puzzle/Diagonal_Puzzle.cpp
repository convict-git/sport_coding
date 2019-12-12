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
#define x         first
#define y         second
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
using   vi  =     vector <int>;
using   vl  =     vector<ll>;
using   vvi =     vector <vi>;
using   vp  =     vector <pii>;
using   vvp =     vector <vp>;
typedef tree
< int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
ordered_set;

struct chash {
   int operator () (pii x) const { return x.x*31 + x.y; }
};
gp_hash_table <pii, int, chash> mp;

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

const int N = 10;
struct Node {
  int A = 0;
  int cnt = 0, n;

  Node (int n_, int A_)  {
    n = n_, A = A_;
  }

  void flip_diag_one (int r_idx, int c_idx) {
    int r = r_idx, c = c_idx;
    do {
      A ^= (1 << (n * c_idx + r_idx));
      r += 1, c -= 1;
    } while (r >= 0 && c >= 0 && r < n && c < n);
  }
  void flip_diag_two (int r_idx, int c_idx) {
    int r = r_idx, c = c_idx;
    do {
      A ^= (1 << (n * c_idx + r_idx));
      r += 1, c += 1;
    } while (r >= 0 && c >= 0 && r < n && c < n);
  }
  int recompute () {
    cnt = 0;
    fr (i, 0, n-1) fr (j, 0, n-1) cnt += (A & (1 << (n * j + i)));
    return cnt;
  }
};

signed main() {
   IOS; PREC;
   const int N = (int)1e6, infi = (int)1e9;

   int tc;
   cin >> tc;

   int dist[1 << 17];
   int A;
   bool vis[1 << 17];
   vector <string> Mat;

   while(tc--) {
     Mat.clear();
     int n;
     cin >> n;
     A = 0;
     if (n > 8) break;
     fr (i, 0, 1 <<17) dist[i] = infi, vis[i] = 0;
     string foo;
     fr (i, 0, n-1) cin >> foo, Mat.push_back(foo);
     fr (i, 0, n-1) fr(j, 0, n-1) if (Mat[i][j] == '#')
       A |= (1 << (n * j + i));

     dist[A] = 0;
     Node start(n, A);

     queue <Node> q;
     q.push(start);
     int ans = 0;

     while (!q.empty()) {
       Node v = q.front();
       q.pop();

       if (v.recompute() == n * n) {
         ans = dist[v.A];
         break;
       }

       if (vis[v.A]) continue;
       vis[v.A] = true;

       fr (c, 0, n-1) {
         Node nw(n, v.A);
         nw.flip_diag_one(0, c);
         if (!vis[nw.A] && dist[nw.A] > dist[v.A] + 1) {
           dist[nw.A] = dist[v.A] + 1;
           q.push(nw);
         }
       }
       fr (r, 0, n-1) {
         Node nw(n, v.A);
         nw.flip_diag_one(r, n-1);
         if (!vis[nw.A] && dist[nw.A] > dist[v.A] + 1) {
           dist[nw.A] = dist[v.A] + 1;
           q.push(nw);
         }
       }
       fr (c, 0, n-1) {
         Node nw(n, v.A);
         nw.flip_diag_two(0, c);
         if (!vis[nw.A] && dist[nw.A] > dist[v.A] + 1) {
           dist[nw.A] = dist[v.A] + 1;
           q.push(nw);
         }
       }
       fr (r, 0, n-1) {
         Node nw(n, v.A);
         nw.flip_diag_two(r, 0);
         if (!vis[nw.A] && dist[nw.A] > dist[v.A] + 1) {
           dist[nw.A] = dist[v.A] + 1;
           q.push(nw);
         }
       }
     }
     cout << ans << '\n';
   }
   return EXIT_SUCCESS;
}

