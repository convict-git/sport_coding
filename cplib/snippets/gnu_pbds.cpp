#include      <ext/pb_ds/assoc_container.hpp>
#include      <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

typedef tree
< int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
ordered_set;

struct chash {
  int operator () (pair <int, int> x) const { return x.first*31 + x.second; }
};
gp_hash_table <pair <int, int>, int, chash> gmp;

