/*
=====================================================================
QUESTION SUMMARY: "Color rocks"
=====================================================================
You receive N rocks, one at a time. Each rock has a color (a number).
Every new rock is put on TOP of a vertical pile.

MAGIC RULE: whenever there are K rocks of the SAME color sitting
right next to each other (consecutive) in the pile, those K rocks
disappear. K is either 2 or 3.

Because rocks disappear, the rocks that were underneath can end up
touching each other, and then they may disappear too.

TASK: After all N rocks have been received, print how many rocks are
      left in the pile.

INPUT:
 - Line 1: N and K (1 <= N <= 100,000, K is 2 or 3)
 - Line 2: N integers, the colors of the rocks in order
           (each color is between 1 and 1,000,000)

OUTPUT:
 - One integer: the number of rocks left.

SAMPLE INPUT 1:
11 2
1 2 4 4 3 5 5 2 2 3 9

SAMPLE OUTPUT 1:
3

WHY 3? (walking through sample 1, K = 2, pile shown bottom -> top)
 rock 1 -> [1]
 rock 2 -> [1 2]
 rock 4 -> [1 2 4]
 rock 4 -> [1 2 4 4]  two 4s touch, they disappear -> [1 2]
 rock 3 -> [1 2 3]
 rock 5 -> [1 2 3 5]
 rock 5 -> two 5s disappear -> [1 2 3]
 rock 2 -> [1 2 3 2]
 rock 2 -> two 2s disappear -> [1 2 3]
 rock 3 -> two 3s touch, they disappear -> [1 2]
 rock 9 -> [1 2 9]
 Final pile has 3 rocks.

SAMPLE INPUT 2:
11 3
1 1 2 5 5 4 4 4 5 2 2
SAMPLE OUTPUT 2:
2
 (Three 4s disappear, then the 5s touch and a third 5 arrives so
  three 5s disappear, then two 2s + a third 2 disappear. Left: 1 1.)

KEY IDEA:
 The pile is a STACK (a pile where you only touch the top).
 For each rock in the pile we also remember one extra number:
 "how many rocks of the same color are in a row ending at this rock".
 We call it the run length.
   - New rock has the same color as the top rock?
         run length = (top rock's run length) + 1
   - Otherwise: run length = 1.
 If the run length reaches K, we remove K rocks from the top.
 After removing, the rock now on top still has the correct run
 length written next to it, so everything keeps working.
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
#include <vector>     // lets us use "vector" (a list that can grow and shrink)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    // Magic speed-up lines so reading 100,000 numbers is fast.
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;         // n = number of rocks, k = how many in a row disappear
    cin >> n >> k;    // read both numbers

    // Our pile of rocks, stored as two lists that always have the
    // same length. Position 0 is the BOTTOM, the last position is the TOP.
    //   color[i] = the color of the i-th rock in the pile
    //   run[i]   = how many same-colored rocks in a row end at that rock
    vector<int> color;
    vector<int> run;

    // Repeat once for each rock that arrives.
    for (int i = 0; i < n; i++) {

        int c;        // a box for the color of the NEW rock
        cin >> c;     // read it from the input

        int newRun;   // a box for the run length of the new rock

        // Is the pile non-empty AND is the top rock the same color?
        // ("&&" means AND. color.back() is the last item = the top rock.)
        if (!color.empty() && color.back() == c) {
            newRun = run.back() + 1;   // one longer than the top's run
        } else {
            newRun = 1;                // different color (or empty pile)
        }

        // Put the new rock on top of the pile.
        color.push_back(c);
        newRun = newRun;               // (run length is already worked out)
        run.push_back(newRun);

        // Did we get K same-colored rocks in a row?
        if (newRun == k) {
            // Remove K rocks from the top of the pile.
            // pop_back() removes the last item of a list.
            for (int j = 0; j < k; j++) {
                color.pop_back();
                run.pop_back();
            }
        }
    }

    // color.size() tells us how many rocks are left in the pile.
    cout << color.size() << endl;

    return 0;         // tells the computer the program finished successfully
}