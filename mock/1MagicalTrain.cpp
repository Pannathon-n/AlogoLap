/*
=====================================================================
QUESTION SUMMARY: "The Conductor's Magical Train"
=====================================================================
You manage a train made of cars. Each car has a unique ID number.
You start with an EMPTY train and get Q commands (Q <= 5000):

 - PUSH X     : attach car X to the very BACK of the train.
 - POP        : remove the LAST car (the back one).
                If the train is empty, do nothing.
 - INSERT I X : put car X so that it becomes the I-th car, counting
                from 0 (0 = the very front).
                If I >= the current number of cars, just attach X
                to the back.
 - REMOVE X   : search from the front for car X. If found, remove it
                (the cars behind it shift forward).
                If not found, do nothing.

TASK: After all commands, print the IDs from front to back, separated
      by single spaces. If the train is empty, print: Empty

INPUT:
 - Line 1: Q
 - Next Q lines: one command each.

OUTPUT:
 - One line: the final train, or the word Empty.

SAMPLE INPUT 1:
8
PUSH 101
PUSH 102
PUSH 103
INSERT 1 999
POP
REMOVE 101
INSERT 0 888
PUSH 104

SAMPLE OUTPUT 1:
888 999 102 104

WHY? (walking through sample 1, train shown front -> back)
 PUSH 101      -> 101
 PUSH 102      -> 101 102
 PUSH 103      -> 101 102 103
 INSERT 1 999  -> 101 999 102 103   (999 becomes the car at index 1)
 POP           -> 101 999 102       (103 removed from the back)
 REMOVE 101    -> 999 102
 INSERT 0 888  -> 888 999 102       (888 goes to the very front)
 PUSH 104      -> 888 999 102 104

SAMPLE INPUT 2:
4
PUSH 50
POP
REMOVE 50
POP
SAMPLE OUTPUT 2:
Empty
 (50 is pushed then popped. REMOVE 50 finds nothing. The last POP
  does nothing on an empty train.)

KEY IDEA:
 A "vector" (a list that can grow) can do all four commands:
   - push_back adds at the back          (PUSH)
   - pop_back removes the back           (POP)
   - insert puts a value at any spot     (INSERT)
   - erase removes the value at any spot (REMOVE, after we find it)
 Inserting or erasing in the middle shifts the other cars, which
 costs up to 5000 steps. With only 5000 commands, that is at most
 about 25 million steps, which is fast enough, so no fancy structure
 is needed.
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
#include <vector>     // lets us use "vector" (a list that can grow)
#include <string>     // lets us use "string" (a variable that holds text)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    int q;            // a box to hold Q, the number of commands
    cin >> q;

    // The train. train[0] is the FRONT car, the last item is the BACK car.
    // "long long" is a big number box (IDs go up to 1,000,000,000).
    vector<long long> train;

    // Handle each command one by one.
    for (int c = 0; c < q; c++) {

        string command;    // a box for the command word
        cin >> command;    // read the first word of the line

        if (command == "PUSH") {
            // Attach car X to the back.
            long long x;
            cin >> x;
            train.push_back(x);

        } else if (command == "POP") {
            // Remove the last car, but ONLY if the train is not empty.
            // (Removing from an empty list would crash the program.)
            if (!train.empty()) {      // "!" means NOT
                train.pop_back();
            }

        } else if (command == "INSERT") {
            // Put car X at index I.
            int i;
            long long x;
            cin >> i >> x;

            if (i >= (int)train.size()) {
                // I is too big (or exactly the size): attach at the back.
                train.push_back(x);
            } else {
                // "train.begin() + i" means "the spot number i".
                // insert puts x there; the cars from that spot onward
                // shift one place toward the back.
                train.insert(train.begin() + i, x);
            }

        } else {
            // The only command left is REMOVE.
            long long x;
            cin >> x;

            // Search from the front for the FIRST car with ID x.
            for (int j = 0; j < (int)train.size(); j++) {
                if (train[j] == x) {
                    train.erase(train.begin() + j);   // remove it, cars shift forward
                    break;    // stop searching: we only remove one car
                }
            }
            // If the loop finishes without finding x, nothing happens.
        }
    }

    // Print the result.
    if (train.empty()) {
        cout << "Empty" << endl;
    } else {
        for (int j = 0; j < (int)train.size(); j++) {
            if (j > 0) {
                cout << ' ';      // a space BETWEEN IDs only
            }
            cout << train[j];
        }
        cout << '\n';
    }

    return 0;         // tells the computer the program finished successfully
}
/*
On accuracy: this problem is the same “list with insert and erase” idea as the Cookies, 
Bonus points, and Tiniest machines tasks you already practiced, 
so it is a reasonable match for the midterm style. 
The one difference is that the limits here are small (Q ≤ 5000), 
so a plain vector is enough and a linked list is not required.
*/