#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define ll long long
const ll MAX = (ll)1e12;

vector <pair <int, string>> have, not_have;

inline int get_min_base (string &s) {
   int mn = 1;
   for (int ch : s) {
      if (ch - '0' >= 0 && ch - '0' <= 9)
         mn = max(mn, ch - '0');
      else
         mn = max(mn, ch - 'A' + 10);
   }
   return mn + 1;
}

ll get_val (string &s, int b) {
   ll val = 0;
   ll base_pw = 1;
   for (char ch : s) {
      if (base_pw > MAX) return -2;
      if (ch - '0' >= 0 && ch - '0' <= 9)
         val += base_pw * (ch - '0');
      else
         val += base_pw * (ch - 'A' + 10);
      base_pw *= b;
      if (val > MAX) {
         return -2;
      }
   }
   return val;
}

bool check (string &s, ll val) {
   // binary search on all base [min_base, 36]
   int l = get_min_base(s), h = 36;
   while (l <= h) {
      int mid = (l + h)/2;
      ll gv = get_val (s, mid);
      if (gv == -2) h = mid - 1;
      else if (val == gv) {
         return true;
      }
      else if (val > gv) {
         l = mid + 1;
      }
      else h = mid - 1;
   }
   return false;
}

bool final_check (ll val, int sidx) {
   for (int i = sidx; i < (int)not_have.size(); ++i) {
      if (check(not_have[i].se, val) == false) {
         return false;
      }
   }
   return true;
}

int main() {
   int tc;
   cin >> tc;
   while (tc--) {
      int n;
      cin >> n;
      have.clear(), not_have.clear();

      for (int i = 0; i < n; ++i) {
         int foo; string bar;
         cin >> foo >> bar;
         reverse(bar.begin(), bar.end());
         if (foo == -1) {
            not_have.push_back(make_pair(foo, bar));
         }
         else {
            have.push_back(make_pair(foo, bar));
         }
      }

      bool ok = true;
      ll real_val = -1;
      if (have.size() >= 1) {
         // get first value
         real_val = get_val(have[0].se, have[0].fi);
         if (real_val == -2)
            ok = false;

         // check if all in 'have' have the same value

         for (int i = 1; ok && i < (int)have.size(); ++i) {
            ll gv = get_val(have[i].se, have[i].fi);
            if (gv == -2 || real_val != gv) {
               ok = false;
               break;
            }
         }
         // if got all correct then proceed with possibility in not have
      }

      if (ok) {
         ok = false;
         if (real_val == -1) {
            for (int b = get_min_base(not_have[0].se); b <= 36; ++b) {
               ll cur_val = get_val(not_have[0].se, b);
               if (cur_val == -2) continue;
               if (final_check(cur_val, 1)) {
                  real_val = cur_val;
                  ok = true;
                  break;
               }
            }
         }
         else if (final_check(real_val, 0)) {
            ok = true;
         }
      }
      cout << (ok ? real_val : -1) << '\n';
   }
   return 0;
}
