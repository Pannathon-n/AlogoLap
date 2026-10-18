/*
=====================================================================
QUESTION SUMMARY: "Postfix Evaluation"
=====================================================================
Normally we write math like this (INFIX):   (3 + 5) / (5 - 2)
In POSTFIX notation, the operator comes AFTER its two numbers:
                                            3 5 + 5 2 - /

To evaluate a postfix expression we use a STACK (a pile of plates
where you only touch the top plate):
 - If the token is a NUMBER: put it on top of the pile.
 - If the token is an OPERATOR (+ - * /):
       take the top TWO numbers off the pile,
       do the operation,
       put the result back on top of the pile.
 - The token "=" is always last and means "finished".
   The one number left on the pile is the answer.

TASK: Read the expression and print its value with 4 digits after
      the decimal point.

INPUT:
 - Many lines, one token per line: a number, an operator (+ - * /),
   or "=" as the very last token.

OUTPUT:
 - One line: the result with 4 decimal digits.

SAMPLE INPUT 1:
3 5 + 5 2 - / =       (one token per line in the real input)

SAMPLE OUTPUT 1:
2.6667

WHY 2.6667? (walking through sample 1)
 3   -> pile: [3]
 5   -> pile: [3, 5]
 +   -> take 5 and 3, 3+5 = 8       -> pile: [8]
 5   -> pile: [8, 5]
 2   -> pile: [8, 5, 2]
 -   -> take 2 and 5, 5-2 = 3       -> pile: [8, 3]
 /   -> take 3 and 8, 8/3 = 2.6667  -> pile: [2.6667]
 =   -> finished, answer is 2.6667

SAMPLE INPUT 2:
10 20 + 30 * 10 5 / + =
SAMPLE OUTPUT 2:
902.0000       (because (10+20)*30 + 10/5 = 900 + 2)

IMPORTANT DETAILS:
 - ORDER MATTERS for - and /. The number taken off the pile FIRST is
   the RIGHT side; the one taken SECOND is the LEFT side.
   For "5 2 -" we compute 5 - 2 (not 2 - 5).
 - Division must keep decimals (8 / 3 = 2.6667, not 2), so we store
   the numbers as "double" (numbers that can have a decimal part).
 - A lone "-" is the minus operator, but "-5" (longer than 1
   character) is a negative number. We tell them apart by length.
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
#include <string>     // lets us use "string" (a variable that holds text)
#include <stack>      // lets us use "stack" (a pile where you only touch the top)
#include <iomanip>    // lets us use fixed and setprecision (control decimals)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    // The pile of numbers. "double" means each number can have decimals.
    stack<double> pile;

    string token;     // a box for ONE token (number, operator, or "=")

    // Read one token at a time. cin >> token skips spaces and new lines.
    // The loop stops when the reading fails (no more input).
    while (cin >> token) {

        // "=" is the last token, so we stop reading.
        if (token == "=") {
            break;
        }

        // Is this token an operator? It is one if it is exactly ONE
        // character long AND that character is + - * or /.
        // (token[0] means "the first character of the token".)
        bool isOperator = (token.size() == 1 &&
                           (token[0] == '+' || token[0] == '-' ||
                            token[0] == '*' || token[0] == '/'));

        if (isOperator) {
            // Take the top number off the pile: this is the RIGHT side.
            double right = pile.top();   // top() looks at the top number
            pile.pop();                  // pop() removes it from the pile

            // Take the next number: this is the LEFT side.
            double left = pile.top();
            pile.pop();

            double result;               // a box for the answer of this step

            if (token[0] == '+') {
                result = left + right;
            } else if (token[0] == '-') {
                result = left - right;   // left first, then right
            } else if (token[0] == '*') {
                result = left * right;
            } else {
                result = left / right;   // the only choice left is "/"
            }

            pile.push(result);           // put the answer back on the pile

        } else {
            // It is a number. stod ("string to double") changes the text
            // "10" into the number 10.0, then we put it on the pile.
            pile.push(stod(token));
        }
    }

    // Print the one number left on the pile.
    // "fixed" + "setprecision(4)" means: always show exactly 4 digits
    // after the decimal point (so 902 prints as 902.0000).
    cout << fixed << setprecision(4) << pile.top() << endl;

    return 0;         // tells the computer the program finished successfully
}