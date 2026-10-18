/*
=====================================================================
QUESTION SUMMARY: "Climb"
=====================================================================
You walk along a mountain road with N stops. Stop i has height Hi.
You start at height 0 (this is H0 = 0).

Moving from stop (i-1) to stop i:
 - If Hi is HIGHER than Hi-1, you climb, and it costs energy:
        energy = (Hi - Hi-1) + M
   where M = how many climbs in a row you made just BEFORE this one.
   (Climbing again and again makes you more tired.)
 - If Hi is the same or LOWER, it costs 0 energy, and your tiredness
   resets: M goes back to 0 for the next step.

TASK: Print the total energy needed to reach the last stop.

INPUT:
 - Line 1: N = number of stops (1 <= N <= 1000)
 - Next N lines: Hi = height of stop i (0 <= Hi <= 10000)

OUTPUT:
 - One integer: the total energy.

SAMPLE INPUT:
10
5 7 7 10 5 3 10 15 18 4   (one number per line in the real input)

SAMPLE OUTPUT:
29

WHY 29? (walking through the sample)
 Start at height 0, tiredness (M) = 0.
 Stop 1:  0 -> 5   climb 5, M=0  -> energy 5+0 = 5    (M becomes 1)
 Stop 2:  5 -> 7   climb 2, M=1  -> energy 2+1 = 3    (M becomes 2)
 Stop 3:  7 -> 7   not a climb   -> energy 0          (M resets to 0)
 Stop 4:  7 -> 10  climb 3, M=0  -> energy 3+0 = 3    (M becomes 1)
 Stop 5:  10 -> 5  going down    -> energy 0          (M resets to 0)
 Stop 6:  5 -> 3   going down    -> energy 0          (M stays 0)
 Stop 7:  3 -> 10  climb 7, M=0  -> energy 7+0 = 7    (M becomes 1)
 Stop 8:  10 -> 15 climb 5, M=1  -> energy 5+1 = 6    (M becomes 2)
 Stop 9:  15 -> 18 climb 3, M=2  -> energy 3+2 = 5    (M becomes 3)
 Stop 10: 18 -> 4  going down    -> energy 0          (M resets to 0)
 Total = 5 + 3 + 3 + 7 + 6 + 5 = 29

KEY IDEA:
 Walk through the stops one by one. Remember two things:
   - the previous height
   - how many climbs in a row we have made so far (M)
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    int n;            // a box to hold N, the number of stops
    cin >> n;         // read N from the input

    // A box for the height of the previous stop.
    // It starts at 0 because the starting point has height 0.
    int previous = 0;

    // A box for M: how many climbs in a row we have just made.
    // It starts at 0 because we have not climbed anything yet.
    int climbsInARow = 0;

    // A box for the running total of energy. Starts at 0.
    long long total = 0;

    // Repeat once for each stop.
    for (int i = 0; i < n; i++) {

        int height;       // a box for the height of THIS stop
        cin >> height;    // read it from the input

        if (height > previous) {
            // We are climbing UP, so it costs energy:
            // the height gained, plus the extra tiredness (M).
            total = total + (height - previous) + climbsInARow;

            // We made one more climb in a row, so tiredness goes up.
            climbsInARow = climbsInARow + 1;

        } else {
            // Same height or going down: no energy is used,
            // and the chain of climbs is broken, so tiredness resets.
            climbsInARow = 0;
        }

        // This stop becomes the "previous" stop for the next round.
        previous = height;
    }

    cout << total << endl;   // print the total energy

    return 0;                // tells the computer the program finished successfully
}