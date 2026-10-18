/*
=====================================================================
QUESTION SUMMARY: "Accelerator"
=====================================================================
A rocket starts on the ground with speed 0 at second 0.
We look at it second by second.

At each second T:
 - If the engine IGNITES at second T, then in second T+1 the speed
   goes UP by S units.
 - If the engine does NOT ignite at second T, then in second T+1 the
   speed goes DOWN by 1 unit, but never below 0.

We are given the N seconds when the engine ignites (in increasing
order) and the boost S.

TASK: Print the HIGHEST speed the rocket ever reaches.

INPUT:
 - Line 1: N and S (1 <= N <= 1000, 1 <= S <= 1000)
 - Line 2: N increasing times T1, T2, ..., TN (0 <= Ti <= 10000)

OUTPUT:
 - One integer: the highest speed.

SAMPLE INPUT 1:
5 5
2 4 5 10 13
SAMPLE OUTPUT 1:
18

SAMPLE INPUT 2:
4 3
0 1 2 14
SAMPLE OUTPUT 2:
9

WHY 9? (walking through sample 2, S = 3, ignites at 0, 1, 2, 14)
 Second 0: speed 0.  Ignites at 0 -> next second speed = 0 + 3 = 3
 Second 1: speed 3.  Ignites at 1 -> next second speed = 3 + 3 = 6
 Second 2: speed 6.  Ignites at 2 -> next second speed = 6 + 3 = 9
 Second 3: speed 9.  No ignite -> next second speed = 8
 ... it keeps falling by 1 each second. The highest was 9.

KEY IDEA:
 Simulate every second, from 0 up to a little past the last ignition.
 Times are at most 10,000, so this is tiny and fast.
 We use a list of true/false marks: ignites[t] is true if the engine
 ignites at second t. Then for each second we update the speed using
 the rule, and remember the biggest speed we have seen.
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
#include <vector>     // lets us use "vector" (a list of values)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    int n, s;         // n = number of ignitions, s = speed boost each time
    cin >> n >> s;    // read both numbers

    // ignites[t] is true if the engine ignites at second t.
    // Times go up to 10,000, so we make 10,002 spots (a little extra).
    // Every spot starts as false ("no ignition").
    vector<bool> ignites(10002, false);

    // Read the N ignition times and mark each one as true.
    for (int i = 0; i < n; i++) {
        int t;
        cin >> t;
        ignites[t] = true;
    }

    int speed = 0;    // the current speed. It is 0 at second 0.
    int best = 0;     // the highest speed seen so far

    // Go through every second from 0 up to 10,000.
    // At each second we decide what the speed will be in the NEXT second.
    for (int t = 0; t <= 10000; t++) {

        if (ignites[t]) {
            speed = speed + s;       // engine ignited: speed goes up by S
        } else {
            if (speed > 0) {
                speed = speed - 1;   // no ignition: speed drops by 1
            }
            // If speed is already 0, it stays 0 (never below 0).
        }

        // "speed" is now the speed at second t+1.
        // If it is a new record, remember it.
        if (speed > best) {
            best = speed;
        }
    }

    cout << best << endl;   // print the highest speed

    return 0;               // tells the computer the program finished successfully
}