#include      <bits/stdc++.h>
using namespace std;
#define IOS       ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC      cout.precision (10); cout << fixed

namespace Validation {
   const int MAX_CABINET_SIZE = (1 << 10) - 1;
   const int MAX_CABINET_COUNT = (1 << 6) - 1;
   const int MAX_QUERIES = INT_MAX;
   inline void check_error (bool validation) {
      if (validation == false) {
         cout << "INPUT_ERROR" << endl;
         exit(0);
      }
   }
}

typedef long long Index;

class Cabinet {
   private:
      int capacity;                                             /* Capacity of the cabinet */
      list <Index> cache_list;                                  /* list to hold items */
      unordered_map <Index, list <Index>::iterator> mp_to_iter; /* Map from Index to iterator of list */

      /* Inserts a new item in the cache list assuming the size is sufficient */
      void add_new_item_helper (Index item_id) {
         cache_list.push_front(item_id);
         mp_to_iter[item_id] = cache_list.begin();
      }

      /* Deletes an existing item in the cache given its iterator of cache_list */
      void delete_item_helper (list <Index>::iterator iter) {
         Index item_id = *iter;
         cache_list.erase(iter);
         mp_to_iter.erase(item_id);
      }

      /* Returns the oldest item in the cache_list if the cache_list is full
       * else returns -1 */
      Index manage_full_cache_helper () {
         int cur_sz_cache = static_cast <int> (cache_list.size());
         if (cur_sz_cache == capacity) { // the cache is full
            Index oldest_item_in_cache = cache_list.back();
            delete_item_helper(mp_to_iter[oldest_item_in_cache]);
            return oldest_item_in_cache;
         }
         else { return -1; }
      }

   public:
      Cabinet (int sz) : capacity(sz) {
         cache_list.clear();
         mp_to_iter.clear();
      }

      /* return capacity of the cabinet */
      int get_capacity() { return capacity; }

      /* Inserts a item in the cache list, and returns the oldest item it the insertion
       * caused overflow of the cabinet, else returns -1 */
      Index insert (Index item_id) {
         Index replaced_item_id = manage_full_cache_helper(); // find the oldest to be removed, if required
         add_new_item_helper(item_id); // add the new item
         return replaced_item_id;
      }

      /* Removes an item in the cache list if exists */
      void remove (Index item_id) {
         if (mp_to_iter.find(item_id) != mp_to_iter.end()) {
            delete_item_helper(mp_to_iter[item_id]);
         }
      }
};

class Simulator {
   private:
      int queries;                         /* Number of queries */
      int cabinet_count;                   /* Number of cabinets in the simulator */
      vector <Cabinet> vec_cabinet;        /* vector to hold all the instances of Cabinet */
      unordered_map <Index, int> index_mp; /* Map from Index of item to its cabinet's index */

      /* processing a given item with item index */
      void process_item (Index item_id) {
         // if item exists already, find which cabinet it belongs to and delete it from there
         if (index_mp.find(item_id) != index_mp.end()) {
            int cabinet_idx_of_item = index_mp[item_id];
            Cabinet & cab_ref = vec_cabinet[cabinet_idx_of_item];
            cab_ref.remove(item_id);
         }

         // insert the new item, maintaining the invariant
         Index cur_item_id = item_id;
         for (int cabinet_idx = 0; cabinet_idx < cabinet_count; ++cabinet_idx) {
            Cabinet & cur_cabinet_ref = vec_cabinet[cabinet_idx];
            Index replaced_item_id = cur_cabinet_ref.insert(cur_item_id);
            index_mp[cur_item_id] = cabinet_idx;

            if (replaced_item_id == -1) { break; }
            else cur_item_id = replaced_item_id;
         }
      }

   public:
      Simulator (
            int __cabinet_count,
            const vector <int> & vec_cabinet_sizes,
            int __queries)
      {
         cabinet_count = __cabinet_count + 1; // +1 for the infinite capacity cabinet outside
         queries = __queries;
         vec_cabinet.clear();
         index_mp.clear();

         for (int sz : vec_cabinet_sizes) {
            vec_cabinet.push_back(Cabinet(sz)); // create cabinet instances and store it
         }
         vec_cabinet.push_back(Cabinet(INT_MAX)); // last outside cabinet of infinte capacity
      }

      /* simulates the process */
      void simulate() {
         for (int q = 0; q < queries - 1; ++q) {
            Index item_id;
            cin >> item_id;
            // check_error(item_id > 0 and item_id <= INT_MAX);
            Validation::check_error(item_id > 0);
            process_item(item_id);
         }

         // last queury asks for result
         Index last_item_id;
         cin >> last_item_id;
         // check_error(last_item_id > 0 and last_item_id <= INT_MAX);
         Validation::check_error(last_item_id > 0);

         // if the item exists in one of the cabinets or outside
         if (index_mp.find(last_item_id) != index_mp.end()) {
            if (index_mp[last_item_id] == cabinet_count - 1) { cout << "OUTSIDE" << endl; }
            else { cout << index_mp[last_item_id] + 1 << endl; }
         }
         // otherwise its new
         else { cout << "NEW" << endl; }
      }
};

signed main()
{
   IOS; PREC;
   string inp;
   getline(cin, inp);
   stringstream ss(inp);

   // take the input to get all the cabinet sizes
   int size_tmp;
   vector <int> vec_cabinet_sizes;
   while (ss >> size_tmp) {
      Validation::check_error(size_tmp > 0 and size_tmp <= Validation::MAX_CABINET_SIZE);
      vec_cabinet_sizes.push_back(size_tmp);
   }
   int cabinet_count = static_cast <int> (vec_cabinet_sizes.size());
   Validation::check_error(cabinet_count > 0 and cabinet_count <= Validation::MAX_CABINET_COUNT);

   // input to take the number of queries
   int queries;
   cin >> queries;
   Validation::check_error(queries > 0 and queries <= Validation::MAX_QUERIES);

   // Create an instance of the Simulator
   Simulator sim(cabinet_count, vec_cabinet_sizes, queries);
   sim.simulate();

   return EXIT_SUCCESS;
}

