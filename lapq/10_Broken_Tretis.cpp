/*
=====================================================================
QUESTION SUMMARY: "Broken Tretis"
=====================================================================
Tretis is like Tetris. Pieces fall from the sky into a game area that
is 10 columns wide. Each piece is made of 4 square blocks.
Only 3 kinds of pieces exist, and they cannot be moved or rotated:
 - "-" (dash): 4 blocks in a flat line  -> 4 columns wide, 1 tall
 - "i"       : 4 blocks in a tall line  -> 1 column wide,  4 tall
 - "o"       : 4 blocks in a square     -> 2 columns wide, 2 tall

Each piece falls straight down. It stops when it lands on the floor
or on top of blocks that are already there. Full rows do NOT
disappear.

For each piece we are told its type and its LEFT-MOST column (1 to 10).

TASK: After all pieces have fallen, print the height of the tallest
      column (the highest level reached).

INPUT:
 - Line 1: N = number of pieces (1 <= N <= 1000)
 - Next N lines: a character (-, i or o) and a column number C
   (1 <= C <= 10).

OUTPUT:
 - One integer: the maximum height.

SAMPLE INPUT 1:
5
- 1
o 1
i 4
- 2
i 10

SAMPLE OUTPUT 1:
6

WHY 6? (walking through sample 1)
 Column heights start as all 0.
 "- 1" : covers columns 1-4. They are all 0, so it lands on the floor.
         Those columns become height 1.
 "o 1" : covers columns 1-2 (both height 1). Lands on top of them.
         It is 2 tall, so those columns become 1 + 2 = 3.
 "i 4" : covers column 4 (height 1). It is 4 tall, so column 4 becomes 5.
 "- 2" : covers columns 2-5. Their heights are 3, 1, 5, 0.
         The tallest is 5, so the piece rests at 5 and the columns
         become 5 + 1 = 6.
 "i 10": covers column 10 (height 0). Column 10 becomes 4.
 The tallest column is 6.

SAMPLE INPUT 2:
5
- 1
- 5
- 1
- 5
o 9

SAMPLE OUTPUT 2:
2

KEY IDEA:
 Keep a list of 10 numbers: the current height of each column.
 When a piece falls, it lands on the TALLEST column among the columns
 it covers (the other columns under it are left with gaps, which is
 fine). Then every column it covers gets the new height:
        new height = (tallest height under it) + (height of the piece)
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
#include <algorithm>  // lets us use max (pick the bigger of two numbers)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    int n;            // a box to hold N, the number of pieces
    cin >> n;         // read N from the input

    // A list of 10 boxes, one for each column.
    // heights[0] is column 1, heights[1] is column 2, ... heights[9] is
    // column 10. (C++ lists start counting at 0, not 1.)
    // The "= {0}" makes every box start at 0 (an empty game area).
    int heights[10] = {0};

    // Repeat once for each piece.
    for (int i = 0; i < n; i++) {

        char type;    // a box for the piece type: '-', 'i' or 'o'
        int col;      // a box for the left-most column number (1 to 10)
        cin >> type >> col;   // read both from the input

        // Columns in the input start at 1, but our list starts at 0,
        // so we subtract 1 to get the correct spot in the list.
        int start = col - 1;

        // Work out how wide and how tall this piece is.
        int width;    // how many columns the piece covers
        int height;   // how many rows tall the piece is

        if (type == '-') {
            width = 4;    // flat line: 4 columns wide
            height = 1;   // and only 1 row tall
        } else if (type == 'i') {
            width = 1;    // tall line: 1 column wide
            height = 4;   // and 4 rows tall
        } else {
            width = 2;    // the only choice left is 'o', the square:
            height = 2;   // 2 columns wide and 2 rows tall
        }

        // Find where the piece lands: it rests on the TALLEST column
        // among the columns it covers.
        int base = 0;     // start at 0 (the floor)
        for (int j = start; j < start + width; j++) {
            base = max(base, heights[j]);   // keep the bigger number
        }

        // The piece has landed. Every column it covers now has height
        // equal to (where it landed) + (how tall the piece is).
        for (int j = start; j < start + width; j++) {
            heights[j] = base + height;
        }
    }

    // Find the tallest column of all 10.
    int answer = 0;
    for (int j = 0; j < 10; j++) {
        answer = max(answer, heights[j]);
    }

    cout << answer << endl;   // print the maximum height

    return 0;                 // tells the computer the program finished successfully
}