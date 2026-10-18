/*
=====================================================================
QUESTION SUMMARY: "Minimum Swaps" (sorting with adjacent flips)
=====================================================================
You are given N integers (N <= 1000). The ONLY operation allowed is
a "flip": swap two numbers that sit NEXT to each other.
TASK: Find the MINIMUM number of flips needed to sort the numbers in
      ascending order.

INPUT (many test cases, until the end of the file, "EOF"):
 - Each case: N, then N integers.

OUTPUT:
 - For each case, one line:
       Minimum exchange operations : M
   where M is the minimum number of flips.

SAMPLE INPUT:
3
1 2 3
3
2 3 1

SAMPLE OUTPUT:
Minimum exchange operations : 0
Minimum exchange operations : 2

WHY? (walking through the second case: 2 3 1)
 Flip 3 and 1 -> 2 1 3
 Flip 2 and 1 -> 1 2 3   (sorted after 2 flips)
 Fewer than 2 is impossible.

KEY IDEA (INVERSIONS):
 An "inversion" is a pair of numbers that are out of order: the LEFT
 number is BIGGER than the RIGHT number.
 For 2 3 1: the pairs (2,1) and (3,1) are inversions, so 2 inversions.
 Each flip of two neighbors can fix AT MOST ONE inversion, and we can
 always find a flip that fixes exactly one. So:
        minimum flips = number of inversions.
 (This is the same as "bubble sort" swap count.)

 Since N <= 1000, we can simply check EVERY pair of positions:
 about 500,000 pairs per case, which is fast enough.
 Equal numbers are NOT an inversion (we use ">" not ">="), because
 two equal numbers never need to be swapped.
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
#include <vector>     // lets us use "vector" (a list that can grow)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    int n;            // a box to hold N, the count of numbers in a case

    // Keep reading N while the reading works.
    // When the input reaches the end of the file (EOF), reading fails
    // and the loop stops. Each time around handles ONE test case.
    while (cin >> n) {

        vector<int> a(n);        // the list of n numbers
        for (int i = 0; i < n; i++) {
            cin >> a[i];         // read each number
        }

        // "long long" is a big number box. With 1000 numbers the count
        // is at most about 500,000, so int would fit, but this is safer.
        long long inversions = 0;

        // Look at every pair of positions (i, j) with i before j.
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                // If the left number is bigger than the right number,
                // the pair is out of order: one inversion.
                if (a[i] > a[j]) {
                    inversions = inversions + 1;
                }
            }
        }

        // Print the answer in the exact format the question wants.
        cout << "Minimum exchange operations : " << inversions << '\n';
    }

    return 0;         // tells the computer the program finished successfully
}