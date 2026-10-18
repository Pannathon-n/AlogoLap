/*
=====================================================================
QUESTION SUMMARY: "ZamooZooma"
=====================================================================
You keep a line of balls. Each ball has a number on it. At the start
the line is empty.

Each step, a new ball arrives at either:
 - the FRONT of the line (D = 0), or
 - the END of the line   (D = 1).

RULE: If the line ALREADY has a ball with the same number as the new
ball, then both balls with that number, and EVERY ball between them,
are destroyed. (So the new ball is destroyed too and is not added.)

TASK: After all N steps, print how many balls are left in the line.

INPUT:
 - Line 1: N = number of steps (1 <= N <= 100,000)
 - Next N lines: D and A
       D = 0 -> ball arrives at the front
       D = 1 -> ball arrives at the end
       A = the number on the ball (1 <= A <= 200,000)

OUTPUT:
 - One integer: the number of balls remaining.

SAMPLE INPUT 1:
6
0 1
0 2
0 3
0 4
0 2
0 3

SAMPLE OUTPUT 1:
2

WHY 2? (walking through sample 1, line shown from front to end)
 0 1 -> [1]
 0 2 -> [2, 1]
 0 3 -> [3, 2, 1]
 0 4 -> [4, 3, 2, 1]
 0 2 -> ball 2 is already in the line. Destroy 4, 3, 2 (everything
        from the front up to the old 2). The new 2 is destroyed too.
        Line: [1]
 0 3 -> 3 is NOT in the line anymore (it was destroyed), so it is
        added: [3, 1]
 Final count = 2.

SAMPLE INPUT 2 (11 steps) gives output 1.
 (After all steps the line is just [12].)

KEY IDEAS:
 1) A "deque" (say "deck") is a list where you can add and remove
    quickly at BOTH the front and the end. Perfect for this problem.

 2) When a ball arrives at the FRONT and its number is already in the
    line, everything between the front and that old ball must go.
    That is simply "remove balls from the front, one by one, until we
    remove the ball with that number". The same is true for the END:
    remove from the end until we remove that number.
    So we never need to delete from the middle.

 3) We need a fast way to ask "is this number in the line right now?"
    We keep a true/false list called inLine. inLine[5] is true if a
    ball numbered 5 is in the line. (Numbers in the line are always
    different, because two equal numbers would have been destroyed.)

 4) It is fast: each ball is added once and removed at most once.
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
#include <deque>      // lets us use "deque" (a list with fast front AND end)
#include <vector>     // lets us use "vector" (a normal list of values)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    // These two lines make reading input faster (a "magic speed-up").
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;            // a box to hold N, the number of steps
    cin >> n;         // read N from the input

    // The line of balls. The FRONT of the deque is the front of the line.
    deque<int> line;

    // inLine[a] is true if a ball numbered a is in the line right now.
    // Ball numbers go up to 200,000, so we need 200,001 spots
    // (spot 0 is unused). "false" means every spot starts as "not in line".
    vector<bool> inLine(200001, false);

    // Repeat once for each step.
    for (int i = 0; i < n; i++) {

        int d, a;     // d = where it arrives (0 front, 1 end), a = its number
        cin >> d >> a;

        if (inLine[a]) {
            // A ball with this number is ALREADY in the line, so a
            // destruction happens. We remove balls until we have removed
            // the old ball with number a. The new ball is simply never
            // added (it is destroyed too).

            if (d == 0) {
                // The new ball arrived at the FRONT, so everything from
                // the front up to the old ball is destroyed.
                while (true) {
                    int removed = line.front();   // look at the front ball
                    line.pop_front();             // remove it from the front
                    inLine[removed] = false;      // it is no longer in the line
                    if (removed == a) {
                        break;                    // we removed the old ball a, stop
                    }
                }
            } else {
                // The new ball arrived at the END, so everything from
                // the old ball up to the end is destroyed.
                while (true) {
                    int removed = line.back();    // look at the last ball
                    line.pop_back();              // remove it from the end
                    inLine[removed] = false;      // it is no longer in the line
                    if (removed == a) {
                        break;                    // we removed the old ball a, stop
                    }
                }
            }

        } else {
            // No ball with this number is in the line, so the new ball
            // simply joins the line.
            if (d == 0) {
                line.push_front(a);   // add at the FRONT
            } else {
                line.push_back(a);    // add at the END
            }
            inLine[a] = true;         // remember that a is now in the line
        }
    }

    // line.size() tells us how many balls are left.
    cout << line.size() << endl;

    return 0;         // tells the computer the program finished successfully
}