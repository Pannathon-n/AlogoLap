/*
=====================================================================
QUESTION SUMMARY: "Rotating slot machine"
=====================================================================
A slot machine screen has 4 rows and 4 columns. Each cell shows a
digit from 0 to 9.

SCORE: the number of ROWS where all 4 digits are the same.

SPECIAL POWER: you may "rotate" each column up or down any number of
steps. Rotating is like a loop: a digit pushed off the top comes back
in at the bottom (and the other way round).
Example: column  9 1 3 2  rotated up 1 step becomes  1 3 2 9.

TASK: Rotate the columns in the best possible way and print the
      MAXIMUM score you can get. (Not rotating at all is allowed.)

INPUT:
 - 4 lines, each with 4 integers (0 to 9).

OUTPUT:
 - One integer: the maximum score.

SAMPLE INPUT 1:
9 3 1 4
1 9 3 1
3 5 9 3
2 1 6 9

SAMPLE OUTPUT 1:
2

WHY 2? (walking through sample 1)
 Rotate column 2 down 2 steps and column 3 down 1 step. The screen
 becomes:
   9 5 6 4
   1 1 1 1   <- all the same, 1 point
   3 3 3 3   <- all the same, 1 point
   2 9 9 9
 Total = 2 points, and no rotation can do better.

SAMPLE INPUT 2:
0 0 0 0
2 2 2 2
3 3 3 3
4 4 4 4
SAMPLE OUTPUT 2:
4      (already 4 same rows, no rotating needed)

KEY IDEA:
 A column has only 4 cells, so rotating it 4 steps brings it back to
 where it started. So each column only has 4 different choices:
 rotate by 0, 1, 2 or 3 steps. (Rotating "down 1" is the same as
 rotating "up 3", so we only need to think about going one direction.)
 There are 4 columns, so there are only 4 x 4 x 4 x 4 = 256 combos.
 That is small, so we simply TRY EVERY COMBINATION, count the score
 for each, and remember the best one.
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    // A 4x4 grid of numbers: grid[row][column].
    // C++ counts spots from 0, so rows and columns are 0, 1, 2, 3.
    int grid[4][4];

    // Read the 16 numbers. The outer loop goes through the rows,
    // the inner loop goes through the columns of that row.
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            cin >> grid[r][c];
        }
    }

    // A box to remember the best score found so far. Starts at 0.
    int best = 0;

    // Four loops: s0 is how many steps we rotate column 0,
    // s1 is for column 1, s2 for column 2, s3 for column 3.
    // Each one tries 0, 1, 2 and 3. Together they try ALL 256 combos.
    for (int s0 = 0; s0 < 4; s0++) {
        for (int s1 = 0; s1 < 4; s1++) {
            for (int s2 = 0; s2 < 4; s2++) {
                for (int s3 = 0; s3 < 4; s3++) {

                    // Put the four rotation amounts in a small list
                    // so we can look them up by column number.
                    int shift[4] = {s0, s1, s2, s3};

                    // The score for THIS combination. Starts at 0.
                    int score = 0;

                    // Check each row of the rotated screen.
                    for (int r = 0; r < 4; r++) {

                        // To find which digit sits at (row r, column 0)
                        // after rotating, we look at the ORIGINAL grid
                        // "shift" rows further down, wrapping around.
                        // "% 4" is the remainder operator: it wraps
                        // numbers back into 0..3 (4 becomes 0, 5 becomes 1).
                        // Example: r = 3, shift = 2 -> (3 + 2) % 4 = 1.
                        int first = grid[(r + shift[0]) % 4][0];

                        // Assume this row is all the same until we
                        // find a digit that is different.
                        bool allSame = true;

                        // Compare the other 3 columns with the first one.
                        for (int c = 1; c < 4; c++) {
                            int digit = grid[(r + shift[c]) % 4][c];
                            if (digit != first) {
                                allSame = false;   // found a different digit
                            }
                        }

                        // If the whole row matched, it earns 1 point.
                        if (allSame) {
                            score = score + 1;
                        }
                    }

                    // If this combination beat our record, remember it.
                    if (score > best) {
                        best = score;
                    }
                }
            }
        }
    }

    cout << best << endl;   // print the best score found

    return 0;               // tells the computer the program finished successfully
}