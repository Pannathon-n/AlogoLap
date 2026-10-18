/*
=====================================================================
QUESTION SUMMARY: "Shadow"
=====================================================================
A street is divided into L blocks (positions 0, 1, 2, ..., L-1).
There are N buildings. Building i stands at position Xi and has
height Hi. Every building is 1 block wide.

Each building casts a shadow on the street:
 - The shadow covers its own block AND the next Hi blocks after it.
 - So the shadow covers positions Xi, Xi+1, ..., Xi+Hi
   (that is Hi + 1 blocks).
 - Shadows can overlap, and they can stick out past the end of the
   street. We only care about blocks that are INSIDE the street
   (positions 0 to L-1).

TASK: Print how many street blocks are covered by at least one shadow.
      (A block covered by two shadows still counts only ONCE.)

INPUT:
 - Line 1: N and L (1 <= N <= 1000, 1 <= L <= 3000)
 - Next N lines: Xi and Hi
       (0 <= Xi <= L-1, 1 <= Hi <= 1000)

OUTPUT:
 - One integer: the number of shaded blocks on the street.

SAMPLE INPUT:
3 11
5 3
1 2
7 4

SAMPLE OUTPUT:
9

WHY 9? (walking through the sample, street positions 0 to 10)
 Building at 5, height 3: shadow on positions 5, 6, 7, 8
 Building at 1, height 2: shadow on positions 1, 2, 3
 Building at 7, height 4: shadow on positions 7, 8, 9, 10, 11
                          (11 is outside the street, so we ignore it)
 Position:  0 1 2 3 4 5 6 7 8 9 10
 Shaded?    . X X X . X X X X X X
 Shaded blocks: 1,2,3,5,6,7,8,9,10 = 9 blocks.

KEY IDEA:
 The street is small (at most 3000 blocks), so we use a list of
 true/false marks, one per block: "is this block shaded?"
 For each building we mark every block its shadow covers (skipping
 any block past the end of the street). Marking an already-marked
 block does nothing, so overlaps are never counted twice.
 At the end, we count how many marks are true.
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
#include <vector>     // lets us use "vector" (a list of values)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    int n, l;         // n = number of buildings, l = length of the street
    cin >> n >> l;    // read both numbers

    // shaded[p] is true if street block p is under a shadow.
    // The street has blocks 0 to l-1, so we need l spots.
    // "false" means every block starts as "not shaded".
    vector<bool> shaded(l, false);

    // Repeat once for each building.
    for (int i = 0; i < n; i++) {

        int x, h;         // x = building position, h = building height
        cin >> x >> h;    // read both numbers

        // The shadow covers blocks x, x+1, ..., x+h (that is h+1 blocks).
        // "p" is the block we are marking.
        for (int p = x; p <= x + h; p++) {

            // Only mark blocks that are INSIDE the street.
            // Blocks at position l or beyond are off the street, so we
            // ignore them (this also keeps us from writing outside the list).
            if (p < l) {
                shaded[p] = true;   // mark this block as shaded
            }
        }
    }

    // Count how many blocks are marked as shaded.
    int count = 0;
    for (int p = 0; p < l; p++) {
        if (shaded[p]) {
            count = count + 1;   // this block is shaded, count it
        }
    }

    cout << count << endl;   // print the total shaded length

    return 0;                // tells the computer the program finished successfully
}