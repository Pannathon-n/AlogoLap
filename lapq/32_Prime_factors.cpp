/*
=====================================================================
QUESTION SUMMARY: "Prime Factors"
=====================================================================
A PRIME number is a number bigger than 1 that can only be divided
evenly by 1 and itself (2, 3, 5, 7, 11, ...).

Given an integer N (2 <= N <= 100,000), count how many DIFFERENT
prime numbers divide N evenly.
(Each prime is counted ONCE, even if it divides N many times.)

INPUT:
 - One line with the integer N.

OUTPUT:  
 - One integer: the number of distinct prime factors of N.

SAMPLES:
 N = 2      -> 1   (only 2)
 N = 16     -> 1   (16 = 2*2*2*2, only the prime 2)
 N = 750    -> 3   (750 = 2 * 3 * 5 * 5 * 5, primes 2, 3, 5)
 N = 30030  -> 6   (30030 = 2 * 3 * 5 * 7 * 11 * 13)
 N = 28672  -> 2   (28672 = 2^12 * 7, primes 2 and 7)

WHY 3 FOR 750? (walking through the method)
 750 divisible by 2? Yes -> count 1. Divide: 375. (no more 2s)
 375 divisible by 3? Yes -> count 2. Divide: 125. (no more 3s)
 125 divisible by 4? No.
 125 divisible by 5? Yes -> count 3. Divide: 25, 5, 1.
 N is now 1, so we are done. Answer = 3.

KEY IDEA (trial division):
 Try the divisors d = 2, 3, 4, 5, ... one at a time.
 When d divides N:
   - count one new prime factor,
   - then keep dividing N by d until it no longer divides,
     which removes ALL copies of that prime.
 Because we remove each prime completely before moving on, any d that
 divides N at the moment we reach it is automatically a PRIME (all of
 its smaller prime pieces were already removed). So we never need to
 check whether d is prime.
 We only need to try d while d * d <= N. If something bigger than 1 is
 left over at the end, it must be one last prime factor, so we count
 it too.
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    int n;            // a box to hold N
    cin >> n;         // read N from the input

    int count = 0;    // how many distinct prime factors we have found so far

    // Try d = 2, 3, 4, ... as long as d * d is not bigger than n.
    // (If n had a factor bigger than its square root, the other
    // matching factor would be smaller, so we would already have found it.)
    for (int d = 2; d * d <= n; d++) {

        if (n % d == 0) {
            // "%" gives the remainder. A remainder of 0 means d divides n
            // evenly, so d is a prime factor.
            count = count + 1;     // we found a new distinct prime

            // Remove ALL copies of this prime from n.
            // Example: n = 16, d = 2 -> 8 -> 4 -> 2 -> 1.
            while (n % d == 0) {
                n = n / d;
            }
        }
    }

    // After the loop, if n is still bigger than 1, what is left is
    // one more prime number (bigger than all the d we tried).
    // Example: n = 14: d = 2 removes the 2, leaving 7, which is prime.
    if (n > 1) {
        count = count + 1;
    }

    cout << count << endl;   // print the number of distinct prime factors

    return 0;                // tells the computer the program finished successfully
}