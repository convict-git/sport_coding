/*
    Problem "886. Suffixes" from acmp.ru

    Let the string be a sequence of small letters of the English alphabet. For
    example, empty sequence "" is a string, the word "aabaf" or an infinite
    sequence of letters "a" are string too.

    The i-th suffix S_i of the string S is the string S from which the first i
    letters are cut: so, for the string S = "aabaf" the suffixes will be:

    S_0 = “aabaf”

    S_1 = “abaf”

    S_2 = “baf”

    S_3 = “af”

    S_4 = “f”

    S_5 = S_6 = S_7 = . . . = “”

    The suffixes are defined for all i > 0.

    The cyclic extension S^* of a finite string S is a string obtained by
    duplicating it to itself an infinite number of times. So,

    S^* = S_0^* = “aabafaabafaa...”

    S_1^* = “abafabafabaf...”

    S_2^* = “bafbafbafbaf...”

    S_3^* = “afafafafafaf...”

    S_4^* = “ffffffffffff...”

    S_5^* = S_6^* = S_7^*= . . . = “”

    For a given string S, find out how many of its suffixes S_i have the same
    cyclic extension as the string S itself, that is, the number of different i
    such that S^* = S_i^*.

    Input:

    The input file INPUT.TXT contains a string S consisting of at least one and
    not more than 100 000 small English letters.

    Output:

    In the output file OUTPUT.TXT output the number of suffixes of the string S
    having the same cyclic extension as itself.


    Solution: polynomial hashes, geometric progression, O(n log(n))
*/

#include <stdio.h>
#include <cassert>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>
#include <string>

typedef unsigned long long ull;

// Generate random base in (before, after) open interval:
int gen_base(const int before, const int after) {
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 mt_rand(seed);
    int base = std::uniform_int_distribution<int>(before+1, after)(mt_rand);
    return base % 2 == 0 ? base-1 : base;
}

struct PolyHash {
    // -------- Static variables --------
    static const int mod = (int)1e9+123; // prime mod of polynomial hashing
    static std::vector<int> pow1;        // powers of base modulo mod
    static std::vector<ull> pow2;        // powers of base modulo 2^64
    static int base;                     // base (point of hashing)

    // --------- Static functons --------
    static inline int diff(int a, int b) {
    	// Diff between `a` and `b` modulo mod (0 <= a < mod, 0 <= b < mod)
        return (a -= b) < 0 ? a + mod : a;
    }

    // -------------- Variables of class -------------
    std::vector<int> pref1; // Hash on prefix modulo mod
    std::vector<ull> pref2; // Hash on prefix modulo 2^64

    // Cunstructor from string:
    PolyHash(const std::string& s)
        : pref1(s.size()+1u, 0)
        , pref2(s.size()+1u, 0)
    {
        assert(base < mod);
        const int n = s.size(); // Firstly calculated needed power of base:
        while ((int)pow1.size() <= n) {
            pow1.push_back(1LL * pow1.back() * base % mod);
            pow2.push_back(pow2.back() * base);
        }
        for (int i = 0; i < n; ++i) { // Fill arrays with polynomial hashes on prefix
            assert(base > s[i]);
            pref1[i+1] = (pref1[i] + 1LL * s[i] * pow1[i]) % mod;
            pref2[i+1] = pref2[i] + s[i] * pow2[i];
        }
    }

    // Polynomial hash of subsequence [pos, pos+len)
    // If mxPow != 0, value automatically multiply on base in needed power. Finally base ^ mxPow
    inline std::pair<int, ull> operator()(const int pos, const int len, const int mxPow = 0) const {
        int hash1 = pref1[pos+len] - pref1[pos];
        ull hash2 = pref2[pos+len] - pref2[pos];
        if (hash1 < 0) hash1 += mod;
        if (mxPow != 0) {
            hash1 = 1LL * hash1 * pow1[mxPow-(pos+len-1)] % mod;
            hash2 *= pow2[mxPow-(pos+len-1)];
        }
        return std::make_pair(hash1, hash2);
    }
};

// Init static variables of PolyHash class:
int PolyHash::base((int)1e9+7);
std::vector<int> PolyHash::pow1{1};
std::vector<ull> PolyHash::pow2{1};

// Functions for calculating this sum: 1 + a + a^2 + ... + a^(k-1) by modulo
// mod and 2^64 in O(log(k))
int sum_int(int a, int k) {
    if (k == 1) {
        return 1;
    } else if (k % 2 == 0) {
        return (1LL + a) * sum_int(1LL * a * a % PolyHash::mod, k / 2) % PolyHash::mod;
    } else {
        return 1 + (a+1LL) * a % PolyHash::mod * sum_int(1LL * a * a % PolyHash::mod, k / 2) % PolyHash::mod;
    }
}

ull sum_ull(ull a, int k) {
    if (k == 1) {
        return 1;
    } else if (k % 2 == 0) {
        return (1 + a) * sum_ull(a * a, k / 2);
    } else {
        return 1 + a * sum_ull(a, k - 1);
    }
}

int main() {
    static char buf[1+100000];
    scanf("%100000s", buf);
    std::string a(buf);

    std::reverse(a.begin(), a.end()); // reverse

    // Gen random point of hashing:
    PolyHash::base = gen_base(256, PolyHash::mod);

    // Construct hashes on prefixes of substring a:
    PolyHash hash(a);

    // Length of string:
    const int n = (int)a.size();

    int answ = 0;
    for (int len = 1; len <= n; ++len) {
        // Get polynomial hash:
        auto hash1 = hash(0, len); // on prefix a[0...len)
        auto hash2 = hash(0, n);   // on prefix a[0...n)

        // Multiply on sum of geometry progression hash modulo mod:
        hash1.first = 1LL * hash1.first * sum_int(PolyHash::pow1[len], n) % PolyHash::mod;
        hash2.first = 1LL * hash2.first * sum_int(PolyHash::pow1[n], len) % PolyHash::mod;

        // Multiply on sum of geometry progression hash modulo 2^64:
        hash1.second *= sum_ull(PolyHash::pow2[len], n);
        hash2.second *= sum_ull(PolyHash::pow2[n], len);

        // Compare hashes:
        answ += (hash1 == hash2);
    }
    printf("%d", answ);

    return 0;
}
