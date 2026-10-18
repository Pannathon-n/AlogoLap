/*
=====================================================================
QUESTION SUMMARY: "Chemistry"
=====================================================================
In a game there are M item types, numbered 0 to M-1.
You own N items. Item i has type Pi.

A "combining machine" keeps a STACK S (a pile where you only touch
the top). It runs L instructions:
 1) push i            : put the TYPE of item i on top of the pile.
 2) swap              : swap the top two entries of the pile.
 3) combine_top a b c : remove the top two entries.
                        x = the top one, y = the one below it.
                        Put back ONE new entry of type
                        (a*x + b*y + c) mod M.
 4) combine_with i a b c : remove the top entry (call it y).
                        x = the type of item i.
                        Put back ONE new entry of type
                        (a*x + b*y + c) mod M.

TASK: After all instructions, print the type of the entry on top.

INPUT:
 - Line 1: M, N and L
 - Line 2: P1 ... PN (the types of the items)
 - Next L lines: an instruction type T (1 to 4) followed by its numbers:
     T=1: i          T=2: (nothing)
     T=3: a b c      T=4: i a b c

OUTPUT:
 - One integer: the type on top of the pile at the end.

SAMPLE OUTPUT: 5

WHY? (walking through the sample, M = 8, P = 0 3 2 5 4)
 push 1   -> [0]
 push 3   -> [0, 2]
 push 5   -> [0, 2, 4]
 swap     -> [0, 4, 2]
 combine_top 3 4 5: x = 2 (top), y = 4
          (3*2 + 4*4 + 5) % 8 = 27 % 8 = 3     -> [0, 3]
 swap     -> [3, 0]
 combine_with 4 1 5 0: x = type of item 4 = 5, y = 0 (top)
          (1*5 + 5*0 + 0) % 8 = 5              -> [3, 5]
 Top of the pile = 5.

KEY IDEA:
 Just do exactly what the instructions say, using a stack.
 The numbers are small (up to about 3 million), but we use
 long long to be safe.
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
#include <vector>     // lets us use "vector" (a list that can grow)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    int m, n, l;      // m = number of types, n = number of items,
                      // l = number of instructions
    cin >> m >> n >> l;

    // type[i] = the type of item i. Items are numbered from 1,
    // so we make n + 1 spots (spot 0 is unused).
    vector<long long> type(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> type[i];
    }

    // The pile S. We use a vector as a pile:
    //   push_back adds to the top, back() looks at the top,
    //   pop_back removes the top.
    vector<long long> pile;

    // Run each instruction.
    for (int k = 0; k < l; k++) {

        int t;        // the instruction type (1 to 4)
        cin >> t;

        if (t == 1) {
            // push i: put the TYPE of item i on top of the pile.
            int i;
            cin >> i;
            pile.push_back(type[i]);

        } else if (t == 2) {
            // swap: exchange the top two entries.
            int size = pile.size();
            long long temp = pile[size - 1];   // remember the top
            pile[size - 1] = pile[size - 2];   // the one below moves up
            pile[size - 2] = temp;             // the old top moves down

        } else if (t == 3) {
            // combine_top a b c
            long long a, b, c;
            cin >> a >> b >> c;

            long long x = pile.back();   // the top entry
            pile.pop_back();             // remove it
            long long y = pile.back();   // the entry that was below it
            pile.pop_back();             // remove it too

            // "%" is the remainder operator (the "mod" in the question).
            pile.push_back((a * x + b * y + c) % m);

        } else {
            // t == 4: combine_with i a b c
            int i;
            long long a, b, c;
            cin >> i >> a >> b >> c;

            long long x = type[i];       // the type of item i
            long long y = pile.back();   // the top entry
            pile.pop_back();             // remove it

            pile.push_back((a * x + b * y + c) % m);
        }
    }

    // The answer is the entry on top of the pile.
    cout << pile.back() << endl;

    return 0;         // tells the computer the program finished successfully
}