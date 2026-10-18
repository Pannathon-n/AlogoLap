/*
=====================================================================
QUESTION SUMMARY: "Wrong number"
=====================================================================
There was a secret table with N rows and N columns (3 <= N <= 30),
filled with positive integers. In the ORIGINAL table:
 - every ROW adds up to the same total, and
 - every COLUMN adds up to the same total.

Then exactly ONE cell was changed to a different number.
You are given the table AFTER the change.

TASK: Print the (changed) number sitting in the cell that was changed.

INPUT:
 - Line 1: N
 - Next N lines: N integers each (one row per line).

OUTPUT:
 - One integer: the value in the changed cell.

SAMPLE INPUT:
3
11 4 6
8 1 12
5 16 3

SAMPLE OUTPUT:
5

WHY 5? (walking through the sample)
 Row sums:    11+4+6 = 21,   8+1+12 = 21,   5+16+3 = 24
 Column sums: 11+8+5 = 24,   4+1+16 = 21,   6+12+3 = 21
 The rows should all be equal, but row 3 (sum 24) is different.
 The columns should all be equal, but column 1 (sum 24) is different.
 The changed cell is where that row and that column cross:
 row 3, column 1, which holds 5.

KEY IDEA:
 Changing one cell breaks the total of exactly ONE row and exactly
 ONE column. Find the "odd one out" row and the "odd one out" column.
 The cell where they cross is the answer.

 How do we know which total is the CORRECT one? Since N >= 3, at
 least 2 rows are untouched and share the correct total. Look at the
 first 3 rows: if row 1 and row 2 have the same sum, that is the
 correct total; if not, one of them is the odd one, so row 3's sum
 must be the correct one (it agrees with one of them).
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    int n;            // a box to hold N, the size of the table
    cin >> n;         // read N from the input

    // A 30 x 30 grid of numbers: grid[row][column].
    // The question says N is at most 30, so this is always big enough.
    // (C++ counts spots from 0, so the first row is row 0.)
    int grid[30][30];

    // Lists to hold the total of each row and of each column.
    // "= {0}" makes every total start at 0.
    int rowSum[30] = {0};
    int colSum[30] = {0};

    // Read the table. The outer loop goes through the rows, the inner
    // loop goes through the columns of that row.
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            cin >> grid[r][c];            // read one number

            rowSum[r] = rowSum[r] + grid[r][c];   // add it to its row's total
            colSum[c] = colSum[c] + grid[r][c];   // add it to its column's total
        }
    }

    // Work out the CORRECT row total (see KEY IDEA above).
    int correctRow;
    if (rowSum[0] == rowSum[1]) {
        correctRow = rowSum[0];   // rows 1 and 2 agree, so that's correct
    } else {
        correctRow = rowSum[2];   // one of rows 1/2 is odd; row 3 is correct
    }

    // Work out the CORRECT column total in the same way.
    int correctCol;
    if (colSum[0] == colSum[1]) {
        correctCol = colSum[0];
    } else {
        correctCol = colSum[2];
    }

    // Find the row whose total is NOT the correct one.
    int badRow = 0;
    for (int r = 0; r < n; r++) {
        if (rowSum[r] != correctRow) {
            badRow = r;           // remember this row's number
        }
    }

    // Find the column whose total is NOT the correct one.
    int badCol = 0;
    for (int c = 0; c < n; c++) {
        if (colSum[c] != correctCol) {
            badCol = c;           // remember this column's number
        }
    }

    // The changed cell is where the bad row and bad column cross.
    cout << grid[badRow][badCol] << endl;

    return 0;         // tells the computer the program finished successfully
}