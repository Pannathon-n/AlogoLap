/*
=====================================================================
QUESTION SUMMARY: "A to B"
=====================================================================
You are given two whole numbers, A and B, where A is smaller than B.
TASK: Add up every whole number from A to B, including both A and B.
      That is:  A + (A+1) + (A+2) + ... + (B-1) + B

INPUT:
 - One line with two integers: A and B
   (0 <= A < B <= 10,000)

OUTPUT:
 - One integer: the sum of all numbers from A to B.

SAMPLE INPUT:
1 10

SAMPLE OUTPUT:
55

WHY 55? (walking through the sample)
 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 + 10 = 55

SIZE CHECK:
 The biggest possible sum is about 0 + 1 + ... + 10000 = 50,005,000.
 That fits in a normal int (limit is about 2 billion), but we use
 "long long" anyway to be extra safe.
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    int a, b;         // two boxes: a = start number, b = end number
    cin >> a >> b;    // read both numbers from the input

    // A box to hold the running total.
    // It starts at 0 because we have not added anything yet.
    long long sum = 0;

    // Count from a up to b, one number at a time.
    // "i" starts at a, and after each round "i++" adds 1 to it.
    // "i <= b" means we keep going until we have used b as well
    // (the "=" is important: it makes b INCLUDED in the sum).
    for (int i = a; i <= b; i++) {
        sum = sum + i;   // add the current number to the running total
    }

    cout << sum << endl; // print the final total

    return 0;            // tells the computer the program finished successfully
}