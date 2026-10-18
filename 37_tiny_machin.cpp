/*
=====================================================================
QUESTION SUMMARY: "Tiniest machines"
=====================================================================
A tiny machine walks along a sequence of numbers (each number is 1 to 4).
It always stands on ONE number (its "location"). At the start it
stands on the FIRST number.

The machine can do 4 operations:
 - T = 1 : move to the NEXT number in the sequence.
           (If it is already on the last number, do nothing.)
           (The story says "move left", but the rule says "next
            location", and the examples confirm it moves forward.)
 - T = 2 : move back to the FIRST number.
 - T = 3 K : remove K numbers right AFTER its location.
           (If fewer than K numbers are after it, remove all of them.)
 - T = 4 L a1 ... aL : insert these L numbers right AFTER its location,
           in the same order as given (1 <= L <= 10).
 The machine itself does not move when it inserts or removes.

TASK: After all M operations, print the final sequence.

INPUT:
 - Line 1: N and M (both up to 100,000)
 - Line 2: the N starting numbers
 - Next M lines: the operations

OUTPUT:
 - The final sequence on ONE line, separated by spaces.

SAMPLE INPUT 1:
5 4
1 2 3 4 1
1
1
1
4 3 3 2 1

SAMPLE OUTPUT 1:
1 2 3 4 3 2 1 1

WHY? (walking through sample 1, [ ] = machine location)
 Start:         [1] 2 3 4 1
 T=1 (next):    1 [2] 3 4 1
 T=1 (next):    1 2 [3] 4 1
 T=1 (next):    1 2 3 [4] 1
 T=4 3 3 2 1:   insert 3, 2, 1 after the 4 -> 1 2 3 [4] 3 2 1 1
 Final: 1 2 3 4 3 2 1 1

KEY IDEA (linked list):
 Inserting or removing in the middle of a normal list is slow, because
 everything after it must shift. With 100,000 operations that is too
 slow. So for every number we keep a note: "which number comes right
 after me?" (like a treasure hunt).
   - INSERT: change just a few notes.
   - REMOVE: the machine's number points past the removed numbers.
   - Moving to the next number: follow the note.
   - Moving to the first number: jump back to the start.
 Each removed number is removed only once, so removing is fast overall.
 Since the machine always acts AFTER its own location, we never need
 to know who is BEFORE it. The first number is never removed
 (removals only happen AFTER the machine), so it is always the head.
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
#include <vector>     // lets us use "vector" (a list that can grow)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    // Magic speed-up lines so reading lots of numbers is fast.
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;         // n = starting numbers, m = number of operations
    cin >> n >> m;

    // Every number that ever exists gets an ID: 1, 2, 3, ...
    // At most n + 10*m numbers are ever created (each insert adds up
    // to 10), so we make room for that many (plus spot 0 = "nobody").
    //   value[id]    = the number (1 to 4) stored at this ID
    //   nextNode[id] = the ID that comes right after it (0 = nobody,
    //                  so it is the last one)
    int capacity = n + 10 * m + 2;
    vector<int> value(capacity, 0);
    vector<int> nextNode(capacity, 0);

    int created = 0;  // how many numbers have been created so far

    // Read the starting sequence and link them: 1 -> 2 -> 3 -> ... -> n
    for (int i = 1; i <= n; i++) {
        cin >> value[i];
        nextNode[i] = (i < n) ? i + 1 : 0;   // the last one has nobody after it
    }
    created = n;

    int head = 1;     // the ID of the first number in the sequence
    int cur = 1;      // the machine's location: it starts on the first number

    // Do the M operations.
    for (int i = 0; i < m; i++) {

        int t;        // the type of this operation
        cin >> t;

        if (t == 1) {
            // Move to the next number, but only if there is one.
            if (nextNode[cur] != 0) {
                cur = nextNode[cur];
            }

        } else if (t == 2) {
            // Move back to the first number.
            cur = head;

        } else if (t == 3) {
            // Remove K numbers right after the machine.
            int k;
            cin >> k;

            // Repeat up to k times, but stop early if nothing is left
            // after the machine (nextNode[cur] is 0).
            for (int step = 0; step < k && nextNode[cur] != 0; step++) {
                int victim = nextNode[cur];          // the number to remove
                nextNode[cur] = nextNode[victim];    // skip over it
            }

        } else {
            // t == 4: insert L numbers right after the machine.
            int l;
            cin >> l;

            // "tail" is the number after which we add the next new number.
            // It starts at the machine's location.
            // We remember who was after the machine BEFORE inserting,
            // because the last new number must point to that one.
            int after = nextNode[cur];
            int tail = cur;

            for (int j = 0; j < l; j++) {
                int x;
                cin >> x;                 // read one number to insert

                created = created + 1;    // create a new number
                value[created] = x;

                nextNode[tail] = created; // the previous one points to it
                tail = created;           // the new one becomes the tail
            }

            nextNode[tail] = after;       // connect the last new number to
                                          // what used to come after the machine
        }
    }

    // Print the final sequence: start at the first number and follow
    // the notes until we reach 0 (nobody).
    bool first = true;    // so we put spaces BETWEEN numbers only
    int p = head;
    while (p != 0) {
        if (!first) {
            cout << ' ';
        }
        cout << value[p];
        first = false;
        p = nextNode[p];
    }
    cout << '\n';

    return 0;         // tells the computer the program finished successfully
}