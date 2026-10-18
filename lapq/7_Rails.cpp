/*
=====================================================================
QUESTION SUMMARY: "Rails" (PopPush railway station)
=====================================================================
A train arrives from direction A with N coaches in the order
1, 2, 3, ..., N. The station is a DEAD END with only ONE track, so it
works like a STACK (a pile of plates):
 - A coach enters the station from side A. It goes on TOP of the pile.
 - A coach can only leave toward side B from the TOP of the pile
   (the one that entered most recently).
 - Once a coach enters the station it cannot go back to A.
 - Once a coach leaves toward B it cannot come back.
 - Coaches from A must enter in order 1, 2, 3, ... (they can't skip).

We are given a wanted order a1, a2, ..., aN for the coaches leaving
toward B.
TASK: Decide if that order is possible. Print "Yes" or "No".

INPUT (many blocks):
 - A block starts with N. A line with just 0 instead of N means the
   whole input is finished.
 - After N, there are several lines, each a wanted order (a
   permutation of 1..N).
 - A line with just 0 ends the block.

OUTPUT:
 - One line "Yes" or "No" for each wanted order.
 - After each block, print ONE EMPTY LINE.
 - Print nothing for the final "0".

SAMPLE INPUT:
5
1 2 3 4 5
5 4 1 2 3
0
6
6 5 4 3 2 1
0
0

SAMPLE OUTPUT:
Yes
No

Yes

(The empty lines are the one blank line after each block.)

WHY? (walking through the sample, N = 5)
 Wanted 1 2 3 4 5 -> Yes:
   push 1, pop 1. push 2, pop 2. ... each coach goes in and straight out.
 Wanted 5 4 1 2 3 -> No:
   To get 5 out first, we must push 1,2,3,4,5 and pop 5.
   Then 4 is on top -> pop 4. Now the pile is [1, 2, 3] with 3 on top.
   We want 1 next, but 3 is on top and 1 is buried underneath.
   No coaches are left to push, so it is impossible.
 Wanted 6 5 4 3 2 1 (N = 6) -> Yes:
   Push all of 1..6, then pop them one by one: 6,5,4,3,2,1.

STRATEGY (simulate the station with a stack):
 For each wanted coach, in order:
   - If it is NOT on top of the pile, push the next waiting coaches
     (1, 2, 3, ...) onto the pile until it is on top.
   - If we run out of coaches to push and it is still not on top,
     the answer is "No".
   - Otherwise pop it (it leaves toward B) and go on to the next one.
 If we manage to pop every wanted coach, the answer is "Yes".
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
#include <vector>     // lets us use "vector" (a list of numbers)
#include <stack>      // lets us use "stack" (a pile where you only touch the top)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    int n;            // a box to hold N, the number of coaches in a block

    // Read N. Keep going as long as the reading worked AND n is not 0.
    // When n is 0, that is the final "0" line, so the loop stops.
    // Each time around this loop handles ONE block of the input.
    while (cin >> n && n != 0) {

        // This loop handles each wanted order inside the block.
        // It stops when we see the "0" line that ends the block.
        while (true) {

            int first;         // the FIRST number of the line
            cin >> first;

            // If the first number is 0, this line is the block-ending "0",
            // not a wanted order. So leave this inner loop.
            if (first == 0) {
                break;
            }

            // A list to hold the wanted order for this line (n numbers).
            vector<int> target(n);
            target[0] = first;           // we already read the first number
            for (int i = 1; i < n; i++) {
                cin >> target[i];        // read the other n-1 numbers
            }

            // The station track. It acts like a pile: we can only add to
            // the top or take from the top.
            stack<int> station;

            // The number of the NEXT coach waiting outside at side A.
            // Coaches must enter in order, so it starts at 1.
            int nextCoach = 1;

            // This true/false box says whether the order is possible.
            // We assume "yes" until we find a problem.
            bool possible = true;

            // Go through the wanted order, one coach at a time.
            for (int i = 0; i < n; i++) {

                int want = target[i];   // the coach that must leave next

                // Keep pushing coaches into the station until the coach we
                // want is on TOP. Two cases make us push:
                //   - the station is empty (nothing to take out), or
                //   - the top coach is not the one we want.
                while (station.empty() || station.top() != want) {

                    // If there are no more coaches waiting outside
                    // (nextCoach is bigger than n), we can't push any
                    // more. The coach we want is buried, so it's impossible.
                    if (nextCoach > n) {
                        possible = false;
                        break;           // stop pushing
                    }

                    station.push(nextCoach);  // coach enters, lands on top
                    nextCoach++;              // the next waiting coach is now
                                              // one number higher
                }

                // If we gave up above, stop checking this wanted order.
                if (!possible) {
                    break;
                }

                // The wanted coach is on top now, so it leaves toward B.
                station.pop();
            }

            // Print the answer for this wanted order.
            if (possible) {
                cout << "Yes" << '\n';
            } else {
                cout << "No" << '\n';
            }
        }

        // The block is finished, so print ONE EMPTY LINE as required.
        cout << '\n';
    }

    return 0;         // tells the computer the program finished successfully
}