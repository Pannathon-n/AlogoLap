/*
=====================================================================
QUESTION SUMMARY: "Multiplication (recursion practice 1)"
=====================================================================
You are given two whole numbers A and B (0 <= A <= 1000, 0 <= B <= 1000).
TASK: Compute A x B, but with strict rules:
 - You may ONLY use addition (+), subtraction (-), and comparisons
   (<, >, <=, >=, ==).
 - You may NOT use the * operator.
 - You may NOT use loops (for, while).
 - You MUST use RECURSION (a function that calls itself).

INPUT:
 - One line with two integers A and B.

OUTPUT:
 - One integer: A x B.

SAMPLE INPUT:
120 30
SAMPLE OUTPUT:
3600

WHY? (the idea behind multiplication)
 Multiplying is just repeated adding:
     A x B = A + A + A + ... (B times)
 We can say it in a "recursive" way:
     A x B = A + (A x (B - 1))     when B is bigger than 0
     A x 0 = 0                     (this is the STOP rule)
 Example: 3 x 2
     = 3 + (3 x 1)
     = 3 + (3 + (3 x 0))
     = 3 + (3 + 0)
     = 6

WHAT IS RECURSION?
 A recursive function solves a big problem by calling ITSELF on a
 smaller version of the same problem. It must have a STOP rule
 (called the "base case"), otherwise it would call itself forever.
 Here the problem gets smaller because B goes down by 1 each time,
 until B reaches 0 (the base case).
 With B up to 1000, we go at most about 1000 calls deep, which is safe.
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

// This function returns a x b, using only + and - and recursion.
int multiply(int a, int b) {

    // BASE CASE (the stop rule): anything times 0 is 0.
    // We return right away, so the function stops calling itself.
    if (b == 0) {
        return 0;
    }

    // RECURSIVE CASE: a x b = a + (a x (b - 1)).
    // The function calls itself with a SMALLER b (one less),
    // then adds a to whatever comes back.
    return a + multiply(a, b - 1);
}

int main() {          // every C++ program starts running here

    int a, b;         // two boxes for the numbers A and B
    cin >> a >> b;    // read both from the input

    cout << multiply(a, b) << endl;   // compute and print A x B

    return 0;         // tells the computer the program finished successfully
}