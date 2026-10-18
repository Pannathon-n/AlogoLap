/*
=====================================================================
QUESTION SUMMARY: "Age Sort"
=====================================================================
You are given the ages of all people in a country. Every age is at
least 1 and below 100 (nobody lives to 100 or more).

TASK: For each test case, print all the ages sorted from smallest to
      largest, separated by spaces, on one line.

INPUT (many test cases):
 - Each case: a line with n (0 < n <= 2,000,000), then a line with
   n ages.
 - A case with n = 0 ends the input. Do NOT process it.

OUTPUT:
 - For each case, one line with the n ages in ascending order,
   separated by single spaces.

WARNING: The input is huge (about 25 MB), so we need FAST input and
output.

SAMPLE INPUT:
5
3 4 2 1 5
5
2 3 2 3 1
0

SAMPLE OUTPUT:
1 2 3 4 5
1 2 2 3 3

WHY? (walking through the second case)
 Ages: 2 3 2 3 1
 Count: age 1 appears 1 time, age 2 appears 2 times, age 3 appears 2 times.
 Printing each age as many times as it appeared, smallest first:
 1 2 2 3 3

KEY IDEA (COUNTING SORT):
 A normal sort on 2 million numbers works, but we can do better.
 Ages are only between 1 and 99, so there are only 99 possible values!
 So instead of sorting, we just COUNT how many times each age appears:
     count[age] = number of people with that age.
 Then we walk through the ages 1, 2, 3, ..., 99 and print each age
 exactly count[age] times. That is automatically sorted, and very fast.
 We also never need to store the n numbers: we count them as we read.
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    // Magic speed-up lines. They make reading and printing millions of
    // numbers much faster. (The question warns that the input is big.)
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;            // a box to hold n, the number of people in a case

    // Read n. Keep going while reading works AND n is not 0.
    // When n is 0 we reach the final "0" line and stop.
    // Each time around this loop handles ONE test case.
    while (cin >> n && n != 0) {

        // count[a] = how many people have age a.
        // Ages go up to 99, so we need 100 spots (0 to 99).
        // "= {0}" makes every count start at 0 for each new test case.
        int count[100] = {0};

        // Read the n ages and count each one.
        for (int i = 0; i < n; i++) {
            int age;
            cin >> age;       // read one age
            count[age]++;     // one more person with this age
        }

        // Print the ages in ascending order.
        // "first" helps us put spaces BETWEEN numbers only
        // (no space before the first number, none after the last).
        bool first = true;

        // Go through every possible age from 1 up to 99.
        for (int age = 1; age < 100; age++) {

            // Print this age as many times as it appeared.
            for (int k = 0; k < count[age]; k++) {
                if (!first) {
                    cout << ' ';   // a space before every number except the first
                }
                cout << age;       // print the age
                first = false;
            }
        }

        cout << '\n';   // end the line (faster than endl)
    }

    return 0;           // tells the computer the program finished successfully
}