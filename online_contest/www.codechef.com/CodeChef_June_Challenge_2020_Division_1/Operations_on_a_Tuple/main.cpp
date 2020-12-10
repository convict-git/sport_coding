#include      <bits/stdc++.h>
using namespace std;
#define IOS       ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC      cout.precision (10); cout << fixed
#ifdef CONVICTION
#include "/home/convict/Dropbox/myfiles/sport_coding/cplib/snippets/debug.h"
#else
#define debug(x...)
#endif
//Don’t practice until you get it right. Practice until you can’t get it wrong

#pragma GCC       optimize ("Ofast")
#pragma GCC       optimize ("unroll-loops") /* can make things slower */
#pragma GCC       target   ("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
void preproc() {
}

/* NOTE : Shittest CODE I've even wrote. Forgive me if you have to read this code. */

#define dv(x,y) ((x)/(y))
inline bool is_div (long long x, long long y) {
   return y != 0 and abs(x) % abs(y) == 0;
}

int solve(vector <pair <long long, long long>> &in) {
   long long x = in[0].first, y = in[1].first, z = in[2].first;
   long long a = in[0].second, b = in[1].second, c = in[2].second;

   if (x == a and y == b and z == c) { // if all are same - 0 op
      return 0;
   }
   else if (x != a and y == b and z == c) { // if one is different - 1 op
      return 1;
   }
   else if (x != a and y != b and z == c) { // if two are different - 1/2 op
      if (a - x == b - y) {
         return 1;
      }
      else if (is_div(a, x) and is_div(b, y) and a/x == b/y) {
         return 1;
      }
      else {
         return 2;
      }
   }
   else if (x != a and y != b and z != c) { // if three are different
      // # 1 operations //
      if (a - x == b - y and b - y == c - z) {
         return 1;
      }
      else if (is_div(a, x) and is_div(b, y) and is_div(c, z) and a/x == b/y and a/x == c/z) {
         return 1;
      }
      // * we multiply both
      else if (is_div(a, x) and is_div(b, y) and is_div(c, z) and dv(b, y) == dv(c, z)) {
         return 2;
      }
      else if (is_div(a, x) and is_div(b, y) and is_div(c, z) and y * (a/x) * (c/z) == b) {
         return 2;
      }
      else if (is_div(a, x) and is_div(b, y*(a/x)) and is_div(c, z*(a/x)) and b/(y*(a/x)) == c/(z*(a/x))) {
         return 2;
      }
      // * we add both
      else if (b - y == c - z) {
         return 2;
      }
      else if (z + (a-x) + (b-y) == c) {
         return 2;
      }

      // # First we add and then multiply
      // used both in none
      else if (is_div(a, x) and is_div(b, y) and a/x == b/y) {
         return 2;
      }
      else if (is_div(a, x) and c - z == b - y) {
         return 2;
      }
      // used both in one
      else if (is_div(b, y) and is_div(c, z) and b/y == c/z and is_div(a, b/y)) {
         return 2;
      }
      else if (b - y == c - z and is_div(a, x+(b-y))) {
         return 2;
      }
      else if (is_div(b, y) and is_div(a, b/y) and c - z == a/(b/y) - x) {
         return 2;
      }
      // used both in two
      else if (is_div(z, c) and is_div(a, z/c) and is_div(b, z/c) and a/(z/c) - x == b/(z/c) - y) {
         return 2;
      }
      else if (is_div(a, x+(c-z)) and is_div(b, y+(c-z)) and a/(x+(c-z)) == b/(y+(c-z))) {
         return 2;
      }
      //used both in three
      else if (is_div(a-b, x-y) and is_div(a-c, x-z) and is_div(b-c, y-z) and (a-b)/(x-y) == (a-c)/(x-z) and
            (a-b)/(x-y) == (b-c)/(y-z) and is_div(a-x*((a-b)/(x-y)), (a-b)/(x-y))) {
         return 2;
      }

      // # oR we multiply and then add
      // used both in none
      else if (is_div(a, x) and is_div(b, y) and a/x == b/y) {
         return 2;
      }
      else if (is_div(a, x) and b-y == c-z) {
         return 2;
      }
      // used both in one
      else if (b-y == c-z and is_div(a-(b-y), x)) {
         return 2;
      }
      else if (is_div(b, y) and x*(b/y) + (c-z) == a) {
         return 2;
      }
      else if (is_div(b, y) and is_div(c, z) and b/y == c/z) {
         return 2;
      }
      // used both in two
      else if (is_div(a-b, x-y) and is_div(c, z) and dv(a-b, x-y) == dv(c, z)) {
         return 2;
      }
      else if (is_div(a-b, x-y) and a - x*dv(a-b, x-y) == c-z) {
         return 2;
      }
      // used both in three
      else if (is_div(a-b, x-y) and is_div(a-c, x-z) and is_div(b-c, y-z)
            and dv(a-b, x-y) == dv(a-c, x-z) and dv(a-c, x-z) == dv(b-c, y-z)) {
         return 2;
      }
      // # 3 operations (At most)
      else {
         return 3;
      }
   }
   else return 3;
}

