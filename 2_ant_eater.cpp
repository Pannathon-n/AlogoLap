/*
=====================================================================
QUESTION SUMMARY: "Ant Eaters"
=====================================================================
An anteater eats ants every day, but there are rules:
 - It can eat AT MOST 1,000 ants in one day.
 - If it eats 1,000 ants (the maximum), it is too full, so the NEXT
   day it eats nothing (it rests).
 - The day before the data starts, it did not eat anything, so it
   is ready to eat on day 1.

We are told how many ants are available on each day.
TASK: Work out the TOTAL number of ants the anteater eats.

INPUT:
 - Line 1: N = number of days (1 <= N <= 1000)
 - Line 2: N integers = ants available each day (each <= 1,000,000)

OUTPUT:
 - One integer: the total ants eaten.

SAMPLE INPUT:
5
999 500 1000 500 400

SAMPLE OUTPUT:
2899

WHY 2899? (walking through the sample)
 Day 1: 999 available  -> eats 999   (less than 1000, so no rest)
 Day 2: 500 available  -> eats 500   (total so far 1499)
 Day 3: 1000 available -> eats 1000  (maximum! so it rests tomorrow)
 Day 4: 500 available  -> RESTING, eats 0
 Day 5: 400 available  -> eats 400
 Total = 999 + 500 + 1000 + 0 + 400 = 2899
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    int n;            // a box to hold N, the number of days
    cin >> n;         // read N from the input

    // A box to hold the running total of ants eaten.
    // "long long" is a big number box (safer than plain int).
    // It starts at 0 because nothing has been eaten yet.
    long long total = 0;

    // This true/false box remembers: is the anteater resting TODAY?
    //   true  = it ate 1000 yesterday, so today it eats nothing
    //   false = it is free to eat today
    // It starts as false because the day before day 1, it ate nothing.
    // It is declared OUTSIDE the loop so it remembers its value from
    // one day to the next.
    bool isResting = false;

    // Repeat once for each day: day 1, day 2, ... day n.
    // "i" counts the days, starting at 0 and stopping before n.
    for (int i = 0; i < n; i++) {

        int ants;     // a box for the ants available TODAY
        cin >> ants;  // read today's number from the input.
                      // IMPORTANT: we read it even on a resting day,
                      // otherwise the numbers would get out of sync.

        if (isResting) {
            // The anteater ate 1000 yesterday, so it eats nothing today.
            isResting = false;   // tomorrow it is hungry again
            // Nothing is added to the total on a resting day.
        } else {
            // The anteater can eat today.
            // It eats everything available, BUT never more than 1000.
            int eaten = ants;        // start by assuming it eats all of them
            if (eaten > 1000) {
                eaten = 1000;        // too many! it can only eat 1000
            }

            total = total + eaten;   // add today's meal to the running total

            // If it ate the maximum (1000), it must rest tomorrow.
            if (eaten == 1000) {
                isResting = true;
            }
        }
    }

    cout << total << endl;   // print the final total

    return 0;                // tells the computer the program finished successfully
}