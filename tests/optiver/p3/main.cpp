#include      <bits/stdc++.h>
using namespace std;
#define IOS       ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC      cout.precision (10); cout << fixed

class Simulator {
   public:
      int cabinet_count;
      int query_count;
      int sum_of_sizes;
      vector <int> cabinet_sizes;
      list <int> cache_list;
      unordered_map <int, list <int>::iterator> mp_to_iter;
      set <int> is_outside;

      Simulator(int N, const vector <int> &_cabinet_sizes, int K) {
         reset();

         cabinet_count = N;
         copy(_cabinet_sizes.begin(), _cabinet_sizes.end(), back_inserter(cabinet_sizes));
         query_count = K;
         sum_of_sizes = accumulate(cabinet_sizes.begin(), cabinet_sizes.end(), 0);
      }

      void reset() {
         is_outside.clear();
         cabinet_sizes.clear();
         cache_list.clear();
         mp_to_iter.clear();
         sum_of_sizes = 0;
      }

      void manage_full_cache() {
         int cur_sz_cache = static_cast <int> (cache_list.size());
         if (cur_sz_cache == sum_of_sizes) { // you need to remove the last one
            int oldest_item_in_cache = cache_list.back(); // get the oldest item in cache
            cache_list.pop_back(); // remove it
            is_outside.insert(oldest_item_in_cache); // insert it in outside
            mp_to_iter.erase(oldest_item_in_cache); // remove from the map as well
         }
      }

      void insert_new_item(int item_id) {
         cache_list.push_front(item_id); // push in the front
         mp_to_iter[item_id] = cache_list.begin(); // update the map
      }

      void simulate () {
         for (int q = 0; q < query_count - 1; ++q) {
            int item_id;
            cin >> item_id;
            // three cases -> new one, already existing in the cache_list, old one outside
            // if it exists already in cache list, you don't increase the cache size
            if (mp_to_iter.find(item_id) != mp_to_iter.end()) {
               auto iter = mp_to_iter[item_id];
               cache_list.erase(iter); // remove from that older position
            }
            // if it exists already outside, you will increase the cache size
            else if (is_outside.find(item_id) != is_outside.end()) {
               is_outside.erase(item_id); // is no more outside
               manage_full_cache();
            }
            // new item, you will increase the cache size
            else {
               manage_full_cache();
            }
            insert_new_item(item_id);
         }

         int last_item_id;
         cin >> last_item_id;
         // check
      }
};

signed main()
{
  IOS; PREC;

  return EXIT_SUCCESS;
}
