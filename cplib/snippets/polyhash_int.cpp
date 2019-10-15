#include <bits/stdc++.h>
using namespace std;
struct polyhash {
   static const int Mod = (int)1e9 + 123;
   static vector <int> pow_int;
   static int p; // take p such that a[i] < p < Mod, gcd(p, Mod) = 1
   static int gen_base (const int l, const int r) {
      int base = uniform_int_distribution<int>(l + 1, r) (rng);
      return base % 2 == 0 ? base - 1 : base;
   }
   static void calc_pow(int mx_len) {
      while ((int)pow_int.size() <= mx_len + 1) { // calc powers
         pow_int.push_back(int(1ll * pow_int.back() * p % Mod));
      }
   }
   const int sz;

   vector <int> s;
   vector <int> pref_int;

   void encode(const string &st) {
      s.assign(sz, 0);
      for (int i = 0; i < sz; ++i) s[i] = st[i];
   }

   polyhash (const string &st) : sz((int)st.size())
   {
      encode(st);
      pref_int.assign(sz + 1u, 0);
      assert(p < Mod);

      calc_pow(sz + 1);

      for (int i = 0; i < sz; ++i) {
         assert(p > s[i]);
         pref_int[i] = int(1ll*s[i]*pow_int[i] % Mod);
         pref_int[i] = (pref_int[i] + (i > 0 ? pref_int[i - 1] : 0)) % Mod;
      }
   }

   inline int operator()
      (const int pos, const int len, const int mx_len = -1) const
      {
         assert(pos + len <= sz);
         int hash_int = pref_int[pos + len - 1];
         if (pos != 0) {
            hash_int = (hash_int - pref_int[pos - 1] + Mod) % Mod;
         }
         if (mx_len != -1) { // for direct comparison between prefixes
            //else multiply with opposite powers
            assert (mx_len < (int)pow_int.size());
            hash_int = int(1ll*hash_int*pow_int[mx_len - (pos+len-1)] % Mod);
         }
         return hash_int;
      }
   //indexing from 0, len >= 1
};

int polyhash::p = polyhash::gen_base((int)256, polyhash::Mod);
vector <int> polyhash::pow_int{1};
// int polyhash::p = 31; // 31 for [a ... z], 53 for [a..z, A..Z]