int mnMovesBF=3;
int a, b, c;

signed main() {
   IOS; PREC;
   preproc();
   int tc = 1;
   cin >> tc;
   for (long long Tt = 1; Tt <= tc; ++Tt) {
      // cout << "Case #" << Tt << ": ";
      vector <pair <long long ,long long>> inp(3);
      long long mx=0;
      mnMovesBF=3;
      for (int i = 0; i < 6; ++i) {
         if (i < 3) {
            cin >> inp[i].first;
            mx = max(mx, abs(inp[i].first));
         }
         else {
            cin >> inp[i-3].second;
            mx = max(mx, abs(inp[i-3].second));
         }
      }
      a = inp[0].second, b = inp[1].second, c = inp[2].second;
      if (mx <= 10) {
         mnMovesBF = 3;
         int x = inp[0].first, y = inp[1].first, z = inp[2].first;
         if (a == x and y == b and c == z) {
            mnMovesBF = min(mnMovesBF, 0);
         }
         else {
            for (int d1 = -100; d1 <= 100; ++d1) {
               for (int maskd1 = 1; maskd1 < (1 << 3); ++maskd1) {
                  for (int rot1 = 0; rot1 < 2; ++rot1) {
                     int X = inp[0].first, Y = inp[1].first, Z = inp[2].first;
                     X = (maskd1 & (1 << 0) ? (rot1 ? X - d1 : X * d1) : X);
                     Y = (maskd1 & (1 << 1) ? (rot1 ? Y - d1 : Y * d1) : Y);
                     Z = (maskd1 & (1 << 2) ? (rot1 ? Z - d1 : Z * d1) : Z);
                     if (a == X and b == Y and c == Z) {
                        mnMovesBF = min(mnMovesBF, 1);
                     }

                  for (int d2 = -100; d2 <= 100; ++d2) {
                     for (int rot2 = 0; rot2 < 2; ++rot2) {
                        int XX = X, YY = Y, ZZ = Z;
                        if (rot2) {
                           if (XX - d2 == a) XX -= d2;
                           if (YY - d2 == b) YY -= d2;
                           if (ZZ - d2 == c) ZZ -= d2;
                           if (a == XX and b == YY and c == ZZ) {
                              mnMovesBF = min(mnMovesBF, 2);
                           }
                        }
                        else {
                           if (XX * d2 == a) XX *= d2;
                           if (YY * d2 == b) YY *= d2;
                           if (ZZ * d2 == c) ZZ *= d2;
                           if (a == XX and b == YY and c == ZZ) {
                              mnMovesBF = min(mnMovesBF, 2);
                           }
                        }
                     }
                  }
               }
            }
         }

         }
         cout << mnMovesBF << "\n";
      }
      else {
         sort(inp.begin(), inp.end());
         int res = 3;
         do {
            res = min(res, solve(inp));
         } while(next_permutation(inp.begin(), inp.end()));
         cout << res << '\n';
      }
   }
   return EXIT_SUCCESS;
}
