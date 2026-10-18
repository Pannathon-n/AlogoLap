/*
=====================================================================
QUESTION SUMMARY: "Dream within a Dream" (Inception)
=====================================================================
Dom travels from one person's dream into another person's dream.
He goes deeper each time, like opening boxes inside boxes.
We get n commands (queries) of three kinds:

 - "Sleep X" : Dom goes into the dream of person X. This is now the
              dream he is currently in.
 - "Kick"   : The person whose dream Dom is in wakes up, so Dom goes
              back to the PREVIOUS dream he came from.
              If Dom is not in any dream, ignore this command.
 - "Test"   : Print the name of the person whose dream Dom is in now.
              If Dom is in no dream, print: Not in a dream

TASK: Process all commands in order and print an answer for every
"Test" command.

INPUT:
 - Line 1: n = number of commands (1 <= n <= 10000)
 - Next n lines: one command each.
   (For "Sleep X", X is a name of letters only, up to 15 characters.)

OUTPUT:
 - One line for each "Test" command.
   Print the name exactly as it appeared in the input.

SAMPLE INPUT (shortened):
Sleep Dom, Sleep Sakin, Test, Sleep Asif, Sleep Mushfiq, Test, Kick,
Test, Sleep Shafi, Test, Kick, Test, Kick, Test, Kick, Test, Kick,
Test, Kick, Test

SAMPLE OUTPUT:
Sakin, Mushfiq, Asif, Shafi, Asif, Sakin, Dom, Not in a dream,
Not in a dream (one per line)

WHY? (walking through the first part of the sample)
 Sleep Dom    -> dreams: Dom
 Sleep Sakin  -> dreams: Dom, Sakin          (Sakin is the deepest)
 Test         -> prints Sakin
 Sleep Asif   -> dreams: Dom, Sakin, Asif
 Sleep Mushfiq-> dreams: Dom, Sakin, Asif, Mushfiq
 Test         -> prints Mushfiq
 Kick         -> Mushfiq wakes up, back to Asif
 Test         -> prints Asif
 ...and so on.

KEY IDEA:
 This is a STACK (a pile of plates):
   - "Sleep X" puts X on TOP of the pile.
   - "Kick" removes the TOP of the pile.
   - "Test" looks at the TOP of the pile.
   - An empty pile means Dom is awake (not in a dream).
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
#include <string>     // lets us use "string" (a variable that holds text)
#include <stack>      // lets us use "stack" (a pile where you only touch the top)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    int n;            // a box to hold n, the number of commands
    cin >> n;         // read n from the input

    // The pile of dreams. Each item is a person's name.
    // The TOP of the pile is the dream Dom is in right now.
    stack<string> dreams;

    // Repeat once for each command.
    // "i" counts the commands, starting at 0 and stopping before n.
    for (int i = 0; i < n; i++) {

        string command;   // a box for the command word: Sleep, Kick or Test
        cin >> command;   // read the first word of this line

        if (command == "Sleep") {
            // "Sleep" is followed by a name, so read the name too.
            string name;
            cin >> name;

            // Put the name on TOP of the pile.
            // Dom is now inside this person's dream.
            dreams.push(name);

        } else if (command == "Kick") {
            // Remove the top person (they wake up), but ONLY if the pile
            // is not empty. Removing from an empty pile would crash the
            // program, and the question says to ignore it anyway.
            if (!dreams.empty()) {   // "!" means NOT, so: if not empty
                dreams.pop();        // remove the top of the pile
            }

        } else {
            // The only command left is "Test".
            if (dreams.empty()) {
                // Nobody in the pile, so Dom is awake.
                cout << "Not in a dream" << '\n';
            } else {
                // Look at the top of the pile and print that name.
                cout << dreams.top() << '\n';
            }
        }
    }

    return 0;         // tells the computer the program finished successfully
}