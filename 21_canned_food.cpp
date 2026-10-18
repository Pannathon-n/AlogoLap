/*
=====================================================================
QUESTION SUMMARY: "Canned food"
=====================================================================
You have N canned foods. A can is still GOOD quality only if BOTH
rules are true:
 - AGE rule:    its age is 400 days or LESS.
                (More than 400 days = lost quality. Exactly 400 is OK.)
 - WEIGHT rule: its weight is between 150 and 200 grams INCLUSIVE.
                (150 and 200 are both OK.)
If either rule is broken, the can has lost quality.

TASK: Count how many cans are still good.

INPUT:
 - Line 1: N = number of cans (1 <= N <= 100)
 - Next N lines: A and B
       A = age in days (1 to 1000)
       B = weight in grams (1 to 1000)

OUTPUT:
 - One integer: the number of good cans.

SAMPLE INPUT:
6
200 150
390 250
500 160
150 200
400 180
401 90

SAMPLE OUTPUT:
3

WHY 3? (walking through the sample)
 Can 1: age 200, weight 150 -> age OK, weight OK (150 is allowed)  GOOD
 Can 2: age 390, weight 250 -> weight too high                     bad
 Can 3: age 500, weight 160 -> age too high                        bad
 Can 4: age 150, weight 200 -> age OK, weight OK (200 is allowed)  GOOD
 Can 5: age 400, weight 180 -> age OK (400 is allowed), weight OK  GOOD
 Can 6: age 401, weight 90  -> age too high AND weight too low     bad
 Good cans = 3

TRICKY PART:
 Watch the edges! Age 400 is fine (use <=, not <).
 Weight 150 and 200 are fine (use >= and <=).
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    int n;            // a box to hold N, the number of cans
    cin >> n;         // read N from the input

    // A box to count the good cans. It starts at 0.
    int good = 0;

    // Repeat once for each can.
    for (int i = 0; i < n; i++) {

        int age, weight;       // boxes for this can's age and weight
        cin >> age >> weight;  // read both numbers

        // "&&" means AND: every part must be true.
        //   age <= 400                    -> not too old
        //   weight >= 150 AND weight <= 200 -> weight in the allowed range
        if (age <= 400 && weight >= 150 && weight <= 200) {
            good = good + 1;   // this can is good, so count it
        }
    }

    cout << good << endl;   // print how many good cans there are

    return 0;               // tells the computer the program finished successfully
}