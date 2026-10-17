/*
=====================================================================
QUESTION SUMMARY: "EXP"
=====================================================================
You play an online game for N days in a row. Each day you earn some
EXP points (a score for your progress).

BONUS RULE:
 - Every 4th day of playing (day 4, day 8, day 12, ...) is a bonus day.
 - On a bonus day, the EXP you earn is DOUBLED.
 - All other days count normally.

TASK: Read the EXP for each day and print the TOTAL EXP.

INPUT:
 - Line 1: N = number of days (1 <= N <= 1000)
 - Next N lines: one number per line, the EXP earned that day.
   (The total will never be more than 1,000,000,000.)

OUTPUT:
 - One integer: the total EXP.

SAMPLE INPUT 1:
9
1
2
3
4
5
6
7
8
9

SAMPLE OUTPUT 1:
57

WHY 57? (walking through the sample)
 Day 1: 1        -> normal      -> adds 1
 Day 2: 2        -> normal      -> adds 2
 Day 3: 3        -> normal      -> adds 3
 Day 4: 4        -> BONUS (x2)  -> adds 8
 Day 5: 5        -> normal      -> adds 5
 Day 6: 6        -> normal      -> adds 6
 Day 7: 7        -> normal      -> adds 7
 Day 8: 8        -> BONUS (x2)  -> adds 16
 Day 9: 9        -> normal      -> adds 9
 Total = 1+2+3+8+5+6+7+16+9 = 57

SAMPLE INPUT 2:
4
1
1
1
1

SAMPLE OUTPUT 2:
5      (because 1 + 1 + 1 + (1 x 2) = 5)
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    int n;            // a box to hold N, the number of days
    cin >> n;         // read N from the input

    // A box to hold the running total EXP.
    // "long long" is a big number box, so a large total will fit safely.
    // It starts at 0 because we have not earned anything yet.
    long long total = 0;

    // Repeat once for each day.
    // "day" is a counter that starts at 1 (day 1) and goes up to n.
    // We start at 1 (not 0) because humans count days as 1, 2, 3, ...
    // and the bonus rule is about the 4th, 8th, 12th day, and so on.
    for (int day = 1; day <= n; day++) {

        int exp;      // a box for the EXP earned on THIS day
        cin >> exp;   // read today's EXP from the input

        // "%" is the "remainder" operator: it gives what is left over
        // after dividing.
        //   4 % 4 = 0   (4 divided by 4 leaves nothing)
        //   8 % 4 = 0
        //   5 % 4 = 1   (5 divided by 4 leaves 1)
        // So "day % 4 == 0" is true on day 4, 8, 12, 16, ...
        // which are exactly the bonus days!
        if (day % 4 == 0) {
            exp = exp * 2;   // bonus day: double the EXP
        }

        total = total + exp; // add today's EXP (doubled or not) to the total
    }

    cout << total << endl;   // print the final total

    return 0;                // tells the computer the program finished successfully
}