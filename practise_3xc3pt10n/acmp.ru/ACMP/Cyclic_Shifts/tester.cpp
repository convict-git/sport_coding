/*
    Problem "1158. Cyclic shifts" from acmp.ru

	(Time limit: 5 sec. Memory limit: 16 MB Difficulty: 76%)

	A cyclic shift of the string s is the string:

	    s_{k+1}s_{k+2} ... s_{n}s_{1}s_{2} ... s_{k}

	for some k (0 \le k < n), where n is the length of the string s.

	For a given string, it is required to construct all cyclic shifts, arrange
	them lexicographically, write out the last column, and find the position of
	the original row in this list.

	Input:

	In the single line of the input file INPUT.TXT a string consisting of
	characters with ASCII codes from 33 to 127. A string length does not
	exceed 10^5.

	Output:

	In the first line of the output file OUTPUT.TXT, output the position number
	of the given string in the sorted list of cyclic shifts. If there are
	several such positions, then the position with the smallest number should
	be printed. In the second line, output the last column of the sorted cyclic
	shift table.

	Example:

	Firstly, we write out all 6 cyclic shifts of the string "abraka" and order
	the resulting list lexicographically:

	Original list:

	abraka +
	brakaa
	rakaab
	akaabr
	kaabra
	aabrak

	Sorted list:

	aabrak
	abraka +
	akaabr
	brakaa
	kaabra
	rakaab

	Now we see that in the sorted list the original word is in the 2-nd
	position, and the last column is the string "karaab".

    Solution: polynomial hash, binary search, sort, O(n log(n)^2)
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

int main() {
    // Inout:
    char buf[1+1000000];
    scanf("%1000000s", buf);
    std::string a(buf);
    a += a;

    // Length of string:
    const int n = (int)a.size() / 2;

    // Calculate max neede power of base:
    const int mxPow = 2 * n;

    // Init random base of hashing:
    PolyHash::base = gen_base(256, PolyHash::mod);

    // Creare hashing object over string a:
    PolyHash hash(a);

    // Put all starts positions in vector:
    std::vector<int> pos;
    for (int i = 0; i < n; ++i) {
        pos.push_back(i);
    }

    // Sort all items:
    std::stable_sort(pos.begin(), pos.end(), [&](const int p1, const int p2) {
        // Sinary search by the len of equal part:
        int low = 0, high = n+1;
        while (high - low > 1) {
            int mid = (low + high) / 2;
            if (hash(p1, mid, mxPow) == hash(p2, mid, mxPow)) {
                low = mid;
            } else {
                high = mid;
            }
        }
        return low < n && a[p1+low] < a[p2+low];
    });

    // Output answer:
    printf("%d\n", int(std::find(pos.begin(), pos.end(), 0)-pos.begin())+1);
    std::string temp;
    for (auto p : pos) {
        temp.push_back(a[p+n-1]);
    }
    printf("%s\n", temp.c_str());
    return 0;
}
