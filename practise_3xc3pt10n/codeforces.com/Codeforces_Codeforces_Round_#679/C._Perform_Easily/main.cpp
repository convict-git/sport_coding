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

void preproc()
{
}

void solve()
{
   // take input
   vector <int> A(6);
   for (int &a : A) cin >> a;
   int N;
   cin >> N;
   vector <int> B(N);
   for (int i = 0; i < N; ++i) {
      cin >> B[i];
   }

   /* We will keep an array of pairs, (Bj - Ai, j)
    * The obvious question is why? (Bj - Ai) denotes the distance from the start of the string,
    * or simply the fret number which you will use to play the jth note with ith string.
    *
    * We want to minimize the distance between the farthest frets used while being able to play all the
    * notes from 1...N
    *
    * Now, why do we keep the second cordinate as j? This is to keep a track of the notes that you have already
    * played.
    */

   // Push all pairs (Bj - Ai, j) into range
   vector <pair <int, int>> range;
   for (int i = 0; i < 6; ++i) {
      for (int j = 0; j < N; ++j) {
         range.push_back(make_pair(B[j] - A[i], j));
      }
   }
   sort(range.begin(), range.end()); // Sort the range
   int sz = (int)range.size();

   int notesPlayed = 0; // notesPlayed tells us about the uniques notes that we have played in a range
   vector <int> noteCount(N); //  noteCount[j]: this tells us how many options do we have to play the jth note
   int res = INT_MAX;

   for (int left = 0, right = 0; left < sz and right < sz; ) {
      int leftNote = range[left].second, rightNote = range[right].second;

      /* shift right till you can play all notes, i.e. find a 'right' for the current 'left'
       * such that it is least and yet covers all the notes */
      while (notesPlayed != N and right < sz) {
         rightNote = range[right].second;
         ++noteCount[rightNote]; // update the count of this right note
         if (noteCount[rightNote] == 1) { // saw a new note
            ++notesPlayed;
         }
         ++right;
      }

      /* If you were able to play all the notes, consider it for an answer */
      if (notesPlayed == N) {
         res = min(res, range[right - 1].first - range[left].first);
      }

      /* Now we will have to increment the left pointer, and maintain the datastructures used accordingly */
      --noteCount[leftNote]; // Now you loose one note, i.e. range[left].second
      if (noteCount[leftNote] == 0) { // if you no more play this note in the range
        --notesPlayed; // update the number of notes played
      }
      ++left;
   }

   cout << res << '\n';
   return;
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

