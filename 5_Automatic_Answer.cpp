/*
=====================================================================
QUESTION SUMMARY: "Skill Testing Question"
=====================================================================
Alice must answer a math question to win a prize. The question has a
number n in it, and we are given several different values of n.

For each n, do these steps IN ORDER:
  1. Multiply n by 567
  2. Divide the result by 9
  3. Add 7492
  4. Multiply by 235
  5. Divide by 47
  6. Subtract 498
Then report the digit in the TENS column of the final answer.
(For 237617 the tens digit is 1, because the digits are ...6 1 7
 and the tens column is the second digit from the right.)

TASK: For every test case, print the tens digit of the final answer.

INPUT:
 - Line 1: t = number of test cases (1 <= t <= 100)
 - Next t lines: one integer n each (-1000 <= n <= 1000)

OUTPUT:
 - For each test case, one digit on its own line.

SAMPLE INPUT:
2
637
-120

SAMPLE OUTPUT:
1
3

WHY? (walking through the sample)
 n = 637:
   637 x 567 = 361179
   361179 / 9 = 40131
   40131 + 7492 = 47623
   47623 x 235 = 11191405
   11191405 / 47 = 238115
   238115 - 498 = 237617
   Tens digit of 237617 is 1.
 n = -120:
   -120 x 567 = -68040
   -68040 / 9 = -7560
   -7560 + 7492 = -68
   -68 x 235 = -15980
   -15980 / 47 = -340
   -340 - 498 = -838
   Ignore the minus sign: 838. Tens digit is 3.

KEY IDEAS:
 - Every division in this question comes out EXACTLY (no leftovers),
   because 567 is 9 x 63, and 235 is 47 x 5. So plain whole-number
   math is safe and never loses anything.
 - The answer can be NEGATIVE. We take the absolute value (remove
   the minus sign) before finding the tens digit.
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    int t;            // a box to hold t, the number of test cases
    cin >> t;         // read t from the input

    // Repeat once for each test case.
    // "i" counts the test cases, starting at 0 and stopping before t.
    for (int i = 0; i < t; i++) {

        int n;        // a box for the number n of THIS test case
        cin >> n;     // read n from the input

        // "long long" is a big number box. The numbers get large in the
        // middle of the steps, so we use it to be safe.
        long long x = n;

        // Follow the six steps from the question, one line each.
        x = x * 567;       // step 1: multiply by 567
        x = x / 9;         // step 2: divide by 9  (always exact here)
        x = x + 7492;      // step 3: add 7492
        x = x * 235;       // step 4: multiply by 235
        x = x / 47;        // step 5: divide by 47 (always exact here)
        x = x - 498;       // step 6: subtract 498

        // The answer might be negative (for example -838).
        // If x is below zero, flip its sign so it becomes positive.
        // After this, -838 becomes 838.
        if (x < 0) {
            x = -x;
        }

        // Now find the digit in the tens column.
        //   x / 10 throws away the last digit:  237617 / 10 = 23761
        //   (whole-number division drops the leftover part)
        //   Then "% 10" gives the LAST digit of that: 23761 % 10 = 1
        // So the last digit of (x / 10) is the tens digit of x.
        int tensDigit = (x / 10) % 10;

        cout << tensDigit << endl;   // print the digit on its own line
    }

    return 0;                        // tells the computer the program finished successfully
}