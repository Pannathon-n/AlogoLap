/*
=====================================================================
QUESTION SUMMARY: "List sum (recursion practice 3)"
=====================================================================
You are given a list of N integers (1 <= N <= 1000), each between
1 and 1000.
TASK: Find the SUM of all the integers.

RULES:
 - Only use addition (+), subtraction (-) and comparisons
   (<, >, <=, >=, ==).
 - NO loops (for, while) inside the function that does the summing.
 - You MUST use RECURSION (a function that calls itself).
 - The website template gives helper functions is_empty and is_last.
   We cannot see that template here, so below we write our own simple
   version of the same idea. If you use the official template, keep
   its helper functions and only copy the recursive idea.

INPUT:
 - Line 1: N
 - Next N lines: one integer per line.

OUTPUT:
 - One integer: the sum.

SAMPLE INPUT:
5
4
2
1
3
5
SAMPLE OUTPUT:
15

WHY? (the recursive idea)
 The sum of a list = (first number) + (sum of the REST of the list).
 The STOP rule (base case): when we have gone past the last number,
 the sum of "nothing" is 0.
 Example for 4 2 1 3 5:
     sum = 4 + (2 + (1 + (3 + (5 + 0)))) = 15
 Each call looks at ONE position (index), then calls itself for the
 next position. The problem gets smaller until we run out of numbers.

NOTE ABOUT READING INPUT:
 Reading the numbers uses a loop in main(). That is fine: the rule
 "no loops" is about the function that computes the sum. (If your
 course also wants input read without loops, tell me and I will
 change it.)
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
#include <vector>     // lets us use "vector" (a list that can grow)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

// Returns the sum of the numbers in list "a" from position "index"
// to the end of the list. The "&" means we do not copy the list.
int listSum(const vector<int>& a, int index) {

    // BASE CASE (the stop rule): if index is past the last number,
    // there is nothing left to add, so the sum is 0.
    if (index >= (int)a.size()) {
        return 0;
    }

    // RECURSIVE CASE: this number + the sum of everything after it.
    // The call uses index + 1, so the problem gets smaller each time.
    return a[index] + listSum(a, index + 1);
}

int main() {          // every C++ program starts running here

    int n;            // a box to hold N, how many numbers there are
    cin >> n;

    vector<int> a(n); // the list of numbers
    for (int i = 0; i < n; i++) {
        cin >> a[i];  // read each number
    }

    // Start the recursion at position 0 (the first number).
    cout << listSum(a, 0) << endl;

    return 0;         // tells the computer the program finished successfully
}