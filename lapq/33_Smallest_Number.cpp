/*
=====================================================================
QUESTION SUMMARY: "Smallest Number"
=====================================================================
You are given a very long number written as a string of n digits.
You must REMOVE exactly k digits. The remaining digits keep their
original order and form a new number with n-k digits.

TASK: Print the SMALLEST possible result.
      Leading zeros are kept and printed (00132468 is fine).

INPUT:
 - Line 1: n and k (2 <= n <= 100,000, 1 <= k < n)
 - Line 2: a string of n digits

OUTPUT:
 - One line: the smallest string of n-k digits.

SAMPLE INPUT 1:
5 1
13546
SAMPLE OUTPUT 1:
1346

SAMPLE INPUT 2:
6 2
658372
SAMPLE OUTPUT 2:
5372

SAMPLE INPUT 3:
10 2
0013572468
SAMPLE OUTPUT 3:
00132468

WHY? (walking through sample 1: 13546, remove 1 digit)
 Compare each digit with the one after it. The first time a digit is
 BIGGER than the next one, removing it makes the number smaller.
 1 < 3, 3 < 5, 5 > 4  -> remove the 5  -> 1346.

KEY IDEA (greedy with a stack):
 Because all results have the same length, the one that is smallest
 at the FIRST position that differs wins. So we want small digits as
 far LEFT as possible.
 Go through the digits from left to right, keeping a "result" pile:
   - While we still may remove digits (removed < k) AND the top digit
     of the pile is BIGGER than the new digit, pop the top (remove it).
     A bigger digit sitting before a smaller one makes the number larger.
   - Then push the new digit on the pile.
 At the end, if we have not removed k digits yet, the pile is in
 increasing order, so the biggest digits are at the END: remove them
 from the back.
 Finally the pile has exactly n-k digits.
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
#include <string>     // lets us use "string" (a variable that holds text)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    int n, k;         // n = number of digits, k = how many to remove
    cin >> n >> k;    // read both numbers

    string digits;    // a box for the long number, kept as TEXT
                      // (it is too long to fit in a normal number box)
    cin >> digits;    // read it

    // "result" works like a pile: we add and remove at the END only.
    string result = "";

    int removed = 0;  // how many digits we have removed so far

    // Look at each digit from left to right.
    for (int i = 0; i < n; i++) {

        char c = digits[i];   // the new digit

        // While we can still remove digits, the pile is not empty,
        // and the top digit is BIGGER than the new digit:
        // remove the top digit.
        // (Characters '0'..'9' compare in the same order as numbers.)
        while (removed < k && !result.empty() && result.back() > c) {
            result.pop_back();   // remove the last digit of the pile
            removed++;           // count it
        }

        result.push_back(c);     // put the new digit on the pile
    }

    // If we still have not removed k digits (for example 12345, where
    // nothing is bigger than what follows), remove from the END,
    // because the biggest digits are there.
    while (removed < k) {
        result.pop_back();
        removed++;
    }

    cout << result << endl;   // print the final smallest number

    return 0;                 // tells the computer the program finished successfully
}