/*
=====================================================================
QUESTION SUMMARY
=====================================================================
TeX (a typesetting language) does not like the plain double quote ".
It wants:
    an OPENING quote written as  ``  (two backticks)
    a CLOSING quote written as   ''  (two apostrophes)

TASK: Read some lines of text and print the same text, but replace
every " with the correct TeX version.

RULES:
 - Quotes alternate: 1st " -> ``, 2nd " -> '', 3rd " -> ``, and so on.
 - Input is many lines, with an even number of " in total.
 - Input ends at end-of-file (EOF).
 - Everything else stays EXACTLY the same, including single quotes
   like `C' (only the double quote " is changed).
 - A quote can open on one line and close on a later line.

SAMPLE INPUT:
"To be or not to be," quoth the Bard, "that
is the question".

SAMPLE OUTPUT:
``To be or not to be,'' quoth the Bard, ``that
is the question''.
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
#include <string>     // lets us use "string" (a variable that holds text)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    string line;      // a box that holds ONE line of text at a time

    // This true/false box remembers: is the NEXT quote an opening one?
    //   true  = next quote opens  -> print ``
    //   false = next quote closes -> print ''
    // It is declared OUTSIDE the loop so it keeps its value from line to
    // line (a quote may open on one line and close on another).
    bool nextIsOpening = true;

    // getline reads one whole line (spaces included) into "line".
    // When there is no more input (EOF) it fails, and the loop stops.
    while (getline(cin, line)) {

        // Look at the line one character at a time.
        // "char c : line" means: for each character c inside line.
        for (char c : line) {

            if (c == '"') {                 // is this character a double quote?

                if (nextIsOpening) {
                    cout << "``";           // opening: print two backticks
                } else {
                    cout << "''";           // closing: print two apostrophes
                }

                // Flip the box: true becomes false, false becomes true.
                // "!" means NOT. This makes the quotes alternate.
                nextIsOpening = !nextIsOpening;

            } else {
                cout << c;                  // normal character: print unchanged
            }
        }

        cout << '\n';   // the line ended, so start a new line in the output
    }

    return 0;           // tells the computer the program finished successfully
}