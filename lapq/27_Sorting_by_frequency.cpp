/*
=====================================================================
QUESTION SUMMARY: "Sorting by frequency"
=====================================================================
You get a list of N integers (some may repeat).
TASK: Print each DISTINCT integer once, sorted by:
  1) FREQUENCY (how many times it appears): most frequent first.
  2) If two integers have the SAME frequency: smaller value first.

INPUT:
 - Line 1: N (1 <= N <= 100,000)
 - Next N lines: one integer each (1 to 1,000,000)

OUTPUT:
 - The distinct integers in the sorted order, one per line.

SAMPLE INPUT:
10
5 4 1 1 4 4 5 6 10 3     (one number per line in the real input)

SAMPLE OUTPUT:
4 1 5 3 6 10             (one number per line in the real output)

WHY? (walking through the sample)
 Counts: 4 appears 3 times
         1 appears 2 times
         5 appears 2 times
         3, 6, 10 each appear 1 time
 Most frequent first: 4 (3 times).
 Then the ones with 2 times: 1 and 5 (tie -> smaller value first: 1, 5).
 Then the ones with 1 time: 3, 6, 10 (tie -> smaller first).
 Result: 4, 1, 5, 3, 6, 10

KEY IDEA:
 1) Count how many times each number appears. Numbers are at most
    1,000,000, so we use a list "count" with a spot for every possible
    number: count[x] = how many times x appeared.
 2) Collect every number that appeared at least once into a list of
    pairs (frequency, value).
 3) Sort that list with our own rule: bigger frequency first; if the
    frequencies are equal, smaller value first.
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
#include <vector>     // lets us use "vector" (a list that can grow)
#include <algorithm>  // lets us use sort
#include <utility>    // lets us use "pair" (two values stuck together)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    // Magic speed-up lines so reading 100,000 numbers is fast.
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;            // a box to hold N, the number of integers
    cin >> n;         // read N from the input

    // count[x] = how many times the number x appeared.
    // Numbers go up to 1,000,000, so we need 1,000,001 spots.
    // Every spot starts at 0 (not seen yet).
    vector<int> count(1000001, 0);

    // Read the N numbers and count each one.
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        count[x]++;       // one more appearance of x
    }

    // Build a list of pairs: (frequency, value), only for numbers
    // that actually appeared (count above 0).
    vector< pair<int, int> > items;
    for (int value = 1; value <= 1000000; value++) {
        if (count[value] > 0) {
            items.push_back(make_pair(count[value], value));
        }
    }

    // Sort with our own rule (the small function inside the [ ]):
    // "x goes before y" if
    //     x has a BIGGER frequency, OR
    //     the frequencies are equal AND x has a SMALLER value.
    sort(items.begin(), items.end(),
         [](const pair<int, int>& x, const pair<int, int>& y) {
             if (x.first != y.first) {
                 return x.first > y.first;   // bigger frequency first
             }
             return x.second < y.second;     // tie: smaller value first
         });

    // Print each value (the "second" part of the pair), one per line.
    // We use '\n' because it is faster than endl.
    for (int i = 0; i < (int)items.size(); i++) {
        cout << items[i].second << '\n';
    }

    return 0;         // tells the computer the program finished successfully
}