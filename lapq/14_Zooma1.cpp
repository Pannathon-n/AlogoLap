/*
=====================================================================
QUESTION SUMMARY: "Zooma 1"
=====================================================================
There is a line of n balls, numbered 1 to n, in order.
You then shoot m more balls into the line, one at a time. The balls
you shoot are numbered n+1, n+2, ..., n+m (the j-th shot ball is n+j).

Each shot says: "put my new ball RIGHT AFTER ball number p".
 - p can be an original ball OR a ball you shot earlier.
 - Balls never disappear, so colors do not matter at all.
   (We read the colors from the input but ignore them.)

TASK: After all m shots, print the final line of ball numbers,
      one number per line, from the front of the line to the back.

INPUT:
 - Line 1: n and m (up to 1,000,000 each in the worst case).
 - Next n lines: one color per original ball (ignored).
 - Next m lines: two numbers d and p.
       d = color of the shot ball (ignored)
       p = the ball number it is placed right after.

OUTPUT:
 - n + m numbers, one per line: the final sequence.

SAMPLE INPUT:
5 4
1
2
1
3
3
4 3
1 1
2 6
1 5

SAMPLE OUTPUT:
1 7 2 3 6 8 4 5 9   (one per line in the real output)

WHY? (walking through the sample)
 Start:                    1 2 3 4 5
 Ball 6 after ball 3:      1 2 3 6 4 5
 Ball 7 after ball 1:      1 7 2 3 6 4 5
 Ball 8 after ball 6:      1 7 2 3 6 8 4 5
 Ball 9 after ball 5:      1 7 2 3 6 8 4 5 9   <- final answer

KEY IDEA (a "linked list"):
 Inserting in the middle of a normal list is slow, because everything
 after it has to shift over. With a million balls, that is too slow.

 Instead, for EVERY ball we only remember one thing:
 "which ball comes right after me?"  We call this next[ball].
 It is like a treasure hunt: each ball holds a note pointing to the
 next ball.

 To insert a new ball X right after ball P, we only change two notes:
     1) X's note points to whatever P was pointing to.
     2) P's note now points to X.
 That is just 2 steps, no matter how long the line is. Very fast!

 At the end, we start at the front and follow the notes one by one,
 printing each ball.
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
#include <vector>     // lets us use "vector" (a list of numbers)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    // These two lines make reading and printing MUCH faster.
    // We need this because there can be millions of numbers.
    // (You can treat them as "magic speed-up lines".)
    ios::sync_with_stdio(false);
    cin.tie(nullptr); 

    int n, m;         // n = original balls, m = balls we will shoot
    cin >> n >> m;    // read both numbers

    // The "notes" list. nextBall[x] = the ball that comes right after x.
    // We need spots for balls 1 to n+m, plus a special spot 0,
    // so the size is n + m + 1.
    // Every spot starts at 0.
    vector<int> nextBall(n + m + 1, 0);

    // Spot 0 is a special "fake ball" that stands at the very FRONT of
    // the line. It is not a real ball. Its note points to ball 1, so
    // when we print, we know where to start.
    // The number 0 is also used to mean "nothing after me" (end of line),
    // which works because no real ball is ever numbered 0.
    nextBall[0] = 1;

    // Link the original balls: 1 -> 2 -> 3 -> ... -> n
    for (int i = 1; i < n; i++) {
        nextBall[i] = i + 1;    // the ball after i is i+1
    }
    nextBall[n] = 0;            // the last ball has nothing after it

    // Read and ignore the n colors of the original balls.
    // We still have to read them, otherwise the next numbers we read
    // would be wrong.
    for (int i = 0; i < n; i++) {
        int color;
        cin >> color;           // read it and do nothing with it
    }

    // Now handle the m shots, one by one.
    for (int j = 1; j <= m; j++) {

        int color, p;           // color of the shot ball (ignored), and p
        cin >> color >> p;      // p = the ball we shoot our ball AFTER

        int newBall = n + j;    // the shot balls are numbered n+1, n+2, ...

        // Insert newBall right after ball p, in two steps:
        // Step 1: newBall points to whatever p was pointing to.
        /*
        Step 1: nextBall[newBall] = nextBall[p];
        In English: "Hey Ball 6 (newBall), copy whatever name is written on Ball 3's (p) paper."
        Ball 3’s paper says "Ball 4".
        So, Ball 6 writes "Ball 4" on its paper.
        Now, both Ball 3 and Ball 6 are pointing to Ball 4.
        Ball 3 ───────> Ball 4
                 ▲
        Ball 6 ──────────┘
        Step 2: nextBall[p] = newBall;
        In English: "Hey Ball 3 (p), erase your paper and write 'Ball 6' (newBall) instead."
         Ball 3 changes its paper from "Ball 4" to "Ball 6".
        */
        nextBall[newBall] = nextBall[p];
        // Step 2: p now points to newBall.
        nextBall[p] = newBall;
    }

    // Print the final line.
    // Start at the fake front ball (0), and move to its note (the first
    // real ball). Keep following notes until we reach 0 (the end).
    int current = nextBall[0];  // the first real ball in the line
    while (current != 0) {      // 0 means "no more balls"
        cout << current << '\n';       // print this ball's number
        current = nextBall[current];   // follow the note to the next ball
    }

    return 0;                   // tells the computer the program finished successfully
}