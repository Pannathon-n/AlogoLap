/*
=====================================================================
QUESTION SUMMARY: "List max (recursion practice 4)"
=====================================================================
You are given a list of N integers (1 <= N <= 1000), each between
1 and 1000.
TASK: Find the BIGGEST (maximum) integer in the list.

RULES:
 - Only use addition (+), subtraction (-) and comparisons
   (<, >, <=, >=, ==).
 - NO loops (for, while) inside the function that finds the maximum.
 - You MUST use RECURSION (a function that calls itself).
 - The website template gives helper functions is_empty and is_last.
   We cannot see that template here, so we write our own simple
   version of the same idea. If you use the official template, keep
   its helper functions and copy only the recursive idea.

INPUT:
 - Line 1: N
 - Next N lines: one integer per line.

OUTPUT:
 - One integer: the maximum.

SAMPLE INPUT:
6
4
2
1
3
5
3
SAMPLE OUTPUT:
5

(The sample shows N = 6 and the six numbers 4 2 1 3 5 3.
 The biggest is 5.)

WHY? (the recursive idea)
 The max of a list = the bigger of:
     (the first number)  and  (the max of the REST of the list).
 The STOP rule (base case): when only ONE number is left (the last
 one), that number is the max.
 Example for 4 2 1 3 5 3:
     max(4, max(2, max(1, max(3, max(5, 3)))))
   = max(4, max(2, max(1, max(3, 5))))
   = max(4, max(2, max(1, 5)))
   = max(4, max(2, 5))
   = max(4, 5)
   = 5
 Each call looks at ONE position (index) and then calls itself for
 the next position, so the problem gets smaller every time.

NOTE ABOUT READING INPUT:
 Reading the numbers uses a loop in main(). That is fine: the rule
 "no loops" is about the function that finds the maximum.
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
#include <vector>     // lets us use "vector" (a list that can grow)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

// Returns the biggest number in list "a" from position "index" to the end.
// The "&" means we do not copy the list.
int listMax(const vector<int>& a, int index) {

    // BASE CASE (the stop rule): if this is the LAST number, there is
    // nothing else to compare with, so it is the max of what is left.
    if (index == (int)a.size() - 1) {
        return a[index];
    }

    // RECURSIVE CASE: first find the max of everything AFTER this number.
    // The call uses index + 1, so the problem gets smaller each time.
    int maxOfRest = listMax(a, index + 1);

    // Compare this number with the max of the rest, and return the bigger.
    if (a[index] > maxOfRest) {
        return a[index];
    } else {
        return maxOfRest;
    }
}

int main() {          // every C++ program starts running here

    int n;            // a box to hold N, how many numbers there are
    cin >> n;

    vector<int> a(n); // the list of numbers
    for (int i = 0; i < n; i++) {
        cin >> a[i];  // read each number
    }

    // Start the recursion at position 0 (the first number).
    cout << listMax(a, 0) << endl;

    return 0;         // tells the computer the program finished successfully
}