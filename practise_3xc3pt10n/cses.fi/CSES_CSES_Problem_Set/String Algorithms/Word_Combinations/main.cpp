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

typedef long long Int;

using ull = unsigned long long;
using Hash = pair <int, ull>;

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

class polyhash {
  public:
    static const int Mod = (int)1e9 + 123;
    static vector <int> pow_int;
    static vector <ull> pow_ull;
    static int p; // take p such that a[i] < p < Mod, gcd(p, Mod) = 1

    static int gen_base (const int l, const int r) {
      int base = uniform_int_distribution<int>(l + 1, r - 1) (rng);
      return base % 2 == 0 ? base - 1 : base;
    }
    static void calc_pow(int mx_len) {
      while ((int)pow_int.size() <= mx_len + 1) { // calc powers
        pow_int.push_back(int(1ll * pow_int.back() * p % Mod));
        pow_ull.push_back(pow_ull.back() * p);
      }
    }
    const int sz;

    vector <int> s;
    vector <int> pref_int;
    vector <ull> pref_ull;

    void encode(const string &st) {
      s.assign(sz, 0);
      for (int i = 0; i < sz; ++i) s[i] = st[i];
    }

    polyhash (const string &st) : sz((int)st.size()) {
      encode(st);
      pref_int.assign(sz + 1u, 0);
      pref_ull.assign(sz + 1u, 0);
      assert(p < Mod);

      calc_pow(sz + 1);

      for (int i = 0; i < sz; ++i) {
        assert(p > s[i]);
        pref_int[i] = int(1ll*s[i]*pow_int[i] % Mod);
        pref_int[i] = (pref_int[i] + (i > 0 ? pref_int[i - 1] : 0)) % Mod;
        pref_ull[i] = s[i]*pow_ull[i] + (i > 0 ? pref_ull[i - 1] : 0);
      }
    }

    inline Hash operator()
      (const int pos, const int len, const int mx_len = -1) const {
        assert(pos + len <= sz);
        int hash_int = pref_int[pos + len - 1];
        ull hash_ull = pref_ull[pos + len - 1];
        if (pos != 0) {
          hash_int = (hash_int - pref_int[pos - 1] + Mod) % Mod;
          hash_ull = hash_ull - pref_ull[pos - 1];
        }
        if (mx_len != -1) { // for direct comparison between prefixes
          //else multiply with opposite powers
          assert (mx_len < (int)pow_int.size());
          hash_int = int(1ll*hash_int*pow_int[mx_len - (pos+len-1)] % Mod);
          hash_ull *= pow_ull[mx_len - (pos+len-1)];
        }
        return make_pair(hash_int, hash_ull);
      }
    //indexing from 0, len >= 1

    bool compare (int i, int len1, int j, int len2, int mx_len) {
      assert(i + len1 <= sz && j + len2 <= sz);
      int len = min(len1, len2);
      int l = 1, h = len;
      while (l <= h) {
        int glen = (l + h)/2;
        if ((*this)(i, glen, mx_len) == (*this)(j, glen, mx_len))
          l = glen + 1;
        else h = glen - 1;
      }
      //l is length of first point of difference
      return ((l > len && len1 < len2) || (s[i + l - 1] < s[j + l - 1]));
    }

    Hash inf_ext (int i, int len, int o_len, int mx_len) {
      function <ull(ull, int)> gp_ull;
      function <int(int, int)> gp_int;
      gp_ull = [&](ull a, int k) -> ull {
        ull a_sq = a * a;
        if (k == 1) return 1;
        else if (k & 1) return 1 + a * gp_ull(a, k - 1);
        else return (1 + a) * gp_ull (a_sq, k/2);
      };
      gp_int = [&] (int a, int k)->int {
        int a_sq = int(1ll * a * a % Mod);
        if (k == 1) return 1;
        else if(k & 1) return int((1 + (1ll * a * gp_int(a, k - 1)%Mod)));
        else return int(1ll * (1 + a) * gp_int (a_sq, k/2) % Mod);
      };

      Hash h = (*this)(i, len, mx_len);
      int hx = int(1ll * h.first * pow_int[len] % Mod);
      ull hy = h.second * pow_ull[len] * gp_ull(p, o_len);
      hx = int(1ll * hx * gp_int(p, o_len) % Mod);
      return make_pair(hx, hy);
    }

#define T(x) (1 << (x))
    int lcp (int i, int j, int mx_len) {
      int ii = i, jj = j;
      for (int k = 20; k >= 0; --k) {
        if (ii + T(k) - 1 < sz && jj + T(k) - 1 < sz) {
          if ((*this)(ii, T(k), mx_len) == (*this)(jj, T(k), mx_len))
            ii += T(k), jj += T(k);
        }
      }
      --ii, --jj;
      return (ii - i + 1);
    }
};

int polyhash::p = polyhash::gen_base(256, polyhash::Mod);
vector <int> polyhash::pow_int{1};
vector <ull> polyhash::pow_ull{1};
// int polyhash::p = 31; // 31 for [a ... z], 53 for [a..z, A..Z]
//
void preproc()
{
}
struct pair_hash
{
	template <class T1, class T2>
	std::size_t operator () (std::pair<T1, T2> const &pair) const
	{
		std::size_t h1 = std::hash<T1>()(pair.first);
		std::size_t h2 = std::hash<T2>()(pair.second);

		return h1 ^ h2;
	}
};
void solve()
{
  string s;
  cin >> s;
  int N = (int)s.size();
  int K;
  cin >> K;
  const int Maxn = 1e5 + 10;
  polyhash::calc_pow(Maxn);
  unordered_set <Hash, pair_hash> hashes;
  for (int e = 0; e < K; ++e) {
    string tmp;
    cin >> tmp;
    polyhash p(tmp);
    hashes.insert(p(0, tmp.size(), Maxn));
  }
  vector <vector <int>> occ(N, vector <int> (N));

  polyhash pMain(s);
  for (int i = 0; i < N; ++i) {
    for (int j = i; j < N; ++j) {
       Hash h = pMain(i, j - i + 1, Maxn);
       if (hashes.find(h) != hashes.end()) { occ[i][j] = true; }
    }
  }
  vector <int> dp(N + 1);
  vector <bool> vis(N + 1);
  dp[0] = 1;
  vis[0] = true;

  const int Mod = 1e9 + 7;
  // dp[i] += dp[j] and [i+1, j] is present as a in dict
  for (int i = 0; i <= N; ++i) {
    for (int j = i + 1; j <= N; ++j) {
      if (vis[i] and occ[i][j - 1] == true) {
        vis[j] = true;
        dp[j] += dp[i];
        dp[j] %= Mod;
      }
    }
  }
  debug(dp);
  cout << dp[N] << endl;
}

signed main()
{
  IOS; PREC;
  preproc();

  int tc = 1;
  // cin >> tc;
  for (int Tt = 1; Tt <= tc; ++Tt) {
    // cout << "Case #" << Tt << ": ";
    solve();
  }
  return EXIT_SUCCESS;
}

