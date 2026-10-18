/*
=====================================================================
QUESTION SUMMARY: "Plateau and Swamp"
=====================================================================
We get the heights of N areas in a row.
 - PLATEAU: a run of consecutive areas with EQUAL height, where the
            area on the left AND the area on the right are both LOWER.
 - SWAMP:   a run of consecutive areas with EQUAL height, where the
            area on the left AND the area on the right are both HIGHER.
 - A run can be a single area.
 - A run touching the left end or the right end of the row can never
   be a plateau or a swamp (one neighbor is unknown).

TASK: Print two numbers on one line:
      (number of AREAS that are plateaus) (number of AREAS that are swamps)
      NOTE: we count AREAS (cells), not runs. A plateau "8 8" counts as 2.

INPUT:
 - Line 1: N (1 <= N <= 1000)
 - Line 2: N heights

OUTPUT:
 - One line: plateau areas, then swamp areas.

SAMPLE INPUT 1:
12
1 2 3 3 2 2 4 5 6 5 4 5
SAMPLE OUTPUT 1:
3 3

WHY "3 3"? (walking through sample 1)
 Runs: 1 | 2 | 3 3 | 2 2 | 4 | 5 | 6 | 5 | 4 | 5
 "3 3": neighbors 2 and 2, both lower  -> plateau, 2 areas
 "2 2": neighbors 3 and 4, both higher -> swamp,   2 areas
 "6"  : neighbors 5 and 5, both lower  -> plateau, 1 area
 "4"  : neighbors 5 and 5, both higher -> swamp,   1 area
 Other runs have one lower and one higher neighbor (or touch an end).
 Plateau areas = 2 + 1 = 3. Swamp areas = 2 + 1 = 3.

SAMPLE INPUT 2:
24
5 5 6 8 8 2 4 4 6 5 4 4 6 7 6 6 9 9 6 5 4 6 8 5
SAMPLE OUTPUT 2:
7 6
 (Plateaus: 8 8, 6, 7, 9 9, 8 = 2+1+1+2+1 = 7.
  Swamps: 2, 4 4, 6 6, 4 = 1+2+2+1 = 6.)

KEY IDEA:
 Walk through the array and find each RUN of equal heights, from
 position "start" to position "end". If the run has a left neighbor
 (start > 0) and a right neighbor (end < n-1), compare:
   both neighbors lower  -> add the run's length to plateau
   both neighbors higher -> add the run's length to swamp
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
#include <vector>     // lets us use "vector" (a list that can grow)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    int n;            // a box to hold N, the number of areas
    cin >> n;

    vector<int> h(n); // the heights
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }

    int plateau = 0;  // number of AREAS that are plateaus
    int swamp = 0;    // number of AREAS that are swamps

    int start = 0;    // where the current run of equal heights begins

    while (start < n) {

        // Find where this run ends: move "end" forward while the next
        // height is the same as the height at "start".
        int end = start;
        while (end + 1 < n && h[end + 1] == h[start]) {
            end++;
        }

        // Only runs with a neighbor on BOTH sides can count.
        if (start > 0 && end < n - 1) {
            int left = h[start - 1];    // height just left of the run
            int right = h[end + 1];     // height just right of the run
            int length = end - start + 1;   // how many areas are in the run

            if (left < h[start] && right < h[start]) {
                plateau = plateau + length;   // both neighbors lower
            } else if (left > h[start] && right > h[start]) {
                swamp = swamp + length;       // both neighbors higher
            }
        }

        start = end + 1;   // the next run begins right after this one
    }

    cout << plateau << " " << swamp << endl;

    return 0;         // tells the computer the program finished successfully
}